// File: output.cpp
// Author: Christopher McGregor
// Date: 04/03/2020
// Section: 510
// E-mail: cjmac@tamu.edu
// Description:
// decodes the command types into binary to load into file.hack

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <cstdint>
#include <iomanip>
#include <algorithm>
#include <bitset>

class output {
public:
  output(const std::string &file, symbolTable *symbolTable)
  : outfile(file, std::ofstream::out), validSymbol(symbolTable) {}

  // close output file
  ~output()
  {
    if (outfile.is_open())
      outfile.close();
  }

  // write c instruction to output
  void c_instruction(const std::string &dest, const std::string &comp, const std::string &jump)
  {
    outfile << "111" << std::bitset<7>(validComp[comp])
           << std::bitset<3>(validDest[dest])
           << std::bitset<3>(validJump[jump])
           << std::endl;
  }

  // write a instruction to output
  void a_instruction(const std::string &symbol)
  {
    uint16_t address;
    try {
      if ((address = std::stoi(symbol)));
    } catch(std::invalid_argument) {
      if (!validSymbol->contains(symbol))
        validSymbol->add_var(symbol);

      address = validSymbol->address(symbol);
    }
    outfile << std::setfill('0') << std::setw(16) << std::bitset<16>(address) << std::endl;
  }

private:
  std::ofstream outfile;
  symbolTable *validSymbol;

  std::map<std::string, uint16_t> validDest = {
    {"",    0b000},
    {"M",   0b001},
    {"D",   0b010},
    {"MD",  0b011},
    {"A",   0b100},
    {"AM",  0b101},
    {"AD",  0b110},
    {"AMD", 0b111},
  };
  std::map<std::string, uint16_t> validComp = {
    {"0",   0b0101010},
    {"1",   0b0111111},
    {"-1",  0b0111010},
    {"D",   0b0001100},
    {"A",   0b0110000},
    {"!D",  0b0001101},
    {"!A",  0b0110001},
    {"-D",  0b0001111},
    {"-A",  0b0110011},
    {"D+1", 0b0011111},
    {"A+1", 0b0110111},
    {"D-1", 0b0001110},
    {"A-1", 0b0110010},
    {"D+A", 0b0000010},
    {"D-A", 0b0010011},
    {"A-D", 0b0000111},
    {"D&A", 0b0000000},
    {"D|A", 0b0010101},
    {"M",   0b1110000},
    {"!M",  0b1110001},
    {"-M",  0b1110011},
    {"M+1", 0b1110111},
    {"M-1", 0b1110010},
    {"D+M", 0b1000010},
    {"D-M", 0b1010011},
    {"M-D", 0b1000111},
    {"D&M", 0b1000000},
    {"D|M", 0b1010101},
  };
  std::map<std::string, uint16_t> validJump = {
    {"",    0b000},
    {"JGT", 0b001},
    {"JEQ", 0b010},
    {"JGE", 0b011},
    {"JLT", 0b100},
    {"JNE", 0b101},
    {"JLE", 0b110},
    {"JMP", 0b111},
  };
};
