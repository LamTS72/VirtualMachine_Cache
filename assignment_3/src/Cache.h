#ifndef CACHE_H
#define CACHE_H

#include "main.h"


class ReplacementPolicy {
	protected:
	int count;
	Elem** arr;
	public:
	virtual void update(int addr) = 0;
	virtual void insert(Elem* e) = 0;
	virtual Elem* remove() = 0; 
	virtual void print() = 0;
	bool isFull() {return count == MAXSIZE;}
	bool isEmpty() {return count == 0;}
	virtual ~ReplacementPolicy(){}
};
class SearchEngine {
	public:
	virtual ~SearchEngine(){}
	virtual Elem* search(int key) = 0; // -1 if not found
	virtual void insert(Elem* elem) = 0;
	virtual	void deleteNode(Elem* elem) = 0;
	virtual void print() = 0;
};

class FIFO : public ReplacementPolicy {
	int front=-1;
    int rear=-1;
	public:
	FIFO(){
		count = 0; 
		arr = new Elem*[MAXSIZE];
	}
	~FIFO(){
		for (int i = 0 ; i < count; i++){
			if(arr[i]) delete arr[i];
		}
		if (arr) delete[] arr;
	}
	void insert(Elem* e){
		count++;
		if(front==-1 && rear ==-1){
        		front=rear=0;
      		}
      		else if(rear==MAXSIZE-1 && front != 0){
        		rear=0;
      		}
      		else{
        		rear++;
      		}
      		arr[rear]=e;
	}
	void update(int addr){}
	Elem* remove(){
		Elem*temp=NULL;
		count--;
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
	void print(){
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
};
class MRU : public ReplacementPolicy {
	public:
	MRU(){
		count = 0; 
		arr = new Elem*[MAXSIZE];
	}
	~MRU(){
		for (int i = 0 ; i < count; i++){
			if(arr[i]) delete arr[i];
		}
		if (arr) delete[] arr;
	}
	 void update(int addr) {
		 int i = 0;
		 for (i=0; i < count ; i++){
			 if (arr[i]->addr == addr) break;
		 } 
		 Elem* temp = arr[i]; 
		 for (i--; i>=0 ; i--){
			 arr[i+1] = arr[i];
		 }
		 arr[0] = temp;

	 };
	 void insert(Elem* e) {
		int i;
   		count++;
		for (i = count-1; i > 0; i--){
        	arr[i] = arr[i - 1];
		}
    	arr[0] = e;
	 };
	 Elem* remove() {
		 Elem* temp=arr[0];
		 int i;
		 count--;
		 for(i=0;i<count;i++){
			 arr[i]=arr[i+1];
		 }
		 return temp;
	 }; 
	 void print() {
		 for(int i=0;i<count;i++){
			 arr[i]->print();
		 }
	 };
};
class LRU: public MRU {
	public:
	void update(int addr) { 
		int i = 0;
		for (i=0; i < count ; i++){
			if (arr[i]->addr == addr) break;
		}
		Elem* temp = arr[i]; 
		for (i--; i>=0 ; i--){
			arr[i+1] = arr[i];
		}
		 arr[0] = temp;
	};
	void insert(Elem* e) {
		int i;
   		count++;
		for (i = count-1; i > 0; i--){
        	arr[i] = arr[i - 1];
		}
    	arr[0] = e;
	 };
	 Elem* remove() {
		Elem* temp=arr[count-1];
		count--;
		return temp;
	 }; 
	 void print() {
		  for(int i=0;i<count;i++){
			 arr[i]->print();
		 }
	 };
};

class LFU: public ReplacementPolicy {
	class LFUNode{
		Elem* ele;
		int freq;
		LFUNode(Elem* e){
			ele = e; 
			freq = 0;
		}
		~LFUNode(){delete ele;}
		friend class LFU;
	};
	int getParentInd(int ind){

		return (ind-1)/2;
	}
	int getLeftChild(int ind){
		return ind*2+1;
	}
	int getRightChild(int ind){
		return ind*2 +2;
	}
	void reHeapUp(int ind){
		if(ind == 0) return;
		int parentInd=getParentInd(ind);
		if(myArr[ind]->freq < myArr[parentInd]->freq){
			LFUNode* temp= myArr[ind];
			myArr[ind]=myArr[parentInd];
			myArr[parentInd]=temp;
			reHeapUp(parentInd);
		}
	}
	void reHeapDown(int ind){
		int left = getLeftChild(ind);
		int right = getRightChild(ind);
		int smallest = ind;
		
		if(right< count && myArr[right]->freq <= myArr[smallest]->freq){
			smallest=right;
		}
		if(left< count && myArr[left]->freq<=myArr[smallest]->freq){
			smallest=left;
		}
		if(smallest== ind) return;
		LFUNode*temp= myArr[ind];
		myArr[ind]=myArr[smallest];
		myArr[smallest]= temp;
		reHeapDown(smallest);
	}
	public:
	LFUNode** myArr; 
	LFU(){
		count = 0; 
		myArr = new LFUNode*[MAXSIZE];
	}
	~LFU(){
		for(int i = 0 ; i < count ; i++){
			delete myArr[i];
		}
		delete[] myArr;
	}
	void update(int addr) {
		int i = 0;
		for (i=0; i < count ; i++){
			if (myArr[i]->ele->addr == addr) break;
		}
		myArr[i]->freq++;
		reHeapDown(i);
	};
	
	void insert(Elem* e) {
		count++;
		LFUNode* temp = new LFUNode(e);
		myArr[count-1]=temp;
		reHeapUp(count-1);
		
	};
	
	Elem* remove() {
		Elem*temp=NULL;
		if(count==0) return NULL;
		temp = myArr[0]->ele;
		myArr[0]=myArr[count-1];
		count--;
		reHeapDown(0);
		return temp;
	}
	void print() {
		for(int i=0;i<count;i++){
			if(myArr[i]) myArr[i]->ele->print();
		}
	};
};

class DBHashing: public SearchEngine {
	int (*hash1)(int);
	int (*hash2)(int);
	Elem**arr;
	int size;
	public:
	DBHashing(int (*h1)(int),int (*h2)(int),int s){
		size =s;
		hash1=h1;
		hash2=h2;
		arr=new Elem* [size];
		for(int i=0;i<size;i++){
			arr[i] = nullptr;
		}
	}
	~DBHashing(){
	}
	int doublehashing(int key,int i){
		int H1=(*hash1)(key);
		int H2=(*hash2)(key);
		return (H1+i*H2)%size;
	}
	Elem* search(int key){
        int i = 0;
		Elem*temp=NULL;
        for(; i< size ; i++){
            if (arr[doublehashing(key,i)] != nullptr && arr[doublehashing(key,i)]->addr == key) {
				temp=arr[doublehashing(key,i)];
                return temp;
            }
        }
         return NULL;
	}; 

	void insert(Elem* elem){
		int i = 0;
		int key = elem->addr;
        for (;i<size ; i++){
            if (arr[doublehashing(key,i)] == nullptr) {
				arr[doublehashing(key,i)] = elem;
                return;
            }
        }
        return;

	};
	void deleteNode(Elem* elem) {
		int i = 0;
		int key = elem->addr;
        for ( ;  i < size ; i ++){
            if (arr[doublehashing(key,i)] != nullptr && arr[doublehashing(key,i)]->addr == key) {
				arr[doublehashing(key,i)] = nullptr;
                return;
            }
        }
         return;
	};
		
	void print() {
		cout<<"Prime memory:\n";
		for(int i=0;i<size;i++){
			if(arr[i]){
				arr[i]->print();
			}
		}
	};
};

class AVLTree { 
    public:
    Elem* lem; 
    AVLTree *left; 
    AVLTree *right; 
    int height; 
	friend class AVL;
    
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

class AVL : public SearchEngine {
	public:
		AVLTree *root;
		AVL() {
			root = NULL;
		}
		~AVL() {
			delete root;
		}
		Elem* search(int key) {
			return root->search(key,root);
		}
	 	void insert(Elem* elem) {
			root = root->insert(root, elem);
		}
		void deleteNode(Elem* elem){
			root = root->deleteNode(root , elem);
		}
	 	void print() {
			cout << "Print AVL in inorder:\n";
			root->printIn(root);
			cout << "Print AVL in preorder:\n";
			root->printPre(root);
		}
};






#endif