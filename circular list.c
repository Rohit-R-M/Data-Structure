#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
	void* dp;
	struct node* next;
} NODE;

typedef struct list {
	NODE* head;
	int count;
} LIST;

LIST* createlist() {
	LIST* p;
	p = (LIST*)malloc(sizeof(LIST));
	if (!p)
		return NULL;
	p->head = NULL;
	p->count = 0;
	return p;
}

bool insertion(LIST* p, NODE* pred, void* din) {
	NODE* pnew;
	pnew = (NODE*)malloc(sizeof(NODE));
	if (!pnew)
		return false;
	pnew->dp = din;
	if (pred == NULL) {
		if (p->head == NULL) {
			pnew->next = pnew; // Points to itself to form a circular reference
			p->head = pnew;
		} else {
			pnew->next = p->head;
			NODE* temp = p->head;
			while (temp->next != p->head)
				temp = temp->next;
			temp->next = pnew;
			p->head = pnew;
		}
	} else {
		pnew->next = pred->next;
		pred->next = pnew;
	}
	p->count++;
	return true;
}

void* deletion(LIST* p, NODE* pred) {
	void* dout;
	NODE* delnode;
	if (!p->head)
		return NULL;
	else if (!pred) {
		delnode = p->head;
		if (p->head->next == p->head)
			p->head = NULL;
		else {
			NODE* temp = p->head;
			while (temp->next != p->head)
				temp = temp->next;
			temp->next = p->head->next;
			p->head = p->head->next;
		}
	} else {
		delnode = pred->next;
		pred->next = delnode->next;
	}
	dout = delnode->dp;
	free(delnode);
	p->count--;
	return dout;
}

NODE* searchlist(LIST* p, void* pkey, bool (*cmp)(void*, void*)) {
	NODE* temp;
	if (!p->head)
		return NULL;
	temp = p->head;
	do {
		if (cmp(temp->dp, pkey))
			return temp;
		temp = temp->next;
	} while (temp != p->head);
	return NULL;
}

void* retrievelist(LIST* p, void* pkey, bool (*cmp)(void*, void*)) {
	NODE* temp;
	temp = searchlist(p, pkey, cmp);
	if (temp)
		return (temp->dp);
	return NULL;
}

void displaylist(LIST* p, void (*fp)(void*)) {
	if (!p->head)
		return;
	NODE* temp;
	temp = p->head;
	do {
		fp(temp->dp);
		temp = temp->next;
	} while (temp != p->head);
}

bool listfull(LIST* p) {
	NODE* temp;
	temp = (NODE*)malloc(sizeof(NODE));
	if (temp) {
		free(temp);
		return false;
	}
	return true;
}

bool listempty(LIST* p) {
	if (p->head == NULL)
		return true;
	return false;
}

int listcount(LIST* p) {
	return (p->count);
}

bool destroylist(LIST* p) {
	if (!p)
		return false;
	NODE* t, * delnode;
	if (p->head) {
		t = p->head;
		do {
			delnode = t;
			t = t->next;
			free(delnode->dp);
			free(delnode);
		} while (t != p->head);
	}
	free(p);
	return true;
}
void printlist(void *dp)
{
	printf("%d\n",*(int*)dp);
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
    LIST *p;
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
							  while(temp != NULL && compare(c,(int*)(temp->dp)))
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
			
			
			              
				   
				   
						
						
								   
							 
							  
						
						
						
						
							  
							
								
			
	
