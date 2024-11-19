//Merge Sort
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void merge(int arr[],int low,int mid,int high)
{
	int n1=mid-low+1; //length of first half
	int n2=high-mid; //length of seconf half

	int a[n1],b[n2];    //temp variables
	
	for(int x=0;x<n1;x++)
		a[x] = arr[low+x];
	for(int y=0;y<n2;y++)
		b[y] = arr[mid+1+y];
		
	int i=0,j=0,k=low;
	
	while(i<n1 && j<n2)
	{
		if(a[i]<=b[j])	
			arr[k++] = a[i++];
		else
		 	arr[k++] = b[j++];
	}
	
	while(i<n1)
		arr[k++] = a[i++];
			
	while(j<n2)
		arr[k++] = b[j++];		
	
}

void mergesort(int arr[],int low,int high)
{
	if(low<high)
	{
		int mid=(low+high)/2;
		
		mergesort(arr,low,mid);
		mergesort(arr,mid+1,high);
		merge(arr,low,mid,high);
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
	
	float start = clock();
	
	mergesort(arr,0,n-1);
	
	float end = clock();
	
	float tt=end-start/CLOCKS_PER_SEC;
	
	printf("\nSorted Elements are:\n");
	for(i=0;i<n;i++)
		printf("%d ",arr[i]);
		
	printf("\nTotal Time Taken %f",tt);

}
