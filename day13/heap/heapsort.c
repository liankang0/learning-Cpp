#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define M 100
#define N 10
#define SWAP(a,b){int tmp;tmp=a;a=b;b=tmp;}

void arrCount(int *arr);
void arrPrint(int *arr);
void AdjustMaxHeap(int *arr, int adjustPos, int arrLen,int (*compare)(const void *,const void *));
void arrHeap(int *arr,int (*compare)(const void *,const void *));
void Mergesort(int *arr,int low,int high);
void arrMerge(int *arr,int low,int mid,int high);

void arrPrint(int *arr)
{
	int i;
	for(i =0;i<N;i++)
	{
		printf("%3d",arr[i]);
	}
	printf("\n");
}

void arrCount(int *arr)
{
	int i,j,k;
	int count[M]={0};
	for(i=0;i<N;i++)
	{
		count[arr[i]]++;
	}
	k=0;
	for(i=0;i<M;i++)
	{
		for(j=0;j<count[i];j++)
		{
			arr[k]=i;
			k++;
		}
	}
}

void AdjustMaxHeap(int *arr, int adjustPos, int arrLen,int (*compare)(const void *,const void *))
{
	int dad=adjustPos;
	int son=dad*2+1;
	while(son<arrLen)
	{
		if(son+1<arrLen&&compare(arr+son,arr+son+1)<0)
		{
			son++;
		}
		if(compare(arr+dad,arr+son)<0)
		{
			SWAP(arr[dad],arr[son]);
			dad=son;
			son=dad*2+1;
		}
		else
		{
			break;
		}
	}
}

void arrHeap(int *arr,int (*compare)(const void*,const void*))
{
	int i;
	for(i=N/2-1;i>=0;i--)
	{
		AdjustMaxHeap(arr,i,N,compare);
	}
	SWAP(arr[0],arr[N-1]);
	for(i=N-1;i>1;i--)
	{
		AdjustMaxHeap(arr,0,i,compare);
		SWAP(arr[0],arr[i-1]);
	}
}

void arrMerge(int *arr,int low,int mid,int high)
{
	int B[N],i,j,k;
	for(i=low;i<=high;i++)//将arr中的元素复制进B数组中
	{
		B[i]=arr[i];
	}
	for(i=low,j=mid+1,k=i;i<=mid&&j<=high;k++)
	{
		if(B[i]<B[j])
		{
			arr[k]=B[i++];
		}
		else
		{
			arr[k]=B[j++];
		}
	}
	while(i<=mid)
	{
		arr[k++]=B[i++];
	}
	while(j<=high)
	{
		arr[k++]=B[j++];
	}
}

void Mergesort(int *arr,int low,int high)
{
	int mid;
	if(low<high)
	{
		mid=(low+high)/2;
		Mergesort(arr,low,mid);
		Mergesort(arr,mid+1,high);
		arrMerge(arr,low,mid,high);
	}
}

int compare(const void *left,const void *right)
{
	int *pa=(int*)left;
	int *pb=(int*)right;
	return *pa-*pb;
}
int main()
{
	int i;
	int *arr=(int*)malloc(N*sizeof(int));
	srand(time(NULL));
	for(i=0;i<N;i++)
	{
		arr[i]=rand()%M;
	}
	arrPrint(arr);
	//arrCount(arr);
	//Mergesort(arr,0,N-1);
	arrHeap(arr,compare);
	arrPrint(arr);
}
