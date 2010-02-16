#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "compiler.h"

struct Expression
{
  int kindOf;
  enum {
    NUM = 0,
    STRING,
    NAME,
    LOCAL
  };
  int value;
  int ip;
};

class Parser
{

public:

  Parser(){}
  Compiler comp;
  Lexer lex;
  void parse();
  Token expr(Expression &exp,int precedence);
  void primary(Expression &exp);
  void stat();


};


#endif PARSER_H
