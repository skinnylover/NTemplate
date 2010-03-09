//#include <cstdio>
//#include <string>
//#include <algorithm>
// #include <set>
// #include <map>
 #include "print.h"
 


#define HALT 0xFFFFFFFF

//registers
#define R1   0x00000001
#define R2   0x00000002
#define R3   0x00000003
#define CF   0x00000004
#define ST   0x00000005 //top of the sack
#define STAT 0x00000006





#define CMP  0x30000000
#define JXX  0x20000000
#define JMP  0x10000000
#define JE   0x20000002
#define JNE  0x20000003
#define JL   0x20000006
#define JG   0x20000007


#define OUT  0x90000000//think


//flags
#define EQ   0x00000000 
#define NEQ  0x00010000
#define GE   0x00020000
#define LE   0x00030000

//arith
#define ADD  0x01000000
#define SUB  0x02000000
#define MUL  0x03000000
#define DIV  0x04000000

//stack ops
#define POP  0x00100000
#define PUSH 0x00200000

//regop
#define MOVE 0x00300000

#define operation(op)   (op & 0xFFF00000)

#define source1(op)    ((op & 0x00000F00) >> 8)
#define source(op)    ((op &  0x000000F0) >> 4)
#define destination(op) (op & 0x0000000F)

int makeOp(int op,int src1,int src,int dst)
{
  return (op | (src << 8) | (src << 4) | dst ) ;
}
//#define jmp(op) ((op & 0x0FFFFFF0) >> 1)
//#define jxx(op) ()

int *getDirection(int direction,int * stack, int * staticSeg,int * registers)
{
  switch(direction)
  {
  case ST:
    return stack;
  case STAT:
    return staticSeg;
  default:
    return registers;
  }
  //nevar get here
}

void forStat( instruction)
{
  int expression[60];
  in  ip = 0;
  Token tok;
  std::vector<int> jumpPoints;
  if (tok.kindOf == Token::NAME)
    compile();
  else
    N_assert("ggggg");
  switch(toknext.kindOf)
  {
  case Token::RANGE:
    continue;
  case Token::STRING:
    continue;
  case Token::LIST
    continue;
  }

  ParseExpression();
  

}

void ifstat()
{
  std::vector<int> jumpPoints;
  ParseCondition();
  parseExpression();
  while(tok.kindOf == Token::ELSEIF)
  {
    jumpPoints.push_back(ipPoint);
    ParseCondition();
    parseExpression();
  }
  if (NextToken(tok).kindOf == Token::ELSE) 
  {
    jumpPoints.push_back(ipPoint);
    parseExpresion();
  }
  else
    jumpPoints.push_back(ipPoint);
    
}


void primaryexp()
{
  Token tok;
  getNext(tok);
  switch(tok.kindOf)
  {
  case Token::NUM:
  case Token::NAME:
  case Token::STRING:
  default:
    

  }


}

int isBinarOp(int tokenkind)
{

   
}

