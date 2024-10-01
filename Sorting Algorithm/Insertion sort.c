//Insertion sort
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
		
	for(i=1;i<n;i++)
	{
		temp=a[i];
		j=i-1;
		
		while(j>=0 && a[j]>temp)
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=temp;
	}
	
	printf("Sorted Array elements:\n");
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
}