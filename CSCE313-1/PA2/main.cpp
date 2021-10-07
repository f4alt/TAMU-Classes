#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>
#include <chrono>
#include <ctime>
#include <time.h>
#include <cstring>

using namespace std;

vector<int> background_processes;

void handle_background_proc() {
  for(int i = 0; i < background_processes.size(); i++) {
    if(waitpid(background_processes[i],0,WNOHANG) == background_processes[i]) {
      background_processes.erase(background_processes.begin() +i);
      i--;    // put i back one since we erased position
    }
  }
}

string rm_whitespace(string cmd) {
    string cleaned;
    for (int i = 0; i < cmd.size(); i++) {
        if (cmd[i] != ' ') {
            cleaned.push_back(cmd[i]);
            if(cmd[i+1] == ' ') {
                cleaned.push_back(' ');
            }
        }
    }
    return cleaned;
}

vector<string> split(string line, char separator=' ') {
    vector<string> separated_input;
    bool inside_quotes = false;
    string word = "";

    for(auto i = 0; i < line.size(); i++) {
        if (line[i] == '\"' || line[i] == '\'' || inside_quotes == true) {
          word.push_back(line[i]);
          if ((line[i] == '\"' || line[i] == '\'') && inside_quotes == true) {   // quote finished
            inside_quotes = false;
            if (i == (line.size() -1) || line[i] == separator) {
              separated_input.push_back(word);
            }
          }  else {
            inside_quotes = true;
          }
        }
       else if (inside_quotes == false) {
            if(line[i] == separator) {
                separated_input.push_back(word);
                word = "";
            } else if (i == (line.size() -1)) {
              word.push_back(line[i]);
              separated_input.push_back(word);
            } else {
              word.push_back(line[i]);
            }
        }
    }
    // cleanup output of weird breaks and whitespace
    for (int i=0; i<separated_input.size(); i++) {
      separated_input[i] = rm_whitespace(separated_input[i]);
      if (separated_input[i].size() == 0) {
        separated_input.erase(separated_input.begin() + i);
      }
    }
    return separated_input;
}

int main() {
	int stdin = dup(0);
	int stdout = dup(1);
  char buff[1000];
  string previous_dir;
  string current_dir;

	while (1) {
		handle_background_proc();
		// copy stdin and stdout to reset parent descriptor table after piping
		dup2(stdin,0);
		dup2(stdout,1);

    // print prompt w username and cwd
    // cout << getenv("LOGNAME") << ":" << getcwd(buff, sizeof(buff)) << "$ ";
    // print prompt w username and date-time
    time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char *t = ctime(&time);
    if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
    cout << getenv("LOGNAME") << ":" << t << "$ ";

    // get user input - exit shell on "exit"
		string inputline;
		getline (cin, inputline);
		if(inputline == string("exit")) {
			cout << "Bye!! End of Shell" <<endl;
			break;
		}

		//check for background processes
		bool is_bg_proc = false;
		if(inputline[inputline.size()-1] =='&') {
			cout << "Background process" <<endl;
			is_bg_proc = true;
			inputline = rm_whitespace(inputline.substr(0,inputline.size()-1));//removes & + the space from the end of the string
		}

    // check for piped commands and handle pieces
		vector<string> piped = split(inputline, '|');

		for( int i = 0; i < piped.size();i++) {
		    int fds[2];
		    pipe(fds);
        inputline = piped[i];

		    int pid = fork();

            if (pid == 0) { // child process
                // handle 'cd'
                if(rm_whitespace(inputline).find("cd") ==0) {
                    current_dir = getcwd(buff,sizeof(buff));
                    if (rm_whitespace(inputline).find("-") == 3) {
                        chdir(previous_dir.c_str());
                        previous_dir = current_dir;
                    }
                    else {
                        string dirname = rm_whitespace(split(inputline)[1]);
                        chdir(dirname.c_str());
                        previous_dir = current_dir;
                    }
                    continue;
                }

                // I/O redirection
                int pos = inputline.find('>');
                vector <string> check_forward_pipe = split(inputline, '>');
                if (check_forward_pipe.size() > 1) {
                    string command = rm_whitespace(inputline.substr(0,pos));
                    string filename = rm_whitespace(inputline.substr(pos+1));
                    filename = split(filename, ' ')[0];
                    // cout << "command:" << command << endl;
                    // cout << "filename:" << filename << endl;
                    inputline = command;
                    int fd = open(filename.c_str(), O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                    dup2(fd,1);
                    close(fd);
                }


                 pos = inputline.find('<');
                  vector <string> check_rev_pipe = split(inputline, '<');
                  if (check_rev_pipe.size() > 1) {
                      string command = rm_whitespace(inputline.substr(0,pos));
                      string filename = rm_whitespace(inputline.substr(pos+1));
                      filename = split(filename, ' ')[0];
                      // cout << "command:" << command << endl;
                      // cout << "filename:" << filename << endl;
                      inputline = command;
                      int fd = open(filename.c_str(), O_RDONLY,S_IWUSR|S_IRUSR);
                      dup2(fd,0);
                      close(fd);
                  }



                if( i < piped.size() - 1) {
                    dup2(fds[1] , 1);
                    close(fds[1]);
                }

                vector <string> cmd_parts = split(inputline);
                for (int i=0; i < cmd_parts.size(); i++) {
                  for (int j=0; j < cmd_parts[i].size(); j++) {
                    if (cmd_parts[i][j] == '\'' || cmd_parts[i][j] == '\"') {
                      // remove quotes from final output
                      cmd_parts[i].erase(0, 1);
                      cmd_parts[i].erase(cmd_parts[i].size() - 1);
                      break;
                    }
                  }
                }
                char** args = new char* [cmd_parts.size() +1];
                for (int i = 0; i < cmd_parts.size(); i++) {
              		args[i] = (char*) cmd_parts[i].c_str();
              	}

              	args [cmd_parts.size()] = NULL;
                execvp(args[0],args);

            }
            else {
                if(is_bg_proc == false) {
                    if (i == piped.size()-1) {
                        waitpid(pid,0,0);
                    }
                }
                else
                {
                    background_processes.push_back(pid);
                }

                dup2(fds[0],0);
                close(fds[1]); // close fd[1]
            }
		}
	}
	return 0;
}
