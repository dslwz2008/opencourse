#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////fast io
//const int SZ = 1<<20;
//struct fastio{
//	char inbuf[SZ];
//	char outbuf[SZ];
//	fastio(){
//		setvbuf(stdin,inbuf,_IOFBF,SZ);
//		setvbuf(stdout,outbuf,_IOFBF,SZ);
//	}
//}io;

#define MAX 250

int main(){
#ifndef _OJ_
	freopen("input_bigint.txt", "r", stdin);
	//freopen("output_lh.txt", "w", stdout);
#endif
	int n;
	scanf("%d\r\n", &n);
	char **oprnd1 = new char*[n];
	char **oprnd2 = new char*[n];
	for (int i = 0; i < n; i++)
	{
		char *op1 = new char[MAX];
		scanf("%s",op1);
		oprnd1[i] = op1;
		char *op2 = new char[MAX];
		scanf("%s",op2);
		oprnd2[i] = op2;
	}

	for (int i = 0; i < n; i++)
	{
		int len1 = strlen(oprnd1[i]);
		int len2 = strlen(oprnd2[i]);
		
	}

	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
