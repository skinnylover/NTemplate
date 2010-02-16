

const char *reserved_tokens[] = 
  { "for","in","endfor"
    "if","else","endif",
    "=","<>",
    "set",
    "include",
    "comment",
    "range",
    NULL
  };



static int reserved(const  std::string& string)
{
  for (int i=0;reserved_tokens[i],++i)
  {
    if (reserved_tokes[i]==string)
      return i+1;
  }
  return 0;
}

void Lexer::ReadExpr(token & tok)
{
  for(;!(check('%') && checkNext('}'));)
  {
    if (current==' ')
      continue;
    if (current=='\"')
      ReadString(tok,"\"");
    if (isAlpha(current))
      ReadNameOrStatement(tok);
  }
  inExpression=false;

}

void Lexer::ReadNameOrStatement(token & tok)
{
  std::string string;
  for(;current!=EOZ;next())
  {
    if (check('{') && checknext('%'))
    {
      next();
      break;
    }
    if (isspace(current))
    {
      next();
      break;
    }
    string.append(current);
  }
  next();
  int token = reserved(string);
  //see token::enum
  if (token > 1)
    tok.type = token;
  else
  {
    tok.type = token::NAME;
    tok.hash = addString(string);
  }

}

void Lexer::readString(token & tok)
{
  std::string string;
  for(;current!=EOF;next())
  {
    if (check('{') && checknext('%'))
    {
      next();
      break;
    }
    string.append(current);
  }
  next();
  tok.type = token::STRING;
  tok.hash = addString(string);
}

void Lexer::readString1(token & tok)
{
  std::string string;
  for(;current!=EOZ;next())
  {
    if (check('\"'))
      break;
    string.append(current);
  }
  tok.type = token::STRING;
  tok.hash = addString(string);
}

void Lexer::lex(token & tok)
{
  switch(current)
  {
  case '{':
    if (next()=='%')
    {
      inExpression=true;
      ReadExpr(tok);
      break;
    }
  default:
    if (inExpression)
    {
      ReadExpr(tok);
      break;
    }
    ReadString(tok);
    break;
  }
}
