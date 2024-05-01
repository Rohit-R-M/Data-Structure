#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
  void* dp;
  struct node *next;
}NODE;

typedef struct LIST
{
  NODE* head;
  int count;
}list;

list* createlist()
{
  list *p;
  p=(list*)malloc(sizeof(list));
  if(p)
  {
    p->head=NULL;
    p->count=0;
  }
  return(p);
}

bool insertion(list *p,NODE *pred,void *din)
{
  NODE* pnew;
  pnew=(NODE*)malloc(sizeof(NODE));
  pnew->dp=din;
  if(pred==NULL)
  {
    pnew->next=p->head;
    p->head=pnew;
    if(p->count==0)
      pnew->next=pnew;
    else
    {
      NODE *t=p->head;
      do{
        t=t->next;
      }while(t->next!=pnew->next);
      t->next = p->head;
    }
  }
  else
  {
    pnew->next=pred->next;
    pred->next=pnew;
  }
  p->count++;
  return(true);
}

void* deletion(list *p,NODE *pred)
{
  NODE *dnode;
  void *dout;
  if(!p->head)
    return NULL;
  else if(!pred)
  {
    dnode=p->head;
    p->head=dnode->next;
    NODE *t=p->head;
    do{
      t=t->next;
    }while(t->next!=dnode);
    t->next = p->head;
  }
  else
  {
    dnode=pred->next;
    pred->next=dnode->next;
  }
  dout=dnode->dp;
  free(dnode);
  p->count--;
  return(dout);
}

NODE* searchlist(list *p,void *pkey,bool(*comp)(void*,void*))
{
  NODE *temp;
  if(!p->head)
  return NULL;
  temp=p->head;
  do
  {
    if(comp(temp->dp,pkey))
     return temp;
    temp=temp->next;
  }
  while(temp->next!= p->head);
  return NULL;
}

void* retrievelist(list* p,void *pkey,bool(*comp)(void*,void*))
{
   NODE *temp;
   temp=searchlist(p,pkey,comp);
   if(temp)
    return(temp->dp);
     return NULL;
}

int countlist(list *p)
{
  return(p->count);
}

bool emptylist(list *p)
{
  if(p->count==0)
   return (true);
  return(false);  
}

bool fulllist(list *p)
{
  NODE *n;
  n=(NODE*)malloc(sizeof(NODE));
  if(n)
  {
    free(n);
    return(false);
  }
  return(true);
}

void displaylist(list *p,void(*fp)(void*))
{
  NODE *t;
  t=p->head;
  do
  {
    fp(t->dp);
    t=t->next;
  }while(t!=p->head);
}

bool destroylist(list *p)
 {
   NODE *t,*d;
   if(!p)
    return(false);
   t=p->head;
   while(t->next!=p->head)
   {
     d=t;
     t=t->next;
     free(d->dp);
     free(d);
   }
   free(p);
   return(true);
 }


void printlist(void *dp)
{
	printf("%d\t",*(int*)dp);
}
bool compare(void *p,void *q)
{
	if(*(int*)p==*(int*)q)
		return true;
	return false;
}
int main()
{
	int ch;
    int *c;
    list *p;
    NODE *pred;
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
					   case 2:printf("enter the element after new node to be inserted\n");
							  scanf("%d",c);
							  pred=searchlist(p,c,compare);
							  if(!pred)
							  {
								  printf("Search is failed for key\n");
							  }
							  break;
						case 3:pred=p->head;
								while(pred->next!=p->head)
								{
									pred=pred->next;
								}
								break;
						default:printf("Invalid choice\n");
								goto label1;
					}
						if(ch==2 && pred==NULL)
							break;
						c=(int*)malloc(sizeof(int));
						if(!c)
						{
							printf("List is full\n");
							break;
						}
					    printf("Enter the element to be inserted:\n");
					    scanf("%d",c);
					    res=(int*)insertion(p,pred,c);
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
					   case 2:printf("enter element to be deleted\n");
							  scanf("%d",c);
							  NODE *temp;
							  pred=NULL;
							  temp=p->head;
							  do
							  {
								pred=temp;
								temp=temp->next;
							  }  
							  while(temp !=p->head && compare(c,(int*)(temp->dp)));
							  break;
						case 3:pred=NULL;
							   NODE *t;
							   t=p->head;
							  do{
								   pred=t;
								   t=t->next;
							   }
							    while(t!=p->head);
							   break;
						default:printf("Invalid choice\n");
								goto label2;
					}
					if(ch==2 && pred==NULL)
					{
						printf("key is not found\n");
						break;
					}
					c=(int*)deletion(p,pred);
					if(c)
					{
						printf("Deleted element is:\n");
						printlist(c);
						free(c);
					}
					else
					printf("List is empty\n");
					break;
			case 3:printf("enter key to retrieve the element\n");
				   scanf("%d",c);
				   c=(int*)retrievelist(p,c,compare);
				   if(c)
				   	printlist(c);
				   else
				   printf("list is empty\n");
				   break;
			case 4: printf("Enter key to find element\n");
				   scanf("%d",c);
				   pred=searchlist(p,c,compare);
				   if(pred)
				   {
					   printf("element found\n");
					   printlist(pred->dp);
				   }
				   else
						printf("element not found\n");
				   break;
			case 5:printf("contents of list are:\n");
				   if(!emptylist(p))
						displaylist(p,printlist);
				   else
						printf("List is empty\n");
				   break;
			case 6:if(fulllist(p))
						printf("List is full\n");
				   else
						printf("list is not full\n");
			       break;
			case 7:if(emptylist(p))
						printf("List is empty\n");
				   else
						printf("list is not empty\n");
			       break;
			case 8:printf("number of elements are:%d\n",countlist(p));
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
			
			
			              
				   
				   
						
						
								   
							 
							  
						
						
						
						
							  
							
								
			
	
