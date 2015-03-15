
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

void merge(uint *arr, uint lo, uint mi, uint hi)
{
	uint *A = arr + lo;
	//¸¨ÖúÊı×é¿Õ¼ä
	int lb = mi - lo;
	uint *B = new uint[lb];
	for (uint i = 0; i < lb; i++)
	{
		B[i] = A[i];
	}

	int lc = hi - mi;
	uint *C = arr + mi;
	uint i = 0, j = 0, k = 0;
	while((j < lb) || (k < lc)){
		if ((j < lb) && (!(k < lc) || B[j] <= C[k]))
		{
			A[i++] = B[j++];
		}
		if ((k < lc) && (!(j < lb) || C[k] < B[j]))
		{
			A[i++] = C[k++];
		}
	}
}

void mergeSort(uint *arr, uint lo, uint hi)
{
	if (hi - lo < 2)
	{
		return;
	}
	uint mi = (lo+hi)>>1;
	mergeSort(arr, lo, mi);
	mergeSort(arr, mi, hi);
	merge(arr, lo, mi, hi);
}

int main(){

#ifndef _OJ_
	freopen("input_lh.txt", "r", stdin);
	//freopen("output_lh.txt", "w", stdout);
#endif

	uint n;
	scanf("%d", &n);
	uint *x = new uint[n];
	uint *y = new uint[n];
	for (uint i = 0; i < n; i++)
	{
		scanf("%d %d", &x[i], &y[i]);
		//printf("%d %d\n", x[i], y[i]);
	}
	uint T[10]={1324,61576,7,88,245,236,77,9876,567,666};
	uint AUX[10]={0,1,2,3,4,5,6,7,8,9};
	mergeSort(T, 0, 10);
	for (uint i = 0; i < 10; i++)
	{
		printf("%d \t", T[i]);
	}
	uint counter = 0;
	//

	printf("%d\n", counter);
	fclose(stdin);
	//fclose(stdout);
	return 0;
}
