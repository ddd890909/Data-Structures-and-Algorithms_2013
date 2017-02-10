//構建BST并完成在其中找到最接近的數
//參考上課投影片，獨立完成

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

struct BSTNode
{
	int data;
	struct BSTNode* leftChild;
	struct BSTNode* rightChild;
};

//struct BST
//{
//	struct BSTNode* root;
//};

struct BSTNode *insertNode(BSTNode *root,int x)
{
	if(root==NULL)
	{
		root=(struct BSTNode*)malloc(sizeof(struct BSTNode));
		if(root==NULL)
		{
			printf("Error1\n");
			exit(-1);
		}
		root->data =x;
		root->leftChild =NULL;
		root->rightChild =NULL;
	}
	else
	{
		if(x< root->data )
			root->leftChild =insertNode(root->leftChild,x );
		else if(x> root->data )
			root->rightChild =insertNode(root->rightChild,x);
	}
	return root;
}

struct BSTNode *deleteNode(BSTNode *root,int x)
{
	BSTNode *temp;
	if(root==NULL)
	{
		printf("Error2\n");
		return NULL;
	}
	else if(x< root->data )
		root->leftChild =deleteNode(root->leftChild ,x);
	else if(x> root->data )
		root->rightChild =deleteNode(root->rightChild ,x);
	else  //x= root->data
	{
		if(root->leftChild && root->rightChild )
		{
			temp=root->leftChild ;
			while(temp->rightChild )
			{
				temp=temp->rightChild ;
			}
			root->data =temp->data ;
			root->leftChild =deleteNode(root->leftChild ,root->data );
		}
		else
		{
			temp=root;
			if(root->leftChild ==NULL && root->rightChild !=NULL)
				root=root->rightChild;
			else if(root->rightChild ==NULL && root->leftChild !=NULL)
				root=root->leftChild ;
			else if(root->leftChild ==NULL && root->rightChild ==NULL)
				root=NULL;
			free(temp);
		}
	}
	return root;
}

int dif;
BSTNode *queryTemp;
BSTNode *queryTempRepeat;

struct BSTNode *queryNode(BSTNode *root,int x)
{
	if(root==NULL) //找不到
	{
		if(queryTempRepeat !=NULL && (abs(x-queryTempRepeat->data ) == dif) )
		{	
			if(queryTempRepeat->data > queryTemp->data)
				printf("%d %d\n",queryTemp->data,queryTempRepeat->data);
			else if(queryTempRepeat->data < queryTemp->data)
				printf("%d %d\n",queryTempRepeat->data,queryTemp->data);			
		}
		else
		{
			printf("%d\n",queryTemp->data);
		}
		return root;
	}
	else
	{
		if(x< root->data )
		{
			if( abs(x-root->data ) < dif )
			{
				dif=abs(x-root->data );
				queryTemp=root;
			}
			else if( abs(x-root->data ) == dif )
			{
				queryTempRepeat=root;
			}
			root->leftChild =queryNode(root->leftChild ,x);
		}	
		else if(x> root->data )
		{
			if( abs(x-root->data ) < dif )
			{
				dif=abs(x-root->data );
				queryTemp=root;
			}
			else if( abs(x-root->data ) == dif )
			{
				queryTempRepeat=root;
			}
			root->rightChild =queryNode(root->rightChild ,x);
		}	
		else  //x= root->data
		{		
			printf("%d\n",root->data);
			return root;
		}
	}
	return root;
}

struct BSTNode *queryNodeRepeat(BSTNode *root,int x)
{
	
	if(root==NULL)
	{
		printf("%d\n",queryTemp->data);
		return root;
	}
	else
	{
		if(abs(x-root->data ) == dif)
		{
			if(root->data < queryTemp->data)
			{
				printf("%d %d\n",root->data,queryTemp->data);
				return root;
			}
			else if(root->data > queryTemp->data)
			{	printf("%d %d\n",queryTemp->data,root->data);
				return root;
			}
		}
		else
		{
			if(x< root->data )
			{
				root->leftChild =queryNodeRepeat(root->leftChild ,x);
			}	
			else if(x> root->data )
			{
				root->rightChild =queryNodeRepeat(root->rightChild ,x);
			}	
			else  //x= root->data
			{
				printf("%d\n",queryTemp->data);
				return root;
			}
		}
	}
	return root;
}


int main()
{
	int n;
	int x;
	char operation[9];
	
	struct BSTNode *root;
	root=NULL;
	//struct BSTNode *temp;

	//printf("The Number of Operations:\n");
	scanf("%d",&n);

	//printf("The Operations:\n");
	int i;
	for(i=1;i<=n;i++)
	{
		scanf("%s",&operation);
		
		/////////////////////////////////////insert
		if(operation[0]=='i')
		{
			scanf("%d",&x);					
			root=insertNode(root,x);		
			//printf("%d",root->data );
		}
		/////////////////////////////////////delete
		else if(operation[0]=='d')
		{
			scanf("%d",&x);
			root=deleteNode(root,x);
		}

		/////////////////////////////////////query
		else if(operation[0]=='q')
		{
			scanf("%d",&x);

			dif=abs(x-root->data)+1;
			queryTemp=root;
			queryTempRepeat=NULL;
			root=queryNode(root,x);
			//root=queryNodeRepeat(root,x);
			//printf("%d\n",root->data );
		}
		else
		{
			printf("Error3\n");
			break;
		}
	}

	return 0;
}