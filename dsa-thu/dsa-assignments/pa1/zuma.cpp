#include <stdio.h>

typedef unsigned int uint;

int main(){

#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	////read
	//uint n = 0, m = 0;
	//scanf("%d %d", &n, &m);
	//uint *A = new uint[n];
	//for (uint i = 0; i < n; i++)
	//{
	//	scanf("%d", &A[i]);
	//}
	//quick_sort(A, n);
	//uint *M = new uint[2*m];
	//for (uint i = 0; i < 2*m; i+=2)
	//{
	//	scanf("%d %d", &M[i], &M[i+1]);
	//	if (M[i] > M[i+1])
	//	{
	//		swap(&M[i], &M[i+1]);
	//	}
	//}

	////compute
	//for (uint i = 0; i < 2*m; i+=2)
	//{
	//	bool founda = false, foundb = false;
	//	uint a = bin_search(A, n, M[i], &founda);
	//	uint b = bin_search(A, n, M[i+1], &foundb);
	//	uint count = (founda) ? b-a+1 : b-a;
	//	printf("%d\n", count);
	//}

	//fclose(stdin);
	//fclose(stdout);
	return 0;
}