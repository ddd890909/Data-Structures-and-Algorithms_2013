//longest common prefix
//ddd

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#define max(a,b) ( (a>b)?a:b )
#define Number 11
#define LengthS 200001
#define Q 400001
#define Base 26
#define Modulo 2503 //29989

int problemNumber;
int n;
int lengthS;
char *S;
int *ts;
int queryNumber;
int q;
int a,b;
//char A[LengthS];
//char B[LengthS];
int as,bs;

void RabinKarpHash(char *T,int d,int q,int *ts)
{
	int lengthT=strlen(T);
    int i;
    ts[0]=(T[0]-'a')%q;
	for(i=1;i<=lengthT;i++)
	{  
        ts[i]=( d*ts[i-1]%q + T[i]-'a' )%q; 
    }
	return;
}

int powModulo(double base,int power,int modulo)
{
	int pw = 1;
    while (power > 0) 
	{
        if (power & 1)        // n & 1 等价于 (n % 2) == 1
            pw = (int)(pw*base)%modulo;
        base = (int)(base*base)%modulo;
        power >>= 1;        // n >>= 1 等价于 n /= 2
    }
    return pw;
}

int main()
{
	//FILE *stream;
	//freopen_s(&stream,"D:\\course\\DSA\\HW\\hw6\\dos_format\\sample-large.in","r",stdin);
	//freopen_s(&stream,"D:\\course\\DSA\\HW\\hw6\\dos_format\\result-large.out","w",stdout);	
	
	scanf("%d",&problemNumber);
	for(n=1;n<=problemNumber;n++)
	{
		scanf("%d",&lengthS);
		S=(char *)malloc(lengthS * sizeof(char));
		ts = (int *) malloc( (lengthS+1) * sizeof(int)); 
		scanf("%s",S);
		RabinKarpHash(S,Base,Modulo,ts);
		//printf("ddd");

		scanf("%d",&queryNumber);
		for(q=1;q<=queryNumber;q++)
		{
			scanf("%d %d",&a,&b);
			//strcpy(A,&S[a-1]);
			//strcpy(B,&S[b-1]);
			
			int L=max(a,b)-1;
			int R=lengthS-1;
			int K=0;
			while(L<=R)
			{
				K=L+( (R-L)/2 );
				if(a!=1)
				{
					if( ts[K-max(b-a,0)] >= (ts[a-2]*powModulo( (double)Base , K-max(b-a,0)-a+2 ,Modulo ) %Modulo) )
						as=ts[K-max(b-a,0)] - (ts[a-2]*powModulo( (double)Base , K-max(b-a,0)-a+2 ,Modulo ) %Modulo);
					else
						as=ts[K-max(b-a,0)] - (ts[a-2]*powModulo( (double)Base , K-max(b-a,0)-a+2 ,Modulo ) %Modulo) + Modulo;
				}
				else
					as=ts[K-max(b-a,0)];
				
				if(b!=1)
				{
					if( ts[K-max(a-b,0)]>= (ts[b-2]* powModulo( (double)Base,K-max(a-b,0)-b+2,Modulo ) %Modulo) )
						bs=ts[K-max(a-b,0)]-(ts[b-2]* powModulo( (double)Base,K-max(a-b,0)-b+2,Modulo ) %Modulo);
					else
						bs=ts[K-max(a-b,0)]-(ts[b-2]* powModulo( (double)Base,K-max(a-b,0)-b+2,Modulo ) %Modulo) + Modulo;
				}
				else
					bs=ts[K-max(a-b,0)];

				if(as==bs)
				{
					if( !strncmp(S+a-1,S+b-1,K-max(a,b)+2) )
						L=K+1;
					else
						R=K-1;
				}
				else
				{
					R=K-1;
				}
			}

			printf("%d\n",R-max(a,b)+2); 
		}
	}
 
	return 0;  
	
	//clock_t start,finish;
	//double duration=0; 
    //start = clock(); 
	
	//finish = clock(); 
	//duration = (double)(finish - start) / CLOCKS_PER_SEC; 
    //printf( "%f seconds\n", duration ); 
}