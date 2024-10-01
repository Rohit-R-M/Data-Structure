//Selection sort
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
		int min=i;
		for(j=i+1;j<n;j++)
		{
			if(a[j]<a[min])
				min=j;
		}
		if(min!=i)
		{
			temp=a[i];
			a[i]=a[min];
			a[min]=temp;
		}
	}
	
	printf("Sorted Array elements:\n");
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
}