#include "stdafx.h"

#include <stdio.h> 
#include <string.h> 
#include <iostream>
#include <algorithm>

using namespace std;



void printArr(int a[], int n)
{
	for (int i = 0; i<n; i++)
		cout << a[i] << " ";
	cout << endl;
}

/*
void swap(int *a, int *b)
{
int temp;
temp = *a;
*a = *b;
*b = temp;
}
*/

void permutation(int *arr, int start, int end)
{
	if (start == end)
	{
		printArr(arr, end + 1);
		return;
	}
	int i;
	for (i = start; i <= end; i++)
	{
		//swap((arr + i), (arr + start));
		//permutation(arr, start + 1, end);
		//swap((arr + i), (arr + start));
		swap(arr[0], arr[end - 1]);
		permutation(arr, start + 1, end);
		swap(arr[i], arr[end - 1]);

	}
}

int main()
{
	int arr[4] = { 1,2,3,4 };
	int n = sizeof arr / sizeof arr[0];
	permutation(arr, 0, n - 1);
	system("pause");
}


