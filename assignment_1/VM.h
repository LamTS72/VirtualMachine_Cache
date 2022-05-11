#ifndef VM_H
#define VM_H

#include "main.h"
#define MAX_STACK 1000;
typedef uint16_t;


enum Instruction{
  ADD,MINUS,MUL,DIV,CmpEQ,CmpNE,CmpLT,CmpLE,CmpGT,CmpGE,
  Not,And,Or,Move,Load,Store,Jump,JumpIf,Call,Return,Halt,
  Input,Output
};

union Typedata{//0 no src
  int dataInt; //1
  float dataFlo;//2
  bool dataBoo;//3
  int address;//4
};

struct Data{
  Typedata data;
  int dataType=0;
};
////////////

class CPU{
public:
Instruction opcode;
int dest;// 1-15 generalregister , 0 InvalidOperand, 16 no dest
Data src;
void checkInstruction(string ins,regex reg, int error){git 
  regex add("^Add "); regex minus("^Minus "); regex mul("^Mul "); regex div("^Div ");
  regex cmpEQ("^CmpEQ "); regex cmpNE("^CmpNE "); regex cmpLT("^CmpLT "); regex cmpLE("^CmpLE ");
  regex cmpGT("^CmpGT"); regex cmpGE("^CmpGE "); regex not("^Not "); regex and("^And ");
  regex or("^Or "); regex move("^Move "); regex load("^Load "); regex store("^Store ");
  regex jump("^Jump "); regex jumpIf("^JumIf "); regex call("^Call "); regex back("^Return ");
  regex halt("^Halt "); regex inp("^Input "); regex out("^Output ");
  if(regex_match(ins.begin(),ins.end(),add)) opcode=ADD;
  else if(regex_match(ins.begin(),ins.end(),minus)) opcode=MINUS;
  else if(regex_match(ins.begin(),ins.end(),mul)) opcode=MUL;
  else if(regex_match(ins.begin(),ins.end(),div)) opcode=DIV;
  else if(regex_match(ins.begin(),ins.end(),cmpEQ)) opcode=CmpEQ;
  else if(regex_match(ins.begin(),ins.end(),cmpNE)) opcode=CmpNE;
  else if(regex_match(ins.begin(),ins.end(),cmpLT)) opcode=CmpLT;
  else if(regex_match(ins.begin(),ins.end(),cmpLE)) opcode=CmpLE;
  else if(regex_match(ins.begin(),ins.end(),cmpGT)) opcode=CmpGT;
  else if(regex_match(ins.begin(),ins.end(),cmpGE)) opcode=CmpGE;
  else if(regex_match(ins.begin(),ins.end(),not))   opcode=Not;
  else if(regex_match(ins.begin(),ins.end(),and))   opcode=And;
  else if(regex_match(ins.begin(),ins.end(),or))    opcode=Or;
  else if(regex_match(ins.begin(),ins.end(),move))  opcode=Move;
  else if(regex_match(ins.begin(),ins.end(),load))  opcode=Load;
  else if(regex_match(ins.begin(),ins.end(),store)) opcode=Store;
}
}



class VM
{
public:
  VM(){}
  void run(string filename);
};
 

#endif