//計算矩陣的行列式，
//參考CSDN論壇

#include<stdio.h>
#include<math.h>

int main()
{
	int n=0;
	int i,j=0;
	int k,row,line=0;
	int swarpNumber=0;
	double matrix[10][10],temp,beishu;
	long long a,matrixModulo;
	long long determinant=1;
	long long result;
	long long modulo=1000000007;

	printf("The number of rows: \n");
	scanf("%d",&n);
	printf("The matrix: \n");

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%lf",&matrix[i][j]);
		}
	}

	for(k=0;k<n-1;k++)
	{
		 if(matrix[k][k]==0)
		 {    
			  for(row=n-1;row>k;row--)
			  {
				if(matrix[row][k]!=0)
				{
					 for(line=0;line<n;line++)
					 {
						  temp=matrix[k][line];
						  matrix[k][line]=matrix[row][line];
						  matrix[row][line]=temp;
					 }
					 swarpNumber++;
					 break;
				}
			  }
		 }
		 
		 for(i=k+1;i<n;i++)
		 {
			  beishu=matrix[i][k]/matrix[k][k];
			  for(j=k;j<n;j++)
				matrix[i][j]=matrix[i][j]-matrix[k][j]*beishu;
		 } 

		 //printf("\n");
	}

	for(i=0;i<n;i++)
	{
		
			
			//determinant*=matrix[i][j];

			matrixModulo=matrix[i][i]- modulo*( floor(matrix[i][i]/modulo) );
			determinant=determinant*matrixModulo;
			a=floor( ((double)determinant) /modulo);
			determinant=determinant- modulo*a;
		
	}
	
	determinant=pow(-1.0,swarpNumber)*determinant;
	//printf("%lf\n",determinant);

	result=determinant-	modulo*( floor((double)determinant/modulo) );
	printf("%I64d\n",result);

	getchar(); getchar(); 
	return 0;
}

