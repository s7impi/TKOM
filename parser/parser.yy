%code requires {
#include "ast/Array.hpp"
#include "ast/BinaryExpression.hpp"
#include "ast/Choice.hpp"
#include "ast/Context.hpp"
#include "ast/Definition.hpp"
#include "ast/Expression.hpp"
#include "ast/Field.hpp"
#include "ast/Integer.hpp"
#include "ast/Node.hpp"
#include "ast/Number.hpp"
#include "ast/Reference.hpp"
#include "ast/String.hpp"
#include <map>
#include <memory>
#include <vector>
#include <string>
class lexer;
typedef unsigned int uint;
}

%skeleton "lalr1.cc"
%require "3.0"

%debug
%defines
%define api.token.constructor
%define api.value.type variant
%define parse.error verbose

%lex-param { lexer & scanner }
%parse-param { lexer & scanner }
%parse-param { Context & context }

%code {
static yy::parser::symbol_type yylex(lexer& scanner);
}

%token <uint> NUMBER
%token <std::string> IDENTIFIER
%token DEFINITION_OPERATOR
%token DEFINITION_OPEN
%token DEFINITION_CLOSE
%token SEMICOLON
%token MAP_SEPARATOR
%token ARRAY_OPEN
%token ARRAY_CLOSE
%token CHOICE_OPEN
%token CHOICE_CLOSE
%token LEFT
%token RIGHT
%token ADD_OPERATOR  
%token SUB_OPERATOR
%token MUL_OPERATOR
%token BIT
%token UINT8
%token UINT16
%token UINT32
%token INT8
%token INT16
%token INT32
%token STRING
%token CHOICE

%type <int> start
%type <std::shared_ptr<ast::Definition>> definition
%type <std::vector<std::shared_ptr<ast::Node>>> fields
%type <std::map<uint, std::shared_ptr<ast::Node>>> mappedFields
%type <std::shared_ptr<ast::Field>> field
%type <std::shared_ptr<ast::Choice>> choice
%type <std::shared_ptr<ast::Node>> type
%type <std::shared_ptr<ast::Expression>> addi
%type <std::shared_ptr<ast::Expression>> multi
%type <std::shared_ptr<ast::Expression>> term

%%

start:
  definition { context.definition($1->id(), $1); }
| start definition { context.definition($2->id(), $2); }
;

definition:
  IDENTIFIER DEFINITION_OPERATOR DEFINITION_OPEN fields DEFINITION_CLOSE SEMICOLON { $$=std::make_shared<ast::Definition>($1, std::move($4)); }
;

fields:
  field { $$=std::vector<std::shared_ptr<ast::Node>>{std::move($1)}; }
| fields field { $$=std::move($1); $$.emplace_back(std::move($2)); }
;

mappedFields:
  mappedFields NUMBER MAP_SEPARATOR field { $$=std::move($1); $$.emplace($2, std::move($4)); }
| NUMBER MAP_SEPARATOR field { $$=std::map<uint, std::shared_ptr<ast::Node>>{std::make_pair($1, std::move($3))}; }
;

field:
  type IDENTIFIER SEMICOLON { $$=std::make_shared<ast::Field>($2, std::move($1)); }
| type IDENTIFIER ARRAY_OPEN addi ARRAY_CLOSE SEMICOLON { $$=std::make_shared<ast::Field>($2, std::make_shared<ast::Array>(std::move($4), std::move($1)));  }
;

choice:
  CHOICE CHOICE_OPEN IDENTIFIER CHOICE_CLOSE DEFINITION_OPEN mappedFields DEFINITION_CLOSE { $$=std::make_shared<ast::Choice>($3, std::move($6)); }
;
  
type:
  BIT { $$=std::make_shared<ast::Integer<bool>>(); }
| UINT8 { $$=std::make_shared<ast::Integer<uint8_t>>(); }
| UINT16 { $$=std::make_shared<ast::Integer<uint16_t>>(); }
| UINT32 { $$=std::make_shared<ast::Integer<uint32_t>>(); }
| INT8 { $$=std::make_shared<ast::Integer<int8_t>>(); }
| INT16 { $$=std::make_shared<ast::Integer<int16_t>>(); }
| INT32 { $$=std::make_shared<ast::Integer<uint32_t>>(); }
| STRING { $$=std::make_shared<ast::String>(); }
| IDENTIFIER { $$=std::make_shared<ast::Reference>($1); }
| choice { $$=std::move($1); }
;

addi:
  multi ADD_OPERATOR addi { $$=std::make_shared<ast::BinaryExpression>(std::move($1), ast::BinaryExpression::Operator::ADD, std::move($3)); }
| multi SUB_OPERATOR addi { $$=std::make_shared<ast::BinaryExpression>(std::move($1), ast::BinaryExpression::Operator::SUB, std::move($3)); }
| multi { $$=std::move($1); }
;

multi:
  term MUL_OPERATOR multi { $$=std::make_shared<ast::BinaryExpression>(std::move($1), ast::BinaryExpression::Operator::MUL, std::move($3)); }
| term { $$=std::move($1); }
;

term:
  LEFT addi RIGHT { $$=std::move($2); }
| NUMBER { $$=std::make_shared<ast::Number>($1); }
| IDENTIFIER { $$=std::make_shared<ast::Reference>($1); }
;

%%

#include "lexer.hpp"

void yy::parser::error(const std::string& str)
{
  throw std::runtime_error(str.c_str());
}

static yy::parser::symbol_type yylex(lexer& scanner) {
  yy::parser::symbol_type sym;
  scanner.yylex(&sym);
  return sym;
}