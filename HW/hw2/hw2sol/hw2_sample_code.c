#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int K; //max number of nodes in a block

struct Node{
    struct Node* next;
    int value;
};

struct Block{
    struct Block* next;
    struct Node* head;
    int nodeCount;
};

struct Block* Bhead;

//create an empty block
struct Block* newBlock(){
    struct Block* b=(struct Block*)malloc(sizeof(struct Block));
    b->next=0;
    b->head=0;
    b->nodeCount=0;
    return b;
}

//create a node 
struct Node* newNode(int value){
    struct Node* b=(struct Node*)malloc(sizeof(struct Node));
    b->next=0;
    b->value=value;
    return b;
}


void find(int k,struct Block **fBlock,struct Node **fNode){
    //find the block 
    int j=(k+K-1)/K; //k-th node is in the j-th block 
    struct Block* p=Bhead;
    while(--j){
	p=p->next; 
    }
    *fBlock=p;
    
    //find the node
    struct Node* q=p->head;
    k=k%K;
    if(k==0) k=K;
    k=p->nodeCount+1-k;
    while(k--){
	q=q->next;
    }
    *fNode=q;
}

//start shift operation from block *p 
void shift(struct Block *A){
    struct Block *B;
    struct Node* temp;
    while(A->nodeCount>K){ //if this block still have to shift
	if(A->next==0){ //reach the end. A little different
	    A->next=newBlock();
	    B=A->next;
	    temp=A->head->next;
	    A->head->next=A->head->next->next;
	    B->head=temp;
	    temp->next=temp;
	    A->nodeCount--;
	    B->nodeCount++;
	}else{	// same as hw2 page 4
	    B=A->next;
	    temp=A->head->next;			//1
	    A->head->next=A->head->next->next;	//2
	    temp->next=B->head->next;		//3
	    B->head->next=temp;			//4
	    B->head=temp;			//5
	    A->nodeCount--;			
	    B->nodeCount++;
	}
	A=B;
    }
}

void insert(int k,int x){
    struct Node *p,*q;
    struct Block *r;
    if(!Bhead){ //initial, first node and block
	Bhead=newBlock();
	Bhead->head=newNode(x);
	Bhead->head->next=Bhead->head;
	Bhead->nodeCount++;
    }else{
	if(k==0){ //special case for k=0. 
	    p=Bhead->head;
	    q=p->next;
	    p->next=newNode(x);
	    p->next->next=q;
	    Bhead->head=p->next;
	    Bhead->nodeCount++;
	    shift(Bhead);
	}else{
	    find(k,&r,&p);
	    q=p;
	    while(q->next!=p) q=q->next;
	    q->next=newNode(x);
	    q->next->next=p;
	    r->nodeCount++;
	    shift(r);
	}
    }
}

int query(int k){
    struct Node *p;
    struct Block *q;
    find(k,&q,&p);
    return p->value;
}

int main(){
    int tt=clock();
    int m,i,k,x;
    char cmd[10];
    scanf("%d",&m);
    K=(int)(sqrt(m-0.001))+1;
    for( i=0; i<m; i++ ){
	scanf("%s",cmd);
	if(strcmp(cmd,"insert")==0){
	    scanf("%d %d",&k,&x);
	    insert(k,x);
	}else if(strcmp(cmd,"query")==0){
	    scanf("%d",&k);
	    printf("%d\n",query(k));
	}else{
	    fprintf(stderr,"error case\n");
	}
    }
    return 0;
}
