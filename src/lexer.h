#ifndef LEXER_H
#define LEXER_H 


struct Token
{
  int kindOf;
  int value;
  enum {
    PLUS=0,
    MINUS,
    MOD,
    DIV,
    MUL,
    POW,
    NUM,
    STRING,
    NAME,
    LBRK,
    RBRK,
    EOZ
  };
  
  Token(){}
Token(int kindOf, int value = 0 ):kindOf(kindOf),value(value){}
};

class Lexer
{
 public:
 Lexer(){}

  void nextToken()
  {

  }

  void getToken(Token & tok)
  {

  }

  void readString(token & tok);
  void readString1(token & tok);
  void ReadExpr(token & tok);
  void ReadNameOrStatement(token & tok);
  void lex(token & tok);
  
  

};


#endif
