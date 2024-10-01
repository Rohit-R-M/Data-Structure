//bubble sort
#include<stdio.h>
int main()
{
	int i,j,n,temp;
	
	printf("Enter the size of the array: \n");
	scanf("%d",&n);
	
	int a[n];
	
	printf("Enter the %d numbers: \n",n);
	for (i=0;i<n;i++)
		scanf("%d",&a[i]);
		
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	
	printf("Sorted Array elements:\n");
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
}