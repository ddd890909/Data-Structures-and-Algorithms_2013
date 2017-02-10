//計算A經過固定點到達B的最短距離
//ddd

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <time.h>

using namespace std;
#define N 400001
#define M 600001
#define Q 400001
#define infinity (__int64)0x7fffffffffffffff

typedef struct adjListNode
{
	long long int adjacency;
	struct adjListNode *next;
	long long int weight;
}adjListNode;

adjListNode adjList[N];
adjListNode adjListReverse[N];

typedef struct heapNode
{
	long long int vertex;
	long long int distance;
}heapNode;

heapNode heap[M];
bool hash[N];
long long int dA1[N],d1B[N];
long long int heapLength,n,m;

void heapInsert(heapNode newHeapNode)  
{
	long long int u=++heapLength;
	while(u>1 && heap[u>>1].distance >newHeapNode.distance )
	{
		heap[u]=heap[u>>1];
		u>>=1;
	}
	heap[u]=newHeapNode;
}

heapNode heapPop()  
{
	heapNode first=heap[1];
	heapNode last=heap[heapLength--];
	long long int u=1;
	long long int v;
	while(2*u<=heapLength)
	{
		v=u<<1;
		if(v+1<=heapLength && heap[v+1].distance < heap[v].distance )
			v++;
		if(heap[v].distance < last.distance )
			heap[u]=heap[v];
		else
			break;
		u=v;
	}
	heap[u]=last;
	return first;
}

void adjListInsert(long long int a,long long int b,long long int w)
{
	adjListNode *p,*newAdjListNode;
	p=&adjList[a];
	while(p->next !=NULL)
		p=p->next;
	newAdjListNode=(struct adjListNode*)malloc(sizeof(struct adjListNode)); //new adjListNode;
	newAdjListNode->adjacency =b;
	newAdjListNode->next =NULL;
	newAdjListNode->weight=w;
	p->next =newAdjListNode;
}

void adjListInsertReverse(long long int a,long long int b,long long int w)
{
	adjListNode *p,*newAdjListNode;
	p=&adjListReverse[a];
	while(p->next !=NULL)
		p=p->next;
	newAdjListNode=(struct adjListNode*)malloc(sizeof(struct adjListNode)); //new adjListNode;
	newAdjListNode->adjacency =b;
	newAdjListNode->next =NULL;
	newAdjListNode->weight=w;
	p->next =newAdjListNode;
}

void Dijkstra(adjListNode list[],long long int d[])
{
	heapNode min,newHeapNode;
	adjListNode *p;
	newHeapNode.vertex =1;
	newHeapNode.distance =0;
	d[1]=0;
	heapInsert(newHeapNode);
	while(heapLength)
	{
		min=heapPop ();
		//if(min.vertex ==n)
		//	return min.distance;
		if(hash[min.vertex])
			continue;
		hash[min.vertex]=true;
		p=list[min.vertex].next;
		while(p!=NULL)
		{
			if(!hash[p->adjacency])
			{
				newHeapNode.vertex=p->adjacency;
				newHeapNode.distance=min.distance + p->weight;
				if(newHeapNode.distance<d[newHeapNode.vertex])
				{
					d[newHeapNode.vertex]=newHeapNode.distance;
					heapInsert(newHeapNode);
				}
			}
			p=p->next;
		}
	}
}

int main()
{
	//FILE *stream;
	//freopen_s(&stream,"D:\\course\\DSA\\HW\\hw4\\dos_format\\sample-large.in","r",stdin);
	//freopen_s(&stream,"D:\\course\\DSA\\HW\\hw4\\dos_format\\result-large.out","w",stdout);
	
	long long int i,j,a,b,w,q;
	scanf_s("%lld%lld",&n,&m);
	for(i=1;i<=n;i++)
	{
		adjList[i].next=NULL;
		adjListReverse[i].next=NULL;
	}

	while(m--)
	{
		scanf_s("%lld%lld%lld",&a,&b,&w);
		adjListInsert(a,b,w);
		adjListInsertReverse(b,a,w);
	}

	//clock_t start,finish;
	//double duration=0; 
    //start = clock(); 

	//a to 1
	for(i=1,heapLength=0;i<=n;i++)
	{	
		hash[i]=false;
		dA1[i]=infinity;
	}
	Dijkstra(adjListReverse,dA1);

	//1 to b
	for(i=1,heapLength=0;i<=n;i++)
	{	
		hash[i]=false;
		d1B[i]=infinity;
	}
	Dijkstra(adjList,d1B);  
	
	scanf_s("%lld",&q);
	while(q--)
	{
		scanf_s("%lld%lld",&a,&b);
		if(dA1[a]==infinity || d1B[b]==infinity)
			printf("%lld\n",(long long int)-1);
		else
			printf("%lld\n",dA1[a]+d1B[b]);
	}

	//finish = clock(); 
	//duration = (double)(finish - start) / CLOCKS_PER_SEC; 
    //printf( "%f seconds\n", duration ); 
}
