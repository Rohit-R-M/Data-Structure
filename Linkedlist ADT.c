#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct node
{
	void *dp;
	struct node *next;
}NODE;

typedef struct list
{
	NODE *head;
	int count;
}LIST;
LIST* createlist()
{
	LIST *p;
	p=(LIST*)malloc(sizeof(LIST));
	if(!p)
		return NULL;
	p->head=NULL;
	p->count=0;
	return p;
}
bool insertion(LIST *p,NODE *pred,void *din)
{
	NODE *pnew;
	pnew=(NODE*)malloc(sizeof(NODE));
	if(!pnew)
		return false;
	pnew->dp=din;
	if(pred==NULL)
	{
		pnew->next=p->head;
		p->head=pnew;
	}
	else
	{
		pnew->next=pred->next;
		pred->next=pnew;
	}
	p->count++;
	return true;
}
void* deletion(LIST *p,NODE *pred)
{
	void *dout;
	NODE *delnode;
	if(!p->head)
		return NULL;
	else if(!pred)
	{
		delnode=p->head;
		p->head=delnode->next;
	}
	else
	{
		delnode=pred->next;
		pred->next=delnode->next;
	}
	dout=delnode->dp;
	free(delnode);
	p->count--;
	return dout;
}
NODE* searchlist(LIST *p,void *pkey,bool (*cmp)(void *,void *))
{
	NODE *temp;
	if(!p->head)
		return NULL;
	temp=p->head;
	while(temp!=NULL)
	{
		if(cmp(temp->dp,pkey))
			return temp;
		temp=temp->next;
	}
	return NULL;
}
void* retrievelist(LIST *p,void *pkey,bool (*cmp)(void *,void *))
{
	NODE *temp;
	temp=searchlist(p,pkey,cmp);
	if(temp)
		return(temp->dp);
   	return NULL;
}
void displaylist(LIST *p,void (*fp)(void *))
{
	NODE *temp;
	for(temp=p->head;temp!=NULL;temp=temp->next)
	fp(temp->dp);
}
bool listfull(LIST *p)
{
	NODE *temp;
	temp=(NODE*)malloc(sizeof(NODE));
	if(temp)
	{
		free(temp);
		return false;
	}
	return true;
}

bool listempty(LIST *p)
{
	if(p->head==NULL)
		return true;
	return false;
}

int listcount(LIST *p)
{
	return (p->count);
}

bool destroylist(LIST *p)
{
	NODE *t,*delnode;
	if(!p)
		return false;
	t=p->head;
	while(t)
	{
		delnode=t;
		t=t->next;
		free(delnode->dp);
		free(delnode);
	}
	free(p);
	return true;
}
typedef struct course
{
	char code[10];
	char title[25];
	int credit;
	int l,t,p;
	int cie;
	int see;
	char type[2];
}COURSE;
void printlist(void *dp)
{
	COURSE *t;
	t=(COURSE*)dp;
	printf("\nCourse code:%s\n",t->code);
	printf("Course Title:%s\n",t->title);
	printf("Course credits:%d\n",t->credit);
	printf("L:T:P=%d:%d:%d\n",t->l,t->t,t->p);
	printf("CIE=%d\n",t->cie);
	printf("SEE=%d\n",t->see);
	printf("Type of course=%s\n",t->type);
}
bool compare(void *p,void *q)
{
	COURSE *t,*d;
	t=(COURSE*)p;
	d=(COURSE*)q; 
	if(!strcmp(t->code,d->code))
		return true;
	return false;
}

