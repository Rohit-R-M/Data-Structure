//Quick Sort

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int partition(int arr[],int low,int high)
{
	int key = arr[low];
	int start = low;
	int end = high;
	int temp;
	
	while(start<end)
	{
		while(arr[start] <= key && start<high)
			start++;
	
		while(arr[end]>key)
			end--;
			
		if(start<end)     //swap start and end if the elements are in wrong place
		{
			temp = arr[start];
			arr[start]=arr[end];
			arr[end]=temp;
		}
	}
	temp=arr[low];
	arr[low]=arr[end];
	arr[end]=temp;
	
	return end;
}

int quicksort(int arr[],int low,int high)
{
	if(low<high)
	{
		int loc = partition(arr,low,high);
		quicksort(arr,low,loc-1);
		quicksort(arr,loc+1,high);
	}
}

int main()
{
	int n,i;
	
	printf("Enter the size of the array:\n");
	scanf("%d",&n);
	
	int arr[n];
	
	printf("Generating %d elements:\n",n);
	for(i=0;i<n;i++)
	{
		arr[i]=rand()%1000;
		printf("%d ",arr[i]);
	}
	
	float start =clock();
	
	quicksort(arr,0,n-1);
	
	float end =clock();
	
	float tt=end-start/CLOCKS_PER_SEC;
	
	printf("\nSorted Elements are:\n");
	for(i=0;i<n;i++)
		printf("%d ",arr[i]);
	printf("\n");
	
	printf("Total Time Taken %f",tt);
}
