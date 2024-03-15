//array queue adt
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define s_size 25
typedef struct arrayqueue
{
	void** data;
	int front;
	int rear;
	int count;
	int size;
}AQUEUE;
AQUEUE* createqueue();
bool enqueue(AQUEUE*,void*);
void* dequeue(AQUEUE*);
void* retrivelfront(AQUEUE*);
void* retrivelrear(AQUEUE*);
bool emptyqueue(AQUEUE*);
bool fullqueue(AQUEUE*);
int queuecount(AQUEUE*);
void displayqueue(AQUEUE* ,void (*fp)(void*));
bool destroyqueue(AQUEUE*);
AQUEUE* createqueue()
{
	AQUEUE* q;
	int n;
	q=(AQUEUE*)malloc(sizeof(AQUEUE));
	if(!q)
	{
		free(q);
		return NULL;
	}
	else
	{
		printf("Enter the size of an array:\n");
		scanf("%d",&n);
		q->data=(void**)calloc(n,sizeof(void*));
		if(q->data)
		{
		q->count=0;
		q->front=-1;
		q->rear=-1;
		q->size=n;
		}
	}
	return q;
}
bool enqueue(AQUEUE* q,void* dpin)
{
	if(q->count==q->size)
	return false;
	else if(!q->count)
	{
	q->front=0;
    }
	q->rear=(q->rear+1)%q->size;
	q->data[q->rear]=dpin;
	q->count++;
	return true;
}
void* dequeue(AQUEUE* q)
{
	void* dout;
	if(!q->count)
	return NULL;
	else
	{
	dout=q->data[q->front];
	q->front=(q->front+1)%q->size;
	q->count--;
	if(q->count==0)
	{
		q->front=-1;
		q->rear=-1;
	}
	return dout;
}
}
void* retrivelfront(AQUEUE* q)
{
	if(emptyqueue(q))
	return NULL;
	return(q->data[q->front]);
}
void* retrivelrear(AQUEUE* q)
{
	if(emptyqueue(q))
	return NULL;
	return(q->data[q->rear]);
}
bool emptyqueue(AQUEUE* q)
{
	if(q->count==0)
	return true;
	else
	return false;
}
bool fullqueue(AQUEUE* q)
{
	if(q->count==q->size)
	return true;
	else
	return false;
}
int queuecount(AQUEUE* q)
{
	return(q->count);
}
void displayqueue(AQUEUE* q,void (*fp)(void*))
{
	int i;
	if(q->count==0)
	{
	printf("Queue is empty\n");
	return;
    }
	else
	{
	for(i=q->front;i!=q->rear;i=(i+1)%q->size)
	fp(q->data[i]);
	fp(q->data[i]);
    }
}
bool destroyqueue(AQUEUE* q)
{
	int i;
	if(q)
	{
		for(i=q->front;i!=q->rear;i=(i+1)%q->size)
		{
			free(q->data[i]);
		}
		free(q->data);
		free(q);
	}
	return true;
}
void printstring(void* dp)
{
	printf("%s\n",(char*)dp);
}
int main()
{
	AQUEUE* q;
	char* dp;
	bool result;
	int ch;
	q=createqueue();
	if(!q)
	{
		printf("Queue creation is failed\n");
		return 1;
	}
	else
	printf("---------------------Queue created successfully----------------------------\n");
	printf("1-Enqueue\n2-Dequeue\n3-Display\n4-Front element\n5-Rear element\n6-Empty\n7-Full\n8-Count\n9-Exit");
	while(1)
	{
		printf("\nEnter the Choice:\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				dp=(char*)calloc(s_size,sizeof(char));
				dp=(char*)malloc(sizeof(char));
				printf("Enter the string:\n");
				scanf("%s",dp);
				result=enqueue(q,dp);
				result==0?printf("Failed\n"):printf("Successfull\n");
			    break;
			case 2:
				dp=(char*)dequeue(q);
				if(dp)
				{
					printf("Deleted Element from Queue is:%s \n",dp);
				    free(dp);
				}
				else
					printf("Queue is Empty\n");
				break;
			case 3:
				printf("Queue Contants are:\n");
				displayqueue(q,printstring);
			    break;
			case 4:
				dp=(char*)retrivelfront(q);
				if(dp)
				printf("Front String is: %s\n",dp);
				else
				printf("Queue empty\n");
				break;
			case 5:
				dp=(char*)retrivelrear(q);
				if(dp)
				printf("Rear String is: %s\n",dp);
				else
				printf("Queue empty\n");
				break;
			case 6:
				if(emptyqueue(q))
				printf("Queue is empty\n");
				else
				printf("Queue is not empty\n");
				break;
			case 7:
				if(fullqueue(q))
				printf("Queue is full\n");
				else
				printf("Queue is not full\n");
				break;
			case 8:
				printf("Number of strings in Queue are: %d",queuecount(q));
				break;
			case 9:
				if(destroyqueue(q))
				{
					printf("Queue destroyed Successfully\n");
				}
				else
				{
					printf("Queue doesnt exists\n");
				}
				return 0;
			default:printf("Invalid Choice\n");
		}
	}
}
