#ifndef VM_H
#define VM_H

#include "main.h"

#define MAX_SIZE 1000;
        
static const int vnMemory=65536;
  
enum Type {None,Int,Float, Addr, Bool};
union Data{

        int dInt;
        float dFloat;
        int dAddr;
        bool dBool;
};


class VM
{  
    public:
      struct dataType{
        Type type = None;
        Data data;
        
        void operator=(const dataType & realdata) {
            this->type = realdata.type;
            this->data = realdata.data;
        }

        void operator+=(const dataType & realdata){
            if (this->type==Float || realdata.type==Float) {
                float res=0;
                if (this->type==Float) res+=this->data.dFloat;
                else res+=this->data.dInt;
                if (realdata.type==Float) res+=realdata.data.dFloat;
                else res+=realdata.data.dInt;

                this->type=Float;
                this->data.dFloat=res;
            }
            else {
                this->type=Int;
                this->data.dInt+=realdata.data.dInt;
            }
        }
    
       
        void operator-=(const dataType & realdata){
            if (this->type==Float || realdata.type==Float) {
                float res=0;
                if (this->type==Float) res-=this->data.dFloat;
                else res-=this->data.dInt;
                if (realdata.type==Float) res-=realdata.data.dFloat;
                else res-=realdata.data.dInt;

                this->type=Float;
                this->data.dFloat=res;
            }
            else {
                this->type=Int;
                this->data.dInt-=realdata.data.dInt;
            }
        }
         void operator*=(const dataType & realdata){
            if (this->type==Float || realdata.type==Float) {
                float res=0;
                if (this->type==Float) res*=this->data.dFloat;
                else res*=this->data.dInt;
                if (realdata.type==Float) res*=realdata.data.dFloat;
                else res*=realdata.data.dInt;

                this->type=Float;
                this->data.dFloat=res;
            }
            else {
                this->type=Int;
                this->data.dInt*=realdata.data.dInt;
            }
        }
        void operator/=(const dataType & realdata){
            if (this->type==Float || realdata.type==Float) {
                float res=0;
                if (this->type==Float) res/=this->data.dFloat;
                else res/=this->data.dInt;
                if (realdata.type==Float) res/=realdata.data.dFloat;
                else res/=realdata.data.dInt;

                this->type=Float;
                this->data.dFloat=res;
            }
            else {
                this->type=Int;
                this->data.dInt/=realdata.data.dInt;
            }
        }
        bool operator==(const dataType & realdata){
            bool res=false;
            if(this->type == realdata.type){
                if(this->type == Int) {
                    if(this->data.dInt == realdata.data.dInt) res=true;
                    else res=false;
                }
                else if(this->type == Float) {
                    if(this->data.dFloat == realdata.data.dFloat) res=true;
                    else res=false;
                }
                else if(this->type == Bool) {
                    if(this->data.dBool == realdata.data.dBool) res=true;
                    else res=false;
                }
                return res;
            }
            else 
                return false;
           
        }
        bool operator!=(const dataType & realdata){
            bool res=false;
            if(this->type == realdata.type){
                if(this->type == Int) {
                    if(this->data.dInt != realdata.data.dInt) res=true;
                    else res=false;
                }
                else if(this->type == Float) {
                    if(this->data.dFloat != realdata.data.dFloat) res=true;
                    else res=false;
                }
                else if(this->type == Bool) {
                    if(this->data.dBool != realdata.data.dBool) res=true;
                    else res=false;
                }
                return res;
            }
            else 
                return false;
          
        }
        bool operator<(const dataType & realdata){
            bool res=false;
            if(this->type == realdata.type){
                if(this->type == Int) {
                    if(this->data.dInt < realdata.data.dInt) res=true;
                    else res=false;
                }
                else if(this->type == Float) {
                    if(this->data.dFloat < realdata.data.dFloat) res=true;
                    else res=false;
                }
                else if(this->type == Bool) {
                    if(this->data.dBool < realdata.data.dBool) res=true;
                    else res=false;
                }
                return res;
            }
            else 
                return false;
          
        }
        bool operator<=(const dataType & realdata){
            bool res=false;
            if(this->type == realdata.type){
                if(this->type == Int) {
                    if(this->data.dInt <= realdata.data.dInt) res=true;
                    else res=false;
                }
                else if(this->type == Float) {
                    if(this->data.dFloat <= realdata.data.dFloat) res=true;
                    else res=false;
                }
                else if(this->type == Bool) {
                    if(this->data.dBool <= realdata.data.dBool) res=true;
                    else res=false;
                }
                return res;
            }
            else 
                return false;
            
        }
        bool operator>(const dataType & realdata){
            bool res=false;
            if(this->type == realdata.type){
                if(this->type == Int) {
                    if(this->data.dInt > realdata.data.dInt) res=true;
                    else res=false;
                }
                else if(this->type == Float) {
                    if(this->data.dFloat > realdata.data.dFloat) res=true;
                    else res=false;
                }
                else if(this->type == Bool) {
                    if(this->data.dBool > realdata.data.dBool) res=true;
                    else res=false;
                }
               return res;
            }
            else 
                return false;
                
        }
          
        bool operator>=(const dataType & realdata){
            bool res=false;
            if(this->type == realdata.type){
                if(this->type == Int) {
                    if(this->data.dInt >= realdata.data.dInt) res=true;
                    else res=false;
                }
                else if(this->type == Float) {
                    if(this->data.dFloat >= realdata.data.dFloat) res=true;
                    else res=false;
                }
                else if(this->type == Bool) {
                    if(this->data.dBool >= realdata.data.dBool) res=true;
                    else res=false;
                }
               return res;
            }
            else 
                return false;
        }
    };  //...
      
    int IP=0;
    int countINS=0;
    dataType R[15];
    dataType static_Mem[vnMemory];
    vector<vector<string>> readINS;
    vector<int> Stack;
    void loadFile(string filename);
    dataType srcData(string src);
    void execuProgram();
    void run(string filename);
};




#endif
