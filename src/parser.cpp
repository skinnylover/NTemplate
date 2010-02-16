#include <iostream>
#include <vector>
#include <map>
#include "print.h"


#define N_ASSERT(a)  printf("sdasd");






struct Priority
{
  int left;
  int right;
} priority[]=
  {
    {1,1}, //PLUS
    {1,1},//MINUS
    {2,2}, // MOD
    {3,3},//DIV
    {4,4},//MUL
    {6,5} //POW
  };

std::vector<Token> tokens;

void nextToken()
{
  tokens.erase(tokens.begin());
}

void getToken(Token & tok)
{
  tok = *(tokens.begin());
}

static void match(int matched)
{
  Token tok;
  getToken(tok);
  if (tok.kindOf != matched)
    printf("dasdasd");
    //N_ASSERT();
}



void Parser::primary(Expression &exp)
{
  Token tok;
  getToken(tok);
  switch(tok.kindOf)
    {
    case Token::NUM:
      exp.kindOf = Expression::NUM;
      exp.value = tok.value;
      return;
    case Token::NAME:
      exp.kindOf = Expression::NAME;
      exp.value = tok.value;
      return;
    case Token::STRING:
      exp.kindOf = Expression::STRING;
      exp.value = tok.value;
      return;
    default:
      if (tok.kindOf == Token::LBRK)
      {
	nextToken();
	expr(exp,0);
	match(Token::RBRK);
      }
      //else 
      //N_ASSERT("adasd");
      

    }

}


static bool isBinaryOp(Token & tok)
{
  return tok.kindOf >= Token::PLUS && tok.kindOf < Token::NUM;
}

static int getPriority(Token &tok)
{
  if (isBinaryOp(tok))
    return priority[tok.kindOf].left;
  return -1;
}


int arith(int n1, int n2, const Token &binOp)
{
  switch(binOp.kindOf)
  {
  case Token::PLUS:
    return n1+n2;
  case Token::MINUS:
    return n1-n2;
  case Token::MUL:
    return n1*n2;
  case Token::DIV:
    return n1/n2;
  case Token::MOD:
    return n1%n2;
  default :
    return n1;
  }
}



void compileBinExp(Expression &exp1, Expression &exp2, Token binOp)
{
  Expression exp;
  if (exp1.kindOf == Expression::NUM)
    if (exp2.kindOf == Expression::NUM)
    {
      exp1.kindOf = Expression::NUM;
      exp1.value = arith(exp1.value, exp2.value, binOp);
    }
    //print(binOp.kindOf);
  // if (exp1.kindOf == )
    
}

Token Parser::expr(Expression &exp, int precendence)
{
  primary(exp);
  Token binOp;
  nextToken();
  getToken(binOp);
  int limit = -1;
  if (isBinaryOp(binOp))
    limit = priority[binOp.kindOf].left;
  while(isBinaryOp(binOp) && limit >= precendence)
  {
    Expression exp1;
    nextToken();
    Token tok1 = expr(exp1,priority[binOp.kindOf].right);
    compileBinExp(exp,exp1,binOp);
    binOp = tok1;
    //getToken(token);
    //exp = exp1;
  }

  return binOp; 
  
}

void Parser::stat()
{
  

}
