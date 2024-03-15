//QUEUE Linked list ADT
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct NODE
{
	void* dp;
	struct NODE* next;
}node;
typedef struct QUEUE
{
	node* front;
	node* rear;
	int count;
}queue;
queue* createqueue();
bool enqueue(queue*,void*);
void* dequeue(queue*);
void* retrivelfront(queue*);
void* retrivelrear(queue*);
bool emptyqueue(queue*);
bool fullqueue(queue*);
int queuecount(queue*);
void displayqueue(queue* ,void (*fp)(void*));
bool destroyqueue(queue*);
queue* createqueue()
{
	queue* q;
	q=(queue*)malloc(sizeof(queue));
	if(q)
	{
		q->front=NULL;
		q->count=0;
		q->rear=NULL;
		return q;
	}
	else
	{
		return NULL;
	}
}
bool enqueue(queue* q,void* dpin)
{
	node* pnew;
	pnew=(node*)malloc(sizeof(node));
	if(pnew)
	{
		pnew->dp=dpin;
		if(q->count==0)
		q->front=pnew;
		else
		q->rear->next=pnew;
		q->rear=pnew;
		q->count++;
		return true;
	}
	else
	{
		return false;
	}
}
void* dequeue(queue* q)
{
	node* pnode;
	void* ddata;
	if(q->count==0)
	return NULL;
	else
	pnode=q->front;
	if(q->count==1)
	{
		q->rear=NULL;
	}
	q->front=q->front->next;
	ddata=pnode->dp;
	q->count--;
	free(pnode);
	return ddata;
}
void* retrivelfront(queue* q)
{
	if(emptyqueue(q))
	return false;
	return(q->front->dp);
}
void* retrivelrear(queue* q)
{
	if(emptyqueue(q))
	return false;
	return(q->rear->dp);
}
bool emptyqueue(queue* q)
{
	if(!q->count)
	return true;
	return false;
}
bool fullqueue(queue* q)
{
	node* temp;
	temp=(node*)malloc(sizeof(node));
	if(temp)
	return false;
	return true;
}
int queuecount(queue* q)
{
	return (q->count);
}
void qdisplay(queue* q,void (*print)(void*))
{
	node* temp;
	if(!q->count)
	return;
	for(temp=q->front;temp!=q->rear;temp=temp->next)
	print(temp->dp);
	print(temp->dp);
}
bool qdestory(queue* q)
{
	node* temp;
	if(q)
	{
		while(q->front!=NULL)
		{
			free(q->front->dp);
			temp=q->front;
			q->front=temp->next;
			free(temp);
		}
		free(q);
	}
	return true;
}
void print(void* dp)
{
	printf("%f\n",*(float*)dp);
}
int main()
{
	queue* q;
	float* dp;
	bool result;
	int ch;
	q=createqueue();
	if(!q)
	{
		printf("QUEUE creation is failed\n");
		return 0;
	}
	printf("---------------------Queue created successfully----------------------------\n");
	while(1)
	{
	    printf("1-Enqueue\n2-Dequeue\n3-Display\n4-Front element\n5-Rear element\n6-Empty\n7-Full\n8-Count\n9-Exit");
		printf("\nEnter the choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
			    dp=(float*)malloc(sizeof(float));
			    printf("Enter the floating point number\n");
			    scanf("%f",dp);
			    result=enqueue(q,dp);
			    result==0?printf("Failed\n"):printf("Successfull");
			    break;
			case 2:
				dp=dequeue(q);
				if(dp)
				printf("Deleted elements is: %f",*dp);
				else
				printf("Queue is Empty\n");
				break;
			case 3:
			    if(!emptyqueue(q))
			    printf("Queue is empty\n");
			    else
			    printf("Queue contants are: \n");
			    qdisplay(q,print);
			    break;
			case 4:
				dp=(float*)retrivelfront(q);
				if(dp)
				printf("Front element is: %f\n",*dp);
				else
				printf("Queue empty\n");
				break;
			case 5:
				dp=(float*)retrivelrear(q);
				if(dp)
				printf("Rear element is: %f\n",*dp);
				else
				printf("Queue empty\n");
				break;
			case 6:
				if(emptyqueue(q))
				printf("Queue is empty\n");
				else
				printf("Queue not empty\n");
				break;
			case 7:
				if(fullqueue(q))
				printf("Queue is full\n");
				else
				printf("Queue not full\n");
				break;
			case 8:
				printf("Elements in queue are:%d\n",queuecount(q));
				break;
			case 9:
			    if(qdestory(q))
			    printf("Queue destoryed\n");
			    else
			    printf("Failed\n");
			    return 0;
		    default:printf("Invalid choice\n");
		}
	}
}