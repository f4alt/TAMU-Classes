#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;


int main() {
int fd=open("file.txt", O_CREAT|O_RDWR);
write(fd, "Hello world", 6);
if (!fork()) {
	dup2(fd, 1);
	cout << "Mars, I am here!!" << endl;
} else {
	wait (0);
	lseek (fd, 0, SEEK_SET);
	cout << "Mars is great" << endl;
//	write (fd, "Hola ", 5);
	close (fd);
}
}/*


for (int i=0; i < 4; i++) {
	int cid = fork();
	if (i < 2)
		wait(0);
	cout << "ID=" << getpid() << endl;
}
}
*/
