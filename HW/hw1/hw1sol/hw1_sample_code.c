/*
This is the sample code of Prof. HsinMu's 2013 Spring DSA HW1
Contribute to Prof. HsinMu 's excellent teaching in DSA
Timestamp : 2013.2.26
*/
/*
Purposal: To solve a maze according to the determinant of hint matrix
Input Format: PLZ refer to Prof. HsinMu's 2013 Spring DSA HW1 spec for details.
Output Format: the path traveled until encountering a blind-path
*/

#include <stdio.h>
#include <stdlib.h>
int** hint;			//store hint matrix B
int determinant(int current[]);
int main(){
	int i,j,		//counter
		start[2], 	//start point cord.
		current[2], //current point cord.
		direct = 0,	//prev. direction, prevent from moving back, 1~4 represent >,v,<,^
		row,col,	//numbers of row & col
		flag=1,		//flag to decide entering a bling-alley or not, 1 to keep going and 0 to stop
		det;		//determinant of 3*3 hint matrix with origin in current position 
	int** maze;		//store maze matrix A
	//code start
	scanf("%d %d %d %d",&start[0],&start[1],&row,&col);
	maze = (int**)malloc(sizeof(int*)*row);
	hint = (int**)malloc(sizeof(int*)*row);
	for(i=0;i<row;i++){
		maze[i] = (int*) malloc(sizeof(int)*col);
		for(j=0;j<col;j++)
			scanf("%d",&maze[i][j]);
	}
	for(i=0;i<row;i++){
		hint[i] = (int*) malloc(sizeof(int)*col);
		for(j=0;j<col;j++)
			scanf("%d",&hint[i][j]);
	}																//dynamically allocate maze and hint matrix
	current[0] = start[0]-1;
	current[1] = start[1]-1;										// start with start point (-1 to fit array index
	while(flag){
		det = determinant(current);
		printf("%d %d\n",current[0]+1,current[1]+1);				//	print current position as the answer
		if(det == maze[current[0]][current[1]+1] && direct != 3){	// 	if neighbor on the right hand side is valid, 
																	// 	and not come from right ( or var. direct == 3
			current[1]++;											//	go to the entry on the right
			direct = 1;												//	mark we come from left
		}
		else if(det == maze[current[0]+1][current[1]] && direct != 4){	//etc...
			current[0]++;
			direct = 2;
		}
		else if(det == maze[current[0]][current[1]-1] && direct != 1){
			current[1]--;
			direct = 3;
		}
		else if(det == maze[current[0]-1][current[1]] && direct != 2){
			current[0]--;
			direct = 4;
		}
		else
			flag = 0;												// 	none of neighbor is valid except for the way we come from
																	//	jump out
	}
	return 0;
}
int determinant(int current[]){
		int temp[9],	//used to store the 3*3 matrix
			i,j,count=0;
		for(i=-1;i<2;i++)
			for(j=-1;j<2;j++)
				temp[count++] = hint[current[0]+i][current[1]+j];	//store it to 3*3 matrix
		return 	temp[0]*temp[4]*temp[8]+
				temp[1]*temp[5]*temp[6]+
				temp[2]*temp[3]*temp[7]-
				temp[2]*temp[4]*temp[6]-
				temp[1]*temp[3]*temp[8]-
				temp[0]*temp[5]*temp[7];	//determinant operation
}
