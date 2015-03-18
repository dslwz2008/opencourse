//
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef unsigned long long ulint;
//
//void swap(ulint * a, ulint * b) {
//	ulint tmp = * a;
//	* a = * b;
//	* b = tmp;
//}
//
//ulint partition(ulint * ary, ulint * ary2, ulint len, ulint pivot_i) {
//	ulint i = 0;
//	ulint small_len = pivot_i;
//	ulint pivot = ary[pivot_i];
//	swap(&ary[pivot_i], &ary[pivot_i + (len - 1)]);
//	swap(&ary2[pivot_i], &ary2[pivot_i + (len - 1)]);
//	for (; i < len; i++) {
//		if (ary[pivot_i + i] < pivot) {
//			swap(&ary[pivot_i + i], &ary[small_len]);
//			swap(&ary2[pivot_i + i], &ary2[small_len]);
//			small_len++;
//		}
//	}
//	swap(&ary[pivot_i + (len - 1)], &ary[small_len]);
//	swap(&ary2[pivot_i + (len - 1)], &ary2[small_len]);
//	return small_len;
//}
//
//void quick_sort(ulint * ary, ulint * ary2, ulint len) {
//	if (len == 0 || len == 1) 
//		return;
//
//	ulint small_len = partition(ary, ary2, len, 0);
//	quick_sort(ary, ary2, small_len);
//	quick_sort(&ary[small_len + 1], &ary2[small_len + 1], len - small_len - 1);
//}
//
////void merge(ulint *arr, ulint lo, ulint mi, ulint hi)
////{
////	ulint *A = arr + lo;
////	//辅助数组空间
////	int lb = mi - lo;
////	ulint *B = new ulint[lb];//前向量
////	for (ulint i = 0; i < lb; i++)
////	{
////		B[i] = A[i];
////	}
////
////	int lc = hi - mi;
////	ulint *C = arr + mi;//后向量
////	ulint i = 0, j = 0, k = 0;
////	while((j < lb) || (k < lc)){
////		if ((j < lb) && (!(k < lc) || B[j] <= C[k]))
////		{
////			A[i++] = B[j++];
////		}
////		if ((k < lc)){
////			if(!(j < lb))
////			{
////				A[i++] = C[k++];
////			}else if(C[k] < B[j])
////			{
////				A[i++] = C[k++];
////				counter++;
////			}
////		}
////	}
////}
////
////void merge_sort(ulint *arr, ulint lo, ulint hi)
////{
////	if (hi - lo < 2)
////	{
////		return;
////	}
////	ulint mi = (lo+hi)>>1;
////	merge_sort(arr, lo, mi);
////	merge_sort(arr, mi, hi);
////	merge(arr, lo, mi, hi);
////}
//
//void inverse_pair(ulint *A, ulint x, ulint y, ulint* cnt, ulint *T) {
//	if(y - x > 1) {
//		ulint m = x + (y - x) / 2;     //划分
//		ulint p = x, q = m, i = x;
//		inverse_pair(A, x, m, cnt, T);      //递归求解
//		inverse_pair(A, m, y, cnt, T);      //递归求解
//		while(p < m || q < y) {
//			if(q >= y || (p < m && A[p] <= A[q])) T[i++] = A[p++];   //从左半数组复制到临时空间
//			else {
//				T[i++] = A[q++];    //从右半数组复制到临时空间
//				*cnt += m-p;  //更新累加器
//			}
//		}
//		for(i = x; i < y; ++i) A[i] = T[i];   //从辅助空间复制回A数组
//	}
//}
//
//int main(){
//
//#ifndef _OJ_
//	freopen("input_lh.txt", "r", stdin);
//	//freopen("output_lh.txt", "w", stdout);
//#endif
//	//printf("%d\n",sizeof(unsigned long long));
//	ulint n;
//	scanf("%llu", &n);
//	ulint *x = new ulint[n];
//	ulint *y = new ulint[n];
//	ulint *t = new ulint[n];
//	for (ulint i = 0; i < n; i++)
//	{
//		scanf("%llu %llu", &x[i], &y[i]);
//		//printf("%d %d\n", x[i], y[i]);
//	}
//	//uint T[10]={1324,61576,7,88,245,236,77,9876,567,666};
//	//uint AUX[10]={0,1,2,3,4,5,6,7,8,9};
//	//mergeSort(T, 0, 10);
//	quick_sort(x, y, n);
//	//for (uint i = 0; i < 10; i++)
//	//{
//	//	printf("%d \t", x[i]);
//	//}
//	//printf("\n");
//	//for (uint i = 0; i < 10; i++)
//	//{
//	//	printf("%d \t", y[i]);
//	//}
//	//merge_sort(y, 0, n);
//	ulint cnt = 0;
//	inverse_pair(y, 0, n, &cnt, t);
//	ulint result = n * (n-1) / 2 - cnt;
//	printf("%llu\n", result );
//	//fclose(stdin);
//	//fclose(stdout);
//	return 0;
//}
