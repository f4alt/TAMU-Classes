// File: assemblyParser.cpp
// Author: Christopher McGregor
// Date: 04/03/2020
// Section: 510
// E-mail: cjmac@tamu.edu
// Description:
// parses the input file to filter command types into a, c, l and invalid

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <cstdint>
#include <iomanip>
#include <algorithm>
#include <bitset>

class assemblyParser {
public:
  enum class commandType
  {
    invalid, a, c, l,
  };

  // load parser with file
  assemblyParser(const std::string &file) : infile(file, std::ifstream::in) {}

  // close file
  ~assemblyParser()
  {
    if (infile.is_open())
      infile.close();
  }

  // good stream state
  bool keep_going() const
  {
    return infile.good();
  }

  // keep reading file as long as there are lines remaining
  void advance()
  {
    std::string line;
    validCommand = commandType::invalid;
    do {
      std::getline(infile >> std::ws, line);

      // remove spaces from line
      line.erase(std::remove_if(line.begin(), line.end(), [](char x)
      {return std::isspace(x);}), line.end());

      if (line.empty())
        continue;

      // look for comment and erase if found
      std::string::size_type comment = line.find("//");
      if (comment != 0)
      {
        if (comment != std::string::npos)
          line.erase(comment);

        // look for @ - signifies a command
        if (line.find("@") == 0)
          validCommand = commandType::a;
        // look for () - signifies l command
        else if (line.find("(") == 0 && line.rfind(")") == line.size() - 1)
          validCommand = commandType::l;
        // else c command
        else
          validCommand = commandType::c;
      }
    } while (infile.good() && validCommand == commandType::invalid);

    if (validCommand != commandType::invalid) {
      if (validCommand != commandType::l)
        lineNum++;
      currCommand = line;
    } else
      currCommand = "";
  }

  // linenum
  uint16_t line() const
  {
    return lineNum;
  }

  // return command type
  commandType command() const
  {
    return validCommand;
  }

  // convert command types
  std::string symbol() const
  {
    switch (validCommand) {
      case commandType::a:
        return currCommand.substr(1);
        break;
      case commandType::l:
        return currCommand.substr(1, currCommand.size() - 2);
        break;
      default:
        return std::string("");
    };
  }

  // determine dest portion of c commands
  std::string dest() const
  {
    if (validCommand != commandType::c)
      return std::string("");

    std::string::size_type find_len = currCommand.find("=");
    if (find_len == std::string::npos)
      return std::string("");

    return currCommand.substr(0, find_len);
  }

  // determine comp portion of c commands
  std::string comp() const
  {
    if (validCommand != commandType::c)
      return std::string("");

    std::string::size_type find_len = currCommand.find("=");
    return currCommand.substr(find_len + 1, currCommand.find(";") - find_len - 1);
  }

  // determine jump portion of c commands
  std::string jump() const
  {
    if (validCommand != commandType::c)
      return std::string("");

    std::string::size_type find_len = currCommand.find(";");
    if (find_len == std::string::npos)
      return std::string("");
    return currCommand.substr(find_len + 1);
  }

  // go back to beginning of infile and reset stream state
  void reset()
  {
    validCommand = commandType::invalid;
    lineNum = 0;
    infile.clear();
    infile.seekg(0);
  }

private:
  commandType validCommand = commandType::invalid;
  uint16_t lineNum = 0;
  std::ifstream infile;
  std::string currCommand;
};
