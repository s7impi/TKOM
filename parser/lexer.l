%{
#include <iostream>
#include <cstdio>
#include "lexer.hpp"
using namespace std;
%}

%option yyclass="lexer"
%option c++
%option noyywrap
    
NUMBER		[0-9]+
IDENTIFIER	[a-zA-Z][a-zA-Z0-9_]*
    
%%

{NUMBER}	{
  uint n;
  sscanf(YYText(), "%u", &n);
  return value(yy::parser::make_NUMBER(n));
}

"::="		{ return value(yy::parser::make_DEFINITION_OPERATOR()); }
"{"		{ return value(yy::parser::make_DEFINITION_OPEN()); }
"}"		{ return value(yy::parser::make_DEFINITION_CLOSE()); }
";"		{ return value(yy::parser::make_SEMICOLON()); }
":"		{ return value(yy::parser::make_MAP_SEPARATOR()); }
"["		{ return value(yy::parser::make_ARRAY_OPEN()); }
"]"		{ return value(yy::parser::make_ARRAY_CLOSE()); }
"<"		{ return value(yy::parser::make_CHOICE_OPEN()); }
">"		{ return value(yy::parser::make_CHOICE_CLOSE()); }
"("		{ return value(yy::parser::make_LEFT()); }
")"		{ return value(yy::parser::make_RIGHT()); }
"+"		{ return value(yy::parser::make_ADD_OPERATOR()); }
"-"		{ return value(yy::parser::make_SUB_OPERATOR()); }
"*"		{ return value(yy::parser::make_MUL_OPERATOR()); }
"bit"		{ return value(yy::parser::make_BIT()); }
"uint8"		{ return value(yy::parser::make_UINT8()); }
"uint16"	{ return value(yy::parser::make_UINT16()); }
"uint32"	{ return value(yy::parser::make_UINT32()); }
"int8"		{ return value(yy::parser::make_INT8()); }
"int16"		{ return value(yy::parser::make_INT16()); }
"int32"		{ return value(yy::parser::make_INT32()); }
"string"	{ return value(yy::parser::make_STRING()); }
"choice"	{ return value(yy::parser::make_CHOICE()); }

{IDENTIFIER}	{ return value(yy::parser::make_IDENTIFIER(YYText())); }

[ \t\n]+	/* eat up whitespace */
.		cout << "Unrecognized character found: " << YYText() << "\n";
