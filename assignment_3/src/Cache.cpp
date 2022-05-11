#include "main.h"
Cache::Cache(SearchEngine* s,ReplacementPolicy* r):rp(r),s_engine(s) {}
Cache::~Cache(){
	delete rp;
	delete s_engine;
}
Data* Cache::read(int addr) {
    Elem* temp = s_engine->search(addr);
    if(temp !=NULL) {
        rp->update(temp->addr);
        return temp->data;
    }
    else return NULL;
}
Elem* Cache::put(int addr, Data* cont) {
    
    Elem*temp=NULL;
    if(rp->isFull()){
        
        temp=rp->remove();
        s_engine->deleteNode(temp);
    }
    
   
    Elem* p = new Elem(addr,cont,true);
        rp->insert(p);
        s_engine->insert(p);
        return temp;

    
}
Elem* Cache::write(int addr, Data* cont) {
    Elem* temp = s_engine->search(addr);
    if(temp){
        rp->update(temp->addr);
        delete temp->data;
        temp->data=cont;
        temp->sync=false;
        return NULL;
    }
    else{
        Elem*temp=NULL;
        if(rp->isFull()){
            temp=rp->remove();
            s_engine->deleteNode(temp);
        }
        Elem *wr=new Elem(addr,cont,false);
        rp->insert(wr);
        s_engine->insert(wr);
        return temp;
    }
}
void Cache::printRP() {
    rp->print();
}
void Cache::printSE() {
    s_engine->print();
}
