//converting binary to decimal using stack
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stacklladt.h>
int main()
{
	int* dpin;
	STACK* phead;
	bool result;
	int data,temp;
	phead=(STACK*)creatstack();
	printf("Enter the decimal number to convert into binary:\n");
	scanf("%d",&data);
	temp=data;
	while(temp)                                   //it will execute the temp until it become zero
	{
		dpin=(int*)malloc(sizeof(int));
		*dpin=temp%2;
		result=pushstack(phead,dpin);
		temp=temp/2;
	}
	printf("Binary number of %d decimal number is: \n",data);
	while(dpin=(int*)popstack(phead))
	{
		printf("%d",*dpin);
		free(dpin);
	}
	destorystack(phead);
	return 1;
}