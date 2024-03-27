//reverse of integer number......
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stacklladt.h>
int main()
{
	int data;
	int* dpin;
	STACK* phead;
	bool result;
	phead=(STACK*)creatstack();
	printf("Enter the element:EOF for exit\n");
	while(scanf("%d",&data)!=EOF&&!stackfull(phead))
	{
		dpin=(int*)malloc(sizeof(int));
		*dpin=data;
		result=pushstack(phead,dpin);
	}
	printf("Elements in reverse order are:");
	while((dpin=(int*)popstack(phead))!=0)
	{
		printf("%d ",*dpin);
		free(dpin);
	}
	destorystack(phead);
	return 0;
}