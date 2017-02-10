//計算MST
//ddd

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#define T 11
#define N 100001
#define X 1000000001
#define Y 1000000001

typedef struct Vertex
{
	long long int id;
	long long int x;
	long long int y;
}Vertex;

int CompX ( const void* a, const void* b ) 
{
	if ( (*(Vertex*)a).x == (*(Vertex*)b).x ) 
	{
		return (*(Vertex*)a).y - (*(Vertex*)b).y;
	}
	else 
	{
		return (*(Vertex*)a).x - (*(Vertex*)b).x;
	}
}

int CompY ( const void* a, const void* b ) 
{
	if ( (*(Vertex*)a).y == (*(Vertex*)b).y ) 
	{
		return (*(Vertex*)a).x - (*(Vertex*)b).x;
	}
	else 
	{
		return (*(Vertex*)a).y - (*(Vertex*)b).y;
	}
}

typedef struct Edge
{
	long long int begin;
	long long int end;
	long long int weight;
}Edge;

int CompEdge ( const void* a, const void* b ) 
{
	return (*(Edge*)a).weight - (*(Edge*)b).weight;
}

typedef struct MGraph
{
	Vertex vertexX[N];
	Vertex vertexY[N];
	Edge edge[N*4];
	long long int vexNum,edgeNum;
}MGraph;

long long int t,n,x,y,cost;
long long int parent[N];
long long int stack[N];

void CreatGraph(MGraph *);
void MiniSpanTree(MGraph*);
long long int FindRoot(long long int);

void CreatGraph(MGraph *G)//建圖
{
	long long int i,j;
	scanf_s("%lld",&n);
	G->vexNum =n;
	for(i=0;i<=G->vexNum-1;i++) //記錄vertex
	{
		scanf_s("%lld %lld",&x,&y);
		G->vertexX[i].id=i;
		G->vertexX[i].x=x;
		G->vertexX[i].y=y;
		G->vertexY[i].id=i;
		G->vertexY[i].x=x;
		G->vertexY[i].y=y;
	}
	
	//for(i=0;i<=G->vexNum-1;i++)
	//{
	//	printf("%lld %lld\n",G->vertexX[i].x,G->vertexX[i].y);
	//}

	qsort(G->vertexX,G->vexNum,sizeof(Vertex),CompX); //按x的大小對vertex排序
	qsort(G->vertexY,G->vexNum,sizeof(Vertex),CompY); //按y的大小對vertex排序

	//for(i=0;i<=G->vexNum-1;i++)
	//{
	//	printf("%lld %lld\n",G->vertexY[i].x,G->vertexY[i].y);
	//}

	j=0;
	for(i=0;i<=G->vexNum-2;i++) //找出邊
	{
		if(G->vertexX[i].x==G->vertexX[i+1].x)
		{
			G->edge[j].begin=G->vertexX[i].id;
			G->edge[j].end=G->vertexX[i+1].id;
			G->edge[j].weight=G->vertexX[i+1].y-G->vertexX[i].y;
			j++;
		}
		if(G->vertexY[i].y==G->vertexY[i+1].y)
		{
			G->edge[j].begin=G->vertexY[i].id;
			G->edge[j].end=G->vertexY[i+1].id;
			G->edge[j].weight=G->vertexY[i+1].x-G->vertexY[i].x;
			j++;
		}
	}
	G->edgeNum=j;

	//for(j=0;j<=G->edgeNum-1;j++)
	//{
	//	printf("%lld %lld %lld\n",G->edge[j].begin,G->edge[j].end,G->edge[j].weight);
	//}
}

long long int FindRoot( long long int f) //找set的root
{
	long long int sp = 0;
	while ( parent[f] != f ) 
	{
		stack[sp++] = f;
		f = parent[f];
	}
	while ( sp > 0 ) 
	{
		parent[stack[--sp]] = f;
	}
	return f;
}

void MiniSpanTree(MGraph *G)
{
	long long int i,j,a,b;
	

	qsort(G->edge,G->edgeNum,sizeof(Edge),CompEdge);

	//for(j=0;j<=G->edgeNum-1;j++)
	//{
	//	printf("%lld %lld %lld\n",G->edge[j].begin,G->edge[j].end,G->edge[j].weight);
	//}

    for (i = 0; i <= G->vexNum-1; i++) 
    {
		parent[i] = i;
	}
	
	cost=0;
	for (j = 0; j <= G->edgeNum-1; j++) //判斷回路
	{
		a = FindRoot( G->edge[j].begin);
		b = FindRoot( G->edge[j].end);
		if (a != b)
		{
			parent[b] = a;
			//printf("<<%lld, %lld>> %lld\n", G->edge[j].begin, G->edge[j].end, G->edge[j].weight);
			cost=cost+G->edge[j].weight;
		}
	}
	
	a = FindRoot(0);
	for (i = 1; i <= G->vexNum-1; i++) //檢查是不是只有一個set
    {
		b = FindRoot(i);
		if(a!=b)
		{
			cost=-1;
			break;
		}
	}	
	printf("%lld\n",cost);
}

int main()
{
	//FILE *stream;
	//freopen_s(&stream,"D:\\course\\DSA\\HW\\hw5\\dos_format\\sample-large.in","r",stdin);
	//freopen_s(&stream,"D:\\course\\DSA\\HW\\hw5\\dos_format\\result-large.out","w",stdout);	

	scanf_s("%lld",&t);
	while(t!=0)
	{
		MGraph *G;
		G = (MGraph*)malloc(sizeof(MGraph));
		if (G == NULL)
		{
			//printf("memory allcation failed,goodbye");
			exit(1);
		}

		CreatGraph(G);
		MiniSpanTree(G);

		free(G);
		t--;
	}
	return 0;

	//clock_t start,finish;
	//double duration=0; 
    //start = clock(); 
	
	//finish = clock(); 
	//duration = (double)(finish - start) / CLOCKS_PER_SEC; 
    //printf( "%f seconds\n", duration ); 
}
