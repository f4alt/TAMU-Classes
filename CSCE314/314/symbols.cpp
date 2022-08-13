// File: symbols.cpp
// Author: Christopher McGregor
// Date: 04/03/2020
// Section: 510
// E-mail: cjmac@tamu.edu
// Description:
// maps symbols to instructions

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <cstdint>
#include <iomanip>
#include <algorithm>
#include <bitset>

class symbolTable {
public:
  void label(const std::string &symbol, uint16_t address)
  {
    validSymbol[symbol] = address;
  }

  void add_var(const std::string &symbol)
  {
    validSymbol[symbol] = m_var_address++;
  }

  bool contains(const std::string &symbol)
  {
    return validSymbol.find(symbol) != validSymbol.end();
  }

  uint16_t address(const std::string &symbol)
  {
    return validSymbol[symbol];
  }

private:
  std::map<std::string, uint16_t> validSymbol = {
    {"0",      0x0000},
    {"SP",     0x0000},
    {"LCL",    0x0001},
    {"ARG",    0x0002},
    {"THIS",   0x0003},
    {"THAT",   0x0004},
    {"R0",     0x0000},
    {"R1",     0x0001},
    {"R2",     0x0002},
    {"R3",     0x0003},
    {"R4",     0x0004},
    {"R5",     0x0005},
    {"R6",     0x0006},
    {"R7",     0x0007},
    {"R8",     0x0008},
    {"R9",     0x0009},
    {"R10",    0x000A},
    {"R11",    0x000B},
    {"R12",    0x000C},
    {"R13",    0x000D},
    {"R14",    0x000E},
    {"R15",    0x000F},
    {"SCREEN", 0x4000},
    {"KBD",    0x6000},
  };
  uint16_t m_var_address = 0x0010;
};
