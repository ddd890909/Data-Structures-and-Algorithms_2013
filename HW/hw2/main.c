//構建unrolled linked list并完成在其中插值 

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

struct Node
{
	struct Node *next;
	int value;
};

struct Block
{
	struct Block *next;
	struct Node *head;
	int nodeCount;
};

int main()
{
	int m=0;
	int mSqrtCeil;
	//int mSqrtFloor;
	char operation[9];
	int k,x;
	struct Block *blockHead;
	blockHead=(struct Block*)malloc(sizeof(struct Block));
	blockHead->head =NULL;
	blockHead->next =NULL;
	blockHead->nodeCount =0;
	//blockHead->head =(struct Node*)malloc(sizeof(struct Node));
	struct Block *blockTemp;
	//blockTemp=(struct Block*)malloc(sizeof(struct Block));	
	struct Node *nodeTemp;

	//printf("The Number of Operations:\n");
	scanf("%d",&m);

	mSqrtCeil=ceil(sqrt(1.0*m));
	//mSqrtFloor=floor(sqrt(1.0*m));

	//printf("The Operations:\n");
	
	for(int i=1;i<=m;i++)
	{
		
		scanf("%s",&operation);
	
		////////////////////////////////////////insert
		if(operation[0]=='i')
		{
			scanf("%d %d",&k,&x);

			struct Node *insertNode;   //要不要放外面
		    insertNode=(struct Node*)malloc(sizeof(struct Node));
			insertNode->next =NULL;
			insertNode->value =x;

			int blockNumber=ceil(1.0*k/mSqrtCeil);
			int nodeNumber=k%mSqrtCeil;	

			////////////////////////////////k=0的情況
			if(k==0)           
			{
				blockTemp=blockHead;
				if(blockTemp->head ==NULL)
				{
					blockTemp->head=insertNode;
					blockTemp->nodeCount ++;
				}
				else if(blockTemp->head !=NULL)
				{
					if(blockTemp->head ->next ==NULL)
						insertNode->next =blockTemp->head;
					else
						insertNode->next =blockTemp->head ->next ;
					blockTemp->head ->next =insertNode;
					blockTemp->head=insertNode;
					blockTemp->nodeCount ++;

					while(blockTemp->nodeCount >mSqrtCeil)
					{
						nodeTemp=blockTemp->head ->next;
						blockTemp->head ->next =nodeTemp->next;
						blockTemp->nodeCount --;
						
						if(blockTemp->next ==NULL)
						{
							blockTemp->next=(struct Block*)malloc(sizeof(struct Block));
							blockTemp->next->head =NULL;
							blockTemp->next->next =NULL;
							blockTemp->next->nodeCount =0;

							blockTemp=blockTemp->next ;
							nodeTemp->next =NULL;
							blockTemp->head =nodeTemp;
							blockTemp->nodeCount ++;
							break;
						}

						blockTemp=blockTemp->next ;

						if(blockTemp->head ->next ==NULL)
							nodeTemp->next =blockTemp->head;
						else
							nodeTemp->next =blockTemp->head ->next ;
						blockTemp->head ->next =nodeTemp;
						blockTemp->head =nodeTemp;
						blockTemp->nodeCount++;
					}
				}
			}
			///////////////////////////////////k=0的情況結束
			else if(k!=0)
			{
				///////////////////find block
				blockTemp=blockHead;
				for(int i=1;i<=mSqrtCeil;i++)
				{
					if(i==blockNumber)
					{
						break;
					}
					blockTemp=blockTemp->next;
				}
				////////////////////find node
				nodeTemp=blockTemp->head;
				if(nodeNumber!=0)
				{
					for(int j=1;j<=mSqrtCeil;j++)
					{	
						//printf("%d",blockTemp->nodeCount);
						if(j==(blockTemp->nodeCount) - nodeNumber+1)
						{													
							//printf("%d\n",nodeTemp->next);
							insertNode->next =nodeTemp->next ;
							nodeTemp->next =insertNode;
							blockTemp->nodeCount ++;
							break;
						}
						nodeTemp=nodeTemp->next;
					}
				}
				else if(nodeNumber==0)
				{
					if(blockTemp->next ==NULL)
					{
						blockTemp->next=(struct Block*)malloc(sizeof(struct Block));
						blockTemp->next->head =NULL;
						blockTemp->next->next =NULL;
						blockTemp->next->nodeCount =0;

						blockTemp=blockTemp->next ;
						insertNode->next =NULL;
						blockTemp->head =insertNode;
						blockTemp->nodeCount ++;					
					}
					else if(blockTemp->next !=NULL)
					{
						blockTemp=blockTemp->next;
						if(blockTemp->head ->next ==NULL)
							insertNode->next =blockTemp->head;
						else if(blockTemp->head ->next !=NULL)
							insertNode->next =blockTemp->head ->next ;
						blockTemp->head ->next =insertNode;
						blockTemp->head =insertNode;
						blockTemp->nodeCount++;
					}
				}

				//printf("%d",blockTemp->nodeCount);
				while(blockTemp->nodeCount >mSqrtCeil)
				{
					nodeTemp=blockTemp->head ->next;
					blockTemp->head ->next =nodeTemp->next;
					blockTemp->nodeCount --;
					
					if(blockTemp->next ==NULL)
					{
						blockTemp->next=(struct Block*)malloc(sizeof(struct Block));
						blockTemp->next->head =NULL;
						blockTemp->next->next =NULL;
						blockTemp->next->nodeCount =0;

						blockTemp=blockTemp->next ;
						nodeTemp->next =NULL;
						blockTemp->head =nodeTemp;
						blockTemp->nodeCount ++;
						break;
					}

					blockTemp=blockTemp->next ;

					if(blockTemp->head ->next ==NULL)
						nodeTemp->next =blockTemp->head;
					else
						nodeTemp->next =blockTemp->head ->next ;
					blockTemp->head ->next =nodeTemp;
					blockTemp->head =nodeTemp;
					blockTemp->nodeCount++;
				}
			}
		}

		/////////////////////////////////////query
		else if(operation[0]=='q')
		{
			scanf("%d",&k);
			
			//find block
			int blockNumber=ceil(1.0*k/mSqrtCeil);
			blockTemp=blockHead;
			for(int i=1;i<=mSqrtCeil;i++)
			{
				if(i== blockNumber)
					break;
				blockTemp=blockTemp->next;	
			}

			//find node
			int nodeNumber=k%mSqrtCeil;
			nodeTemp=blockTemp->head;
			if(nodeNumber!=0 && nodeNumber!=1)
			{
				for(int j=1;j<=mSqrtCeil;j++)
				{
					if(j==blockTemp->nodeCount - nodeNumber+2)
					{
						printf("%d\n",nodeTemp->value);  //query				
						break;
					}	
					nodeTemp=nodeTemp->next;
				}
			}
			else if(nodeNumber==1)
			{
				printf("%d\n",nodeTemp->value); 
			}
			else if(nodeNumber==0)
			{
				printf("%d\n",nodeTemp->next->value); 
			}
		}

		else
		{
			exit(-1);
		}
	}
	
	return 0;
}