#ifndef CACHE_H
#define CACHE_H

#include "main.h"

class AVLTree { 
    public:
    Elem* lem; 
    AVLTree *left; 
    AVLTree *right; 
    int height; 
	friend class Cache;
    
		int distance(AVLTree *root) 
		{ 
			if (root == NULL) 
				return 0; 
			return root->height; 
		} 
		
		int max(int a, int b) 
		{ 
			return (a > b)? a : b; 
		} 
		
		AVLTree* newNode(Elem*lem) 
		{ 
			AVLTree* node = new AVLTree();
			node->lem = lem; 
			node->left = NULL; 
			node->right = NULL; 
			node->height = 1; 
			return(node); 
		} 
		

		AVLTree *rightRotate(AVLTree *y) 
		{ 
			AVLTree *x = y->left; 
			AVLTree *T2 = x->right; 
		
			x->right = y; 
			y->left = T2; 
		
			y->height = max(distance(y->left), distance(y->right)) + 1; 
			x->height = max(distance(x->left), distance(x->right)) + 1; 
			return x; 
		} 
		
		AVLTree *leftRotate(AVLTree *root) 
		{ 
			AVLTree *y = root->right; 
			AVLTree *T2 = y->left; 
		
			y->left = root; 
			root->right = T2; 
		
			root->height = max(distance(root->left),distance(root->right)) + 1; 
			y->height = max(distance(y->left), distance(y->right)) + 1; 
		
			return y; 
		} 
		

		int getBalance(AVLTree *root) 
		{ 
			if (root == NULL) 
				return 0; 
			return distance(root->left) - distance(root->right); 
		} 
		
		AVLTree* insert(AVLTree* node, Elem*lem) 
		{ 
			
			if (node == NULL) 
				return(newNode(lem)); 
		
			if (lem->addr < node->lem->addr) 
				node->left = insert(node->left, lem); 
			else if (lem->addr > node->lem->addr) 
				node->right = insert(node->right, lem); 
			else 
				return node; 
		
			node->height = 1 + max(distance(node->left), distance(node->right)); 
		
		
			int balance = getBalance(node); 
		
			
			if (balance > 1 && lem->addr < node->left->lem->addr) 
				return rightRotate(node); 
		
			if (balance < -1 && lem->addr > node->right->lem->addr) 
				return leftRotate(node); 
		
			 
			if (balance > 1 && lem->addr > node->left->lem->addr) 
			{ 
				node->left = leftRotate(node->left); 
				return rightRotate(node); 
			} 
		
		
			if (balance < -1 && lem->addr < node->right->lem->addr) 
			{ 
				node->right = rightRotate(node->right); 
				return leftRotate(node); 
			} 
		
			
			return node; 
		} 
		
		AVLTree * minValueNode(AVLTree* node) 
		{ 
			AVLTree* current = node; 
		
			
			while (current->left != NULL) 
				current = current->left; 
		
			return current; 
		} 
		
		AVLTree* deleteNode(AVLTree* root, Elem*lem) 
		{ 
			
			if (root == NULL) 
				return root; 
		
			if ( lem->addr < root->lem->addr ) 
				root->left = deleteNode(root->left, lem); 
		
			else if( lem->addr > root->lem->addr ) 
				root->right = deleteNode(root->right, lem); 
			else
			{ 
				if( (root->left == NULL) || (root->right == NULL) ) 
				{ 
					AVLTree *temp = root->left ? root->left :  root->right; 
		
				
					if (temp == NULL) 
					{ 
						temp = root; 
						root = NULL; 
					} 
					else 
					*root = *temp; 
					delete temp; 
				} 
				else
				{ 
					AVLTree* temp = minValueNode(root->right); 
					root->lem = temp->lem; 
					root->right = deleteNode(root->right, temp->lem); 
				} 
			} 
		
			if (root == NULL) 
			return root; 
			root->height = 1 + max(distance(root->left),distance(root->right)); 
		
			int balance = getBalance(root); 
		
			if (balance > 1 && getBalance(root->left) >= 0) 
				return rightRotate(root); 
		
		
			if (balance > 1 && getBalance(root->left) < 0) 
			{ 
				root->left = leftRotate(root->left); 
				return rightRotate(root); 
			} 
		
			if (balance < -1 && getBalance(root->right) <= 0) 
				return leftRotate(root); 
			if (balance < -1 && getBalance(root->right) > 0) 
			{ 
				root->right = rightRotate(root->right); 
				return leftRotate(root); 
			} 
		
			return root; 
		} 
		Elem* search(int ad,AVLTree* root){
			if(root==NULL) return NULL;
			else{
				AVLTree*temp=root;
				while(temp!=NULL){
					if(ad==temp->lem->addr){
						return temp->lem;
					}
					else if(ad<temp->lem->addr){
						temp=temp->left;
					}
					else{
						temp=temp->right;
					}
				}
				return NULL;
			}
		}
		
		void printIn(AVLTree* node)
		{
			if (node == NULL)
				return;
			else{
			printIn(node->left);
			node->lem->print();
			printIn(node->right);
			}
		}

		void printPre(AVLTree* node)
		{
			if (node == NULL)
				return;
			else{
			node->lem->print();
			printPre(node->left);
			printPre(node->right);
			}
		}

};

class Cache:public AVLTree{
		Elem** arr;
		int p;
		int front=-1;
    	int rear=-1;
    	AVLTree *root=NULL;
	public:
		Cache(int s) {
			arr = new Elem*[s]; 
			p = 0;
		}
		~Cache() {
			delete[] arr;
		}
		void enQueue(Elem* a){
      		if(front==-1 && rear ==-1){
        		front=rear=0;
      		}
      		else if(rear==MAXSIZE-1 && front != 0){
        		rear=0;
      		}
      		else{
        		rear++;
      		}
      		arr[rear]=a;
    	}
    	Elem* deQueue(){
      		Elem*temp;
     		if(front==-1 && rear == -1) return NULL;
     		else{
       			temp=arr[front];
       		if(front==rear){
         		front=-1;
        		rear=-1;
      		}
       		else if(front == MAXSIZE-1){
        		front =0;
        	}
        	else {
        	    front++;
        	}
       		return temp;
      		}
    	}

   		 void display(){
      		int i;
     		if(front<=rear){
       			for(i=front;i<=rear;i++){
         	 		arr[i]->print();
        		}
      		}
      		else{
        		i = front;
        		while(i<MAXSIZE){
          			arr[i]->print();
          			i++;
        		}
        		i=0;
        		while(i<=rear){
          			arr[i]->print();
          			i++;
        		}
      		}
    	}
		Data* read(int addr);
		Elem* put(int addr, Data* cont);
		Elem* write(int addr, Data* cont);
		void print();
		void preOrder();
		void inOrder();	
};


#endif