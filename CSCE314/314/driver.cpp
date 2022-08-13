// File: driver.cpp
// Author: Christopher McGregor
// Date: 04/03/2020
// Section: 510
// E-mail: cjmac@tamu.edu
// Description:
// driver of the assembler combines assemblyParser.cpp, symbols.cpp and output.cpp

#include "assemblyParser.cpp"
#include "symbols.cpp"
#include "output.cpp"

int main(int argc, char *argv[])
{
  // error checking - valid number of input files
  if (argc > 2 || argc < 2)
  {
    std::cout << "ERROR: invalid number of input files" << std::endl;
    return -1;
  }

	symbolTable symbolTable;
	std::string infile(argv[1]);
  // remove .asm and add .hack to end of output file
	std::string outfile(infile.substr(0, infile.rfind(".")).append(".hack"));

  // load infile to assemblyParser and outfile to output
	assemblyParser in(infile);
	output c(outfile, &symbolTable);

  // pass 1 - read input and load labels
	while (in.keep_going()) {
		in.advance();
		if (in.command() == assemblyParser::commandType::l)
			symbolTable.label(in.symbol(), in.line());
	}
  // go back to beginng of infile
	in.reset();
  // pass 2 - write to ouput
	while (in.keep_going()) {
		in.advance();
		if (in.command() == assemblyParser::commandType::a)
			c.a_instruction(in.symbol());
		else if (in.command() == assemblyParser::commandType::c)
			c.c_instruction(in.dest(), in.comp(), in.jump());
	}
	return 0;
}
