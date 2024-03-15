//Array stack ADT of student information
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct array_stack
{
	void** st;
	int top;
	int count;
	int size;
}AST;
AST* creatstack()
{
	int n;
	AST* h=(AST*)malloc(sizeof(AST));
	if(h)
	{
		printf("Enter the size of an array:\n");
		scanf("%d",&n);
		h->st=(void**)calloc(n,sizeof(void*));
		if(h->st)
		{
			h->top=-1;
			h->count=0;
			h->size=n;
		}
		else
		{
			free(h);
			return(NULL);
		}
	}
	return(h);
}
bool pushstack(AST* h,void* dpin)
{
	if(h->top==h->size-1)
	{
		return(false);
	}
	else
	{
		h->top++;
		h->st[h->top]=dpin;
		h->count++;
		return(true);
	}
}
bool stackempty(AST* h)
{
	if(h->count==0)
	return (true);
	else
	return (false);
}
void* popstack(AST* h)
{
	void* dpout;
	if(stackempty(h))
	{
		return (NULL);
	}
	else
	{
		dpout=h->st[h->top];
		h->top--;
		h->count--;
		return (dpout);
	}
}
void stackdisplay(AST* h,void (*pd)(void*))
{
	int i;
	if(stackempty(h))
	{
		printf("Stack is empty\n");
		return;
	}
	else
	{
		for(i=h->top;i>=0;i--)
		{
			pd(h->st[i]);
		}
	}
}
bool stackfull(AST* h)
{
	if(h->top==h->size-1)
	return (true);
	else
	return false;
}
void* stacktop(AST* h)
{
	if(stackempty(h))
	return NULL;
	else
	return (h->st[h->top]);
}
int stackcount(AST* h)
{
	return(h->count);
}
bool destory(AST* h)
{
	int i;
	if(h)
	{
		for(i=h->top;i>=0;i--)
		{
			free(h->st[i]);
			(h->count)--;
		}
		free(h);
	}
	return(true);
}
typedef struct student
{
	int sem,roll_no;
	char name[15],usn[11],branch[6];
}stud;
void printdata(void* s)
{
	stud* t=(stud*)s;
	if(s)
	{
	printf("Name: %s\n",t->name);
	printf("Branch: %s\n",t->branch);
	printf("USN: %s\n",t->usn);
	printf("Sem: %d\n",t->sem);
	printf("Roll_no: %d\n\n",t->roll_no);
    }
}
int main()
{
	stud* s;
	AST* ph;
	int c;
	bool result;
	ph=creatstack();
	printf("Stack of student using array stack ADT\n");
	printf("1-PUSH\n2-POP\n3-DISPLAY\n4-EMPTY STACK\n5-STACK FULL\n6-STACK TOP\n7-STACK COUNT\n8-EXIT\n");
	while(1)
	{
		printf("\n\nEnter the choice\n");
		scanf("%d",&c);
		switch(c)
		{
			case 1:
			    s=(stud*)malloc(sizeof(stud));
			    if(s)
			    {
			    printf("Enter the details of student\n");
			    printf("Enter the Name:\n");
			    scanf("%s",s->name);
			    printf("Enter the Branch:\n");
			    scanf("%s",s->branch);
			    printf("Enter the USN:\n");
			    scanf("%s",s->usn);
			    printf("Enter the SEM:\n");
			    scanf("%d",&s->sem);
			    printf("Enter the Roll_no:\n");
			    scanf("%d",&s->roll_no);
			    if(pushstack(ph,s))
			    {
			    	printf("Student Data inserted Successfully\n");
				}
				else
				{
					printf("Failed");
					free(s);
				}
		        }
			    break;
			case 2: 
			    s=(stud*)popstack(ph);
			    if(s)
			    {
				    printdata(s);	
					free(s);		 	
				}
				else
				{
					printf("Pop opertion is failed\n");
				}
				break;
			case 3:
				if(stackempty(ph))
				printf("No student information is there to display\n");
				else
				printf("Student details are as follows:\n");
				stackdisplay(ph,printdata);
			    break;
			case 4:
				if(stackempty(ph))
				printf("Stack is empty\n");
				else
				printf("Stack is not empty\n");
				break;
			case 5:
				if(stackfull(ph))
				printf("Stack is full\n");
				else
				printf("Stack is not full\n");
				break;
			case 6:
			    s=(stud*)stacktop(ph);
			    if(s)
			    {
			    	printf("Top element in the Stack is:\n");
			    	printdata(s);
				}
				else
				{
					printf("There is no student information present in Stack\n");
				}
				break;
			case 7:
				printf("Number of Student information in stack are: %d",stackcount(ph));
				break;
			case 8:
				 result=destory(ph);
                if (result)
                    printf("Stack destroyed successfully\n");
                else
                    printf("Failed to destroy stack\n");
                return 0;
                break;
			default:
			    printf("Entered choice is invalid\n");  
			}
		}
}