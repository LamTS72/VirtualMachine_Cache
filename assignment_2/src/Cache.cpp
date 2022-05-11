#include "main.h"

Data* Cache::read(int addr) {
	Elem* temp=search(addr,root);
    if(temp !=NULL) { 
        return temp->data;
    }
    else return NULL;
}
Elem* Cache::put(int addr, Data* cont) {
	Elem*temp=NULL;
    if(front==rear+1 || (front ==0 && rear ==MAXSIZE -1)){
        temp=deQueue();
        root=deleteNode(root,temp);
    }
    Elem* p = new Elem(addr,cont,true);
        enQueue(p);
        root=insert(root,p);
        return temp;
}
Elem* Cache::write(int addr, Data* cont) {
    Elem*temp=search(addr,root);
    if(temp){
        delete temp->data;
        temp->data=cont;
        temp->sync=false;
        return NULL;
    }
    else{
        Elem*temp=NULL;
        if(front==rear+1 ||(front ==0 && rear ==MAXSIZE -1)){
            temp=deQueue();
            root=deleteNode(root,temp);
        }
        Elem *wr=new Elem(addr,cont,false);
        enQueue(wr);
        root=insert(root,wr);
        return temp;
    }
}
void Cache::print() {
	display();
}
void Cache::preOrder() {
	printPre(root);
}
void Cache::inOrder() {
     printIn(root);
}
