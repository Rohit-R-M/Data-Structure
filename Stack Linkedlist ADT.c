#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct node
{
	void* dp;
	struct node* next;
}NODE;
typedef struct stack
{
	int count;
	NODE* top;
}STACK;
STACK* creatstack();
bool pushstack(STACK*,void*);
void* popstack(STACK*);
void stackdisplay(STACK*,void(*pd)(void*));
void* stacktop(STACK*);
bool emptystack(STACK*);
bool stackfull();
int stackcount(STACK*);
bool destorystack(STACK*);
STACK* creatstack()
{
	STACK* s;
	s=(STACK*)malloc(sizeof(STACK*));
	if(s)
	{
		s->top=NULL;
		s->count=0;
	}
	return s;
}
bool pushstack(STACK* head,void* dpin)
{
	NODE* pnew;
	pnew=(NODE*)malloc(sizeof(NODE));
	if(pnew)
	{
		pnew->dp=dpin;
		pnew->next=head->top;
		head->top=pnew;
		head->count++;
		return(true);
	}
	else
	{
		return(false);
	}
}
void* popstack(STACK* head)
{
	NODE* pout;
	void* dpout;
	{
		if(!head->count)
		{
			return(NULL);
		}
		else
		{
			pout=head->top;
			head->top=pout->next;
			head->count--;  
			dpout=pout->dp;
			free(pout); 
			return(dpout);
		}
	}
}
void stackdisplay(STACK* head,void (*pd)(void*))
{
	NODE* temp;
	for(temp=head->top;temp!=0;temp=temp->next)
	pd(temp->dp);
}
void* stacktop(STACK* head)
{
	if(!head->count)
	{
		return NULL;
	}
	else
	{
		return(head->top->dp);
	}
}
bool emptystack(STACK* head)
{
	if(!head->count)
	return(true);
	else
	return(false);
}
bool stackfull()
{
	NODE* temp;
	temp=(NODE*)malloc(sizeof(NODE));
	if(!temp)
	{
		return(true);
	}           
	else
	{
		free(temp);
		return(false);
	}
}
int stackcount(STACK* head)
{
	return(head->count);
}
bool destorystack(STACK* head)
{
	NODE* temp;
	if(head)
	{
		while(head->top!=NULL)
		{
			free(head->top->dp);
			temp=head->top;
			head->top=head->top->next;
			free(temp);
		}
		free(head);
	}
	return (true);
}
void pd(void* dp)
{
	printf("%d\n",*(int*)dp);
}
int main()
{
	STACK* head;
	int* dp,c;
	bool result;
	head=creatstack();
	if(!head)
	{
		printf("Stack creation is Failed\n");
		return(1);
	}
	printf("Stack created successfully\n");
	while(1)
	{
		printf("1-PUSH\n2-POP\n3-DISPLAY\n4-STACK TOP\n5-EMPTY STACK\n6-STACK FULL\n7-STACK COUNT\n8-EXIT\n");
		printf("\nEnter the choice\n");
		scanf("%d",&c);
		switch(c)
		{
			case 1:
				dp=(int*)malloc(sizeof(int));
				printf("Enter the element to be pushed\n");
				scanf("%d",dp);
				result=pushstack(head,dp);
				result==0?printf("Failed\n"):printf("Successful\n");
				break;
			case 2:
				dp=(int*)popstack(head);
				if(dp)
				{
					printf("Popped elemets is %d\n",(*dp));
					free(dp);
				}
				else
				{
					printf("Stack is empty we can't delete the element\n");
				}
				break;
			case 3:
			    if(emptystack(head))
			    {
			    	printf("stack has no elements to display:\n");
				}
				else
				{
					printf("stack contants are\n");
					stackdisplay(head,pd);
				}
				break;
		    case 4:
		    	dp=(int*)stacktop(head);
		    	if(dp)
		    	{
		    		printf("Top element in stack is %d\n",*dp);
				}
				else
				{
					printf("Stack is Empty there is no top element to display\n");
				}
				break;
			case 5:
			    if(emptystack(head))
			    printf("Stack is empty\n");
			    else
			    printf("Stack is not empty\n");
			    break;
			case 6:
				if(stackfull())                          //we are allocating dynamical so it is rear to be full
				{
				printf("Stack is Full\n");
			    }
				else          
				{
				printf("Stack is not Full\n");
			    }
				break;
			case 7:
			    printf("Elements in stack are= %d\n",stackcount(head));
				break;
			case 8:
			    if(destorystack(head))
				printf("stack is destoryed\n");
				else
				printf("stack does not exist\n");
				return(1);	
			default:printf("Invalid choice\n");
		}
	}
}
