#include "VM.h"

//TrinhSonLam
void VM:: loadFile(string filename){
ifstream myfile(filename);
        string s;
        while (getline(myfile,s)){
            vector <string> line;
            string part;
            int countspace=0;
            for (int indx=0; indx<(int)s.size(); indx++){
                 if (s[indx]==' '){                             //nếu chuỗi s tại vị trí idx có space
                    if(indx==0 || indx==(int)(s.size()-1))  throw InvalidInstruction(countINS);                      
                        ++countspace;
                        line.push_back(part);                      // line là dòng thứ nào đó  sẽ đầy chuỗi item 
                        part.clear();                               // chuổi part sau đó sẽ dc xoá đi 
                }                                          
                else part.push_back(s[indx]);
            }
            line.push_back(part);  // line =  [INS] ->[DST,] ->[SRC]
            if(line[0]=="Return"|| line[0]=="Halt"){
                if(countspace>0) throw InvalidInstruction(countINS);
            }
            else if(line[0]=="Not"||line[0]=="Output"|| line[0]=="Input"||line[0]=="Jump"||line[0]=="Call"){
                if(countspace>1||countspace <=0) throw InvalidInstruction(countINS);
            }
            else{
                if(countspace>2 || countspace <=1) throw InvalidInstruction(countINS); 
            }
            readINS.push_back(line);
            countINS++;
    } 
};
VM::dataType VM::srcData(string src){
        dataType reg;
        if(src[0] == 'R'){
          int i=stoi(src.substr(1));
            return R[i];
    	}
        
        if (src.find('.')!= string::npos){
            reg.type=Float;                     
            reg.data.dFloat=stof(src);
        }
        else if (src.find('A')!= string::npos){
            reg.type=Addr;
            src.pop_back();             //bỏ đi ký tự A ở cuối chuỗi
            reg.data.dAddr=stoi(src);
        }
        else if (isdigit(src[0])){              
            reg.type=Int;
            reg.data.dInt=stoi(src);
        }
        else {
            reg.type=Bool;
            if (src=="TRUE")
            reg.data.dBool=true;
            else reg.data.dBool=false;
        }
        return reg; 
};

