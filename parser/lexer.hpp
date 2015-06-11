#ifndef LEXER_HPP
#define LEXER_HPP

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <stdexcept>
#include "parser.tab.hh"

class lexer : public yyFlexLexer {
public:
  lexer(std::istream *in) : yyFlexLexer(in) {}
  void yylex(yy::parser::symbol_type *lval) {
    yylval = lval;
    yylex();
  } 
  
private:
  int value(yy::parser::symbol_type symbol) {
    yylval->move(symbol);
    return 0;
  }
  void LexerError(const char* msg) {
    throw std::runtime_error(msg);
  }
  /* hide this one from public view */
  int yylex();
  /* yyval ptr */
  yy::parser::symbol_type *yylval; 
};

#endif /* LEXER_HPP */  
