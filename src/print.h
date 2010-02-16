
#include <cstdio>

void print(char c)
{
  printf("%c",c);
}
void print(unsigned int n)
{
  printf("%u",n);
}
void print(int n)
{
  printf("%d",n);
}
void print(long int l)
{
  printf("%ld",l);
}
void print(long long int l)
{
  printf("%lld",l);
}

void print(const char* str)
{
  printf("%s",str);
}
