#include <iostream>
#include <fstream>
#include <stdexcept>

#include "ast/Context.hpp"
#include "parser/lexer.hpp"
#include "parser/parser.tab.hh"

int main (int argc, char** argv)
{
  if (argc < 4)
  {
    // FIXME
  }
  std::ifstream inDef(argv[1], std::ios_base::in);
  std::ifstream inBin(argv[2], std::ios_base::in | std::ios_base::binary);
  Context context(inBin, std::cout);
  lexer scanner(&inDef);
  yy::parser p(scanner, context);
  //p.set_debug_level(1);
  if (p.parse() != 0)
    throw std::runtime_error("Parser error.");
  context.definition(argv[3])->convert(context);
}