int main()
{
	int ch;
    COURSE *c;
    LIST *p;
    NODE *pred;
    char pkey[10];
    bool res;
	
	
	p=createlist();
	if(!p)
	{
		printf("List creation failed ");
		return 1;
	}
	while(1)
	{
		printf("\n1 for insertion\n2 for deletion\n3 for retrieval\n4 for search\n5 for display\n6 for Full\n7 for Empty\n8 for Count\n9 Exit\n");
		printf("Enter  choice:\n");
		scanf("%d",&ch);
		switch(ch)
		{
			label1:
			 case 1:printf("1 for beginning\n2 for middle\n3 for end\n");
				   printf("Enter  choice:\n");
				   scanf("%d",&ch);
				   switch(ch)
				   {
					   case 1:pred=NULL;
							  break;
					   case 2:printf("enter course code after new node to be inserted\n");
							  scanf("%s",pkey);
							  pred=searchlist(p,pkey,compare);
							  if(!pred)
							  {
								  printf("Search is failed for key\n");
							  }
							  break;
						case 3:pred=p->head;
								while(pred->next)
								{
									pred=pred->next;
								}
								break;
						default:printf("Invalid choice\n");
								goto label1;
					}
						if(ch==2 && pred==NULL)
							break;
						c=(COURSE*)malloc(sizeof(COURSE));
						if(!c)
						{
							printf("List is full\n");
							break;
						}
						printf("Enter course details\n");
						printf("Course code\n");
						scanf("%s",c->code);
						printf("course title\n");
						scanf("%s",c->title);
						printf("course credit\n");
						scanf("%d",&c->credit);
						printf("L:T:P\n");
						scanf("%d %d %d",&c->l,&c->t,&c->p);
						printf("CIE marks\n");
						scanf("%d",&c->cie);
						printf("SEE marks\n");
						scanf("%d",&c->see);
						printf("Course type\n");
						scanf("%s",c->type);
						res=insertion(p,pred,c);
						if(res)
							printf("Inserted successfully\n");
						else
							printf("Insertion failed\n");
						break;
			case 2:printf("1 for beginning\n2 for middle\n3 for end\n");
				   printf("Enter  choice:\n");
				   scanf("%d",&ch);
				   switch(ch)
				   {
					   label2:
					   case 1:pred=NULL;
							  break;
					   case 2:printf("enter course code to delete the course\n");
							  scanf("%s",pkey);
							  NODE *temp;
							  pred=NULL;
							  temp=p->head;
							  while(temp != NULL && strcmp(pkey, ((COURSE *)(temp->dp))->code))
							  {
								pred=temp;
								temp=temp->next;
							  }  
							  break;
						case 3:pred=NULL;
							   NODE *t;
							   t=p->head;
							   while(t->next)
							   {
								   pred=t;
								   t=t->next;
							   }
							   break;
						default:printf("Invalid choice\n");
								goto label2;
					}
					if(ch==2 && pred==NULL)
					{
						printf("key is not found\n");
						break;
					}
					c=(COURSE*)deletion(p,pred);
					free(c);
					break;
			case 3:printf("enter key to retrieve the course\n");
				   scanf("%s",pkey);
				   c=(COURSE*)retrievelist(p,pkey,compare);
				   printlist(c);
				   break;
			case 4:printf("Enter course code to search\n");
				   scanf("%s",pkey);
				   pred=searchlist(p,pkey,compare);
				   if(pred)
				   {
					   printf("course id found\n");
					   printlist(pred->dp);
				   }
				   else
						printf("Course is not found\n");
				   break;
			case 5:printf("contents of list are:\n");
				   if(!listempty(p))
						displaylist(p,printlist);
				   else
						printf("List is empty\n");
				   break;
			case 6:if(listfull(p))
						printf("List is full\n");
				   else
						printf("list is not full\n");
			       break;
			case 7:if(listempty(p))
						printf("List is empty\n");
				   else
						printf("list is not empty\n");
			       break;
			case 8:printf("number of elements are:%d\n",listcount(p));
				   break;
			case 9:if(destroylist(p))
						printf("destroyed successfully\n");
				   else
						printf("failed\n");
				   return 0;
			default:printf("Invalid choice\n");
		}
	}	  
} 		
					
			
			              
				   
				   
						
						
								   
							 
							  
						
						
						
						
							  
							
								
			
	