void VM:: execuProgram(){

    smatch matchs;
    regex ARITHadd("Add");regex ARITHminus("Minus");regex ARITHmul("Mul");regex ARITHdiv("Div");
    regex CMP("CmpEQ|CmpNE|CmpLT|CmpLE|CmpGT|CmpGE");
    regex CMPeq("CmpEQ");regex CMPne("CmpNE");regex CMPlt("CmpLT");regex CMPle("CmpLE");regex CMPgt("CmpGT");regex CMPge("CmpGE");
    regex LOGnot("Not"); regex LOGand("And");regex LOGor("Or");
    regex REWRmove("Move");regex REWRload("Load");regex REWRstore("Store");
    regex CTRjump("Jump");regex CTRjumpif("JumpIf");regex CTRcall("Call");regex CTRreturn("Return");regex CTRhalt("Halt");
    regex IOPip("Input");regex IOPop("Output");


	while (true){
            vector<string> part = readINS[IP];
            int ip=IP;
            IP++;

               if (regex_match(part[0],matchs,ARITHadd)) {
                    R[stoi(part[1].substr(1))]+=srcData(part[2]);
                }
                else if (regex_match(part[0],matchs,ARITHminus)) {
                    R[stoi(part[1].substr(1))]-=(srcData(part[2]));
                }
                else if (regex_match(part[0],matchs,ARITHmul)) {
                    R[stoi(part[1].substr(1))]*=(srcData(part[2]));
                }
                else if (regex_match(part[0],matchs,ARITHdiv)) {
                    if(srcData(part[2]).data.dInt == 0 || srcData(part[2]).data.dFloat == 0.0 ) throw DivideByZero(ip);
                    R[stoi(part[1].substr(1))]/=(srcData(part[2]));
                }
            // Compare
                else if (regex_match(part[0],matchs,CMPeq)) {
                    int i=stoi(part[1].substr(1));
                    R[i].data.dBool=(R[i]==(srcData(part[2])));
                    R[i].type = Bool;
                }
                else if (regex_match(part[0],matchs,CMPne)) {
                    int i=stoi(part[1].substr(1));
                    R[i].data.dBool=(R[i]!=(srcData(part[2])));
                    R[i].type = Bool;
                }
                else if (regex_match(part[0],matchs,CMPlt)) {
                    int i=stoi(part[1].substr(1));
                    R[i].data.dBool=(R[i]<(srcData(part[2])));
                    R[i].type = Bool;
                }
                else if (regex_match(part[0],matchs,CMPle)) {
                    int i=stoi(part[1].substr(1));
                    R[i].data.dBool=(R[i]<=(srcData(part[2])));
                    R[i].type = Bool;
                }
                else if (regex_match(part[0],matchs,CMPgt)) {
                    int i=stoi(part[1].substr(1));
                    R[i].data.dBool=(R[i]>(srcData(part[2])));
                    R[i].type = Bool;
                }
                else if (regex_match(part[0],matchs,CMPge)) {
                    int i=stoi(part[1].substr(1));
                    R[i].data.dBool=(R[i]>=(srcData(part[2])));
                    R[i].type = Bool;
                }

            // Logic
                else if (regex_match(part[0],matchs,LOGnot)) {
                    int i=stoi(part[1].substr(1));
                    if(R[i].type != Bool){
                        throw TypeMismatch(ip);
                    }
                    else
                        R[i].data.dBool = !(R[i].data.dBool);
                }

                else if (regex_match(part[0],matchs,LOGand)) {
                    int i=stoi(part[1].substr(1));
                    if(R[i].type != Bool){
                        throw TypeMismatch(ip);
                    }
                    else
                        R[i].data.dBool = (R[i].data.dBool&&srcData(part[2]).data.dBool);
                }

                else if (regex_match(part[0],matchs,LOGor)) {
                    int i=stoi(part[1].substr(1));
                    if(R[i].type != Bool){
                        throw TypeMismatch(ip);
                    }
                    else
                        R[i].data.dBool = (R[i].data.dBool||srcData(part[2]).data.dBool);
                }

                
            // Load and Store
                else if (regex_match(part[0],matchs,REWRmove)) {
                    int i=stoi(part[1].substr(1));
                    R[i] = srcData(part[2]);
                }
                else if (regex_match(part[0],matchs,REWRload)) {
                    if(srcData(part[2]).type != Addr){

                        throw TypeMismatch(ip);
                    }
                    else{
                        int i=stoi(part[1].substr(1));
                        R[i] = static_Mem[srcData(part[2]).data.dAddr];
                    }
                }
                else if (regex_match(part[0],matchs,REWRstore)) {
                    int i=stoi(part[1].substr(1));
                    if(R[i].type != Addr){
                        throw TypeMismatch(ip);
                    }
                    else{
                        static_Mem[R[i].data.dAddr] = srcData(part[2]);
                    }
                }


            //control
                else if (regex_match(part[0],matchs,CTRjump)) {
                    if(srcData(part[1]).data.dAddr > countINS||srcData(part[1]).data.dAddr < 0 ) throw InvalidDestination(ip);
                    IP = srcData(part[1]).data.dAddr;
                }
                else if (regex_match(part[0],matchs,CTRjumpif)) {
                    int i=stoi(part[1].substr(1));
                    if(R[i].data.dBool){
                      if (srcData(part[2]).data.dAddr > countINS || srcData(part[2]).data.dAddr <0) throw InvalidDestination(ip);
                     IP = srcData(part[2]).data.dAddr;
                   }  
                }
                else if (regex_match(part[0],matchs,CTRcall)) {
                    Stack.push_back(IP);
                    if(Stack.size()== 999) throw StackFull(ip);
                    if(srcData(part[1]).data.dAddr > countINS || srcData(part[1]).data.dAddr <0) throw InvalidDestination(ip);
                    IP = srcData(part[1]).data.dAddr;
                }
                else if (regex_match(part[0],matchs,CTRreturn)) {
                    IP = Stack.back();
                    Stack.pop_back();
                }
                else if (regex_match(part[0],matchs,CTRhalt)) {
                    return;
                }

                //...06
            // Inp and Outp
                else if (regex_match(part[0],matchs,IOPip)) {
                    string s;cin>>s;
                    if(s.find('A')!= string::npos) throw InvalidInput(ip);
                    int i=stoi(part[1].substr(1));
                    R[i]=srcData(s);
                }
                else if (regex_match(part[0],matchs,IOPop)) {
                    dataType out = srcData(part[1]);
                
                    if(out.type == Int) cout<<out.data.dInt;
                    if(out.type == Float) cout<<out.data.dFloat;
                    if(out.type == Addr) cout<<out.data.dAddr<<"A";
                    if(out.type == Bool) cout<<((out.data.dBool)?"true":"false");
                }
                //...
                else  throw InvalidInstruction(ip);
                
        }
}

void VM::run(string filename)
{
 
	loadFile(filename);
    dataType srcData();
    execuProgram();
}