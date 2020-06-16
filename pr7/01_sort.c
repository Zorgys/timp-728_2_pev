#include <stdio.h>

void buildHeap(int arr[], int n, int i, int len, FILE *file)
{
	int max = i;

	int left = 2*i + 1;
	int right = 2*i + 2;

	if (left < n && arr[i] < arr[left])
	{
		max = left;
	}

	if (right < n && arr[max] < arr[right])
	{
		max = right;
	}
	if (max != i)
	{
		int tmp = arr[i];
		arr[i] = arr[max];
		arr[max] = tmp;

		for (int i = 0; i<len-1; i++){
		  fprintf(file, "%d ", arr[i]);
		}
		fprintf(file, "%d", arr[len-1]);
		fprintf(file, "\n");

		buildHeap(arr, n, max, len, file);
	}
}

void heapSort(int arr[], int n, FILE *file)
{

	for (int i = 0; i<n-1; i++)
	{
		fprintf(file, "%d ", arr[i]);
	}
	fprintf(file, "%d", arr[n-1]);
	fprintf(file, "\n");


	for (int i = n; i >= 0; i--)
	{
		buildHeap(arr, n, i, n, file);
	}

	for (int i=n-1; i>=1; i--)
	{
		int tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;

		for (int i = 0; i<n-1; i++)
		{
		  fprintf(file, "%d ", arr[i]);
		}
		fprintf(file, "%d", arr[n-1]);
		fprintf(file, "\n");

		buildHeap(arr, i, 0, n, file);
	}
}

void qsort(int arr[], int len, int a, int b, FILE *file)
{
	int left = a;
	int right = b;
	int br = arr[(a+b)/2];

	while(left <= right)
	{
		while(arr[left] < br)
		{
			left++;
		}

		while(arr[right] > br)
		{
			right--;
		}

		if(left <= right) 
		{

			int temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;


			for(int i=0; i<len; i++)
			{
				fprintf(file, "%d ", arr[i]);
			}
			fprintf(file, "\n");

			left++;
			right--;
		}
	}

	if(a < right)
	{
		qsort(arr, len, a, right, file);
	}

	if(b > left)
	{
		qsort(arr, len, left, b, file);
	}
}

//Qsort - quick sort
void Qsort(int arr[], int len, FILE *file)
{
	int a = 0;
	int b = len - 1;
	qsort(arr, len, a, b, file);
}

int main()
{
	FILE *file1;
	file1 = fopen("quicksort.log", "w");

	FILE *file2;
	file2 = fopen("heapsort.log", "w");

	int n, answer;

	scanf("%d", &n);

	int arr1[n];
	int arr2[n];
	int i;

	for (i = 0; i<n; i++)
	{
		int a;
		scanf("%d", &a);
		arr1[i] = a;
		arr2[i] = a;
	}

	Qsort(arr1, n, file1);
	heapSort(arr2, n, file2);

	for (int i = 0; i<n; i++)
	{
		printf("%d ", arr1[i]);
	}
	printf("\n");

	fclose(file1);
	fclose(file2);
	return 0;
}