//進行迷宮導航
//參考CSDN


#include<stdio.h>
#include<math.h>


long long determinant3(long long a1,long long a2,long long a3,
                       long long b1,long long b2,long long b3,
					   long long c1,long long c2,long long c3);

long long valueMatrix[1000][1000];
long long hintMatrix[1000][1000];
int repeatMatrix[1000][1000];

int main()
{

	int m,n=0;
	int x1,y1=0;
	int i,j=0;
	int x,y=0;
	int k=0;

	printf("Maze entry coordinates:\n");
	scanf("%d %d",&x1,&y1);
	printf("Numbers of rows and columns of the matrices:\n");
	scanf("%d %d",&m,&n);

	printf("The value matrix:\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%I64d",&valueMatrix[i][j]);
		}
	}
	printf("The hint matrix:\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%I64d",&hintMatrix[i][j]);
		}
	}

	//重複矩陣初始化
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			repeatMatrix[i][j]=0;
		}
	}

	//開始走迷宮
	x=x1-1;
	y=y1-1;
	printf("%d %d",x+1,y+1);

	for(k=0;;k++)
	{
		if(x<=0 || x>=m-1)
			break;
		if(y<=0 || y>=n-1)
			break;

		repeatMatrix[x][y]=1;

		if(determinant3(hintMatrix[x-1][y-1],hintMatrix[x-1][y],hintMatrix[x-1][y+1],
			            hintMatrix[x][y-1],hintMatrix[x][y],hintMatrix[x][y+1],
						hintMatrix[x+1][y-1],hintMatrix[x+1][y],hintMatrix[x+1][y+1])==valueMatrix[x][y+1] && repeatMatrix[x][y+1]==0)
		{
			x=x;
		    y=y+1;
			printf("\n%d %d",x+1,y+1);
		}

        else if(determinant3(hintMatrix[x-1][y-1],hintMatrix[x-1][y],hintMatrix[x-1][y+1],
							 hintMatrix[x][y-1],hintMatrix[x][y],hintMatrix[x][y+1],
							 hintMatrix[x+1][y-1],hintMatrix[x+1][y],hintMatrix[x+1][y+1])==valueMatrix[x+1][y] && repeatMatrix[x+1][y]==0)
		{
				x=x+1;
				y=y;
                printf("\n%d %d",x+1,y+1);
		}		

		else if(determinant3(hintMatrix[x-1][y-1],hintMatrix[x-1][y],hintMatrix[x-1][y+1],
			                 hintMatrix[x][y-1],hintMatrix[x][y],hintMatrix[x][y+1],
							 hintMatrix[x+1][y-1],hintMatrix[x+1][y],hintMatrix[x+1][y+1])==valueMatrix[x][y-1] && repeatMatrix[x][y-1]==0)
		{	    
				x=x;
		        y=y-1;
				printf("\n%d %d",x+1,y+1);
		}

		else if(determinant3(hintMatrix[x-1][y-1],hintMatrix[x-1][y],hintMatrix[x-1][y+1],
			                 hintMatrix[x][y-1],hintMatrix[x][y],hintMatrix[x][y+1],
							 hintMatrix[x+1][y-1],hintMatrix[x+1][y],hintMatrix[x+1][y+1])==valueMatrix[x-1][y] && repeatMatrix[x-1][y]==0)
		{
				x=x-1;
		        y=y;
                printf("\n%d %d",x+1,y+1);
		}

		else
			break;

	}


	//printf("\n%d",k);

	getchar(); getchar(); 
	return 0;

}

long long determinant3(long long a1,long long a2,long long a3,
                       long long b1,long long b2,long long b3,
					   long long c1,long long c2,long long c3)
{
	long long det;
	det=a1*b2*c3+a2*b3*c1+a3*b1*c2-a3*b2*c1-a2*b1*c3-a1*b3*c2;

	return det;
}