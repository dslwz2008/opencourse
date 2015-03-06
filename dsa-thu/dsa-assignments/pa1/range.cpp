#include <stdio.h>

typedef unsigned int uint;

uint bin_search(uint *A, uint n, uint target, bool *found){
	uint lo =0, hi = n;
	while(lo < hi){
		uint mi = (lo + hi) / 2;
		if (A[mi] < target)
		{
			lo = mi + 1;
		}
		else if(A[mi] > target){
			hi = mi;
		}
		else{
			*found = true;
			return mi;
		}
	}
	return --lo;
}

void swap(uint * a, uint * b) {
	uint tmp = * a;
	* a = * b;
	* b = tmp;
}

size_t partition(uint * ary, size_t len, size_t pivot_i) {
	size_t i = 0;
	size_t small_len = pivot_i;
	uint pivot = ary[pivot_i];
	swap(&ary[pivot_i], &ary[pivot_i + (len - 1)]);
	for (; i < len; i++) {
		if (ary[pivot_i + i] < pivot) {
			swap(&ary[pivot_i + i], &ary[small_len]);
			small_len++;
		}
	}
	swap(&ary[pivot_i + (len - 1)], &ary[small_len]);
	return small_len;
}

void quick_sort(uint * ary, size_t len) {
	if (len == 0 || len == 1) 
		return;

	size_t small_len = partition(ary, len, 0);
	quick_sort(ary, small_len);
	quick_sort(&ary[small_len + 1], len - small_len - 1);
}

int main(){

#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	//read
	uint n = 0, m = 0;
	scanf("%d %d", &n, &m);
	uint *A = new uint[n];
	for (uint i = 0; i < n; i++)
	{
		scanf("%d", &A[i]);
	}
	quick_sort(A, n);
	uint *M = new uint[2*m];
	for (uint i = 0; i < 2*m; i+=2)
	{
		scanf("%d %d", &M[i], &M[i+1]);
		if (M[i] > M[i+1])
		{
			swap(&M[i], &M[i+1]);
		}
	}

	//compute
	for (uint i = 0; i < 2*m; i+=2)
	{
		bool founda = false, foundb = false;
		uint a = bin_search(A, n, M[i], &founda);
		uint b = bin_search(A, n, M[i+1], &foundb);
		uint count = (founda) ? b-a+1 : b-a;
		printf("%d\n", count);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