Token expr(Token lhs, int precedence, Exp exp)
{
  Token binOp,next;
  std::pair;
  getNext(binOp);
  limit = Priority[binOp.kindOf];
  while(isBinaryOp(binOp.kindOf) && limit >= precedence) 
  {
    Expr exp2;
    next = primaryExp();
    
    getNext(binOp);
    limit = Priority[binOp.kindOf];
  }
  
  return 
}




  int main()
 {
   int staticSeg[] = {1,2,3,4,5,6};
   int instructions[50] = {(MOVE | (STAT << 4) | R1 ), //1
			   1 ,//2
			   2, //3
			   (CMP |(R1 << 4) | STAT),//4
			   2,//5
			   4,//6
			   JG,//7
			   9,//7
			   (OUT | R1),//8
			   2,//9
			   (ADD | (R1 << 8) | (STAT << 4) | R1),//10
			   2,//11
			   0,//12
			   2,//13
			   JMP,//14
			   -11,//15
			   HALT};//16
   int stack[100]={};
   int registers[20]={};
   int *ip = instructions;
   int *sp = stack;
   for(;*ip!=HALT;++ip)
   {
     // print(*ip);
     print("\n");
     switch(operation(*ip))
     {
     case MOVE:
       {
	 int *src = getDirection(source(*ip),stack,staticSeg,registers);
	 int *dst = getDirection(destination(*ip),stack,staticSeg,registers);
	 dst[*(ip+2)] = src[*(ip+1)]; 
	 ip+=2;
	 continue;
       }
       
     case POP:
       {
	 int *dst = getDirection(destination(*ip),stack,staticSeg,registers);
	 dst[*(ip+1)] = *sp;
	 ip++;
	 sp--;
	 continue;
       }
       
     case PUSH:
       {
	 int *dst = getDirection(destination(*ip),stack,staticSeg,registers);
	 sp++;
	 *sp = dst[*(ip+1)];
	 ip++;
	 continue;
       }
     case JMP:
       ip+=*(ip+1);
       ip--;
       continue;
       
     case JXX:
       switch(*ip)
       {
       case JE:	 
	 if (registers[CF] == EQ)
	 {
	   ip+=*(ip+1);
	   ip--;
	 }
	 break;
       case JNE:
	 if (registers[CF] == NEQ)
	 {
	   ip+=*(ip+1);
	   ip--;
	 }
	 break;
       case JG:
	 if (registers[CF] == GE)
	 {
	   ip+=*(ip+1);
	   ip--;
	 }
	 break;
       case JL:
	 if (registers[CF] == LE)
	 {
	   ip+=*(ip+1);
	   ip--;
	 }
	 break;
       default:
	 continue;
      
	 
       }
       ip++;
       
       continue;
     
     case OUT:
       {
	 int *dst = getDirection(destination(*ip),stack,staticSeg,registers);
	 print(dst[*(ip+1)]);
	 print("\n");
	 ip++;
	 continue;
       }
   
     case ADD:
       {
	 int *src = getDirection(source(*ip),stack,staticSeg,registers);
	 int *src1 = getDirection(source1(*ip),stack,staticSeg,registers);
	 int *dst = getDirection(destination(*ip),stack,staticSeg,registers);
	 dst[*(ip+1)] = src[*(ip+2)] + src1[*(ip+3)];
	 ip+=3;
	 continue;
       }
     case SUB:
       {
	 int *src = getDirection(source(*ip),stack,staticSeg,registers);
	 int *src1 = getDirection(source1(*ip),stack,staticSeg,registers);
	 int *dst = getDirection(destination(*ip),stack,staticSeg,registers);
	 dst[*(ip+1)] = src[*(ip+2)] - src1[*(ip+3)];
	 ip+=3;
	 continue;
       }
     case MUL:
       {
	 int *src = getDirection(source(*ip),stack,staticSeg,registers);
	 int *src1 = getDirection(source1(*ip),stack,staticSeg,registers);
	 int *dst = getDirection(destination(*ip),stack,staticSeg,registers);
	 dst[*(ip+1)] = src[*(ip+2)] * src1[*(ip+3)];
	 ip+=3;
	 continue;
       }
     case DIV:
       {
	 int *src = getDirection(source(*ip),stack,staticSeg,registers);
	 int *src1 = getDirection(source1(*ip),stack,staticSeg,registers);
	 int *dst = getDirection(destination(*ip),stack,staticSeg,registers);
	 dst[*(ip+1)] = src[*(ip+2)] / src1[*(ip+3)];
	 ip+=3;
	 continue;
       }
     case CMP:
       {
	 int *first = getDirection(source(*ip),stack,staticSeg,registers);
	 int *second = getDirection(destination(*ip),stack,staticSeg,registers);
	 if (first[*(ip+1)] == second[*(ip+2)])
	   registers[CF] = EQ;
	 else 
	 {
	   if(first[*(ip+1)] > second[*(ip+2)])
	     registers[CF] = GE;
	   else
	     registers[CF] = LE;
	 }
	 ip+=2;
	 continue;
       }
     }


   }
      
  return 0;

  
}
