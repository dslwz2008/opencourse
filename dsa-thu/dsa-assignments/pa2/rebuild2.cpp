//#include <stdio.h>
//#include <stdlib.h>
//
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
//
////��Ҫ�ؽ��ĳ����Լ�����ͺ�������
//bool proper_rebuid(int n, int *preorder, int *inorder, int *postorder)
//{
//	if (n == 0)
//	{
//		return true;
//	}
//	if (n == 1)
//	{
//		if (*preorder == *inorder)
//		{
//			*postorder = *preorder;
//			return true;
//		}
//		return false;
//	}
//	int root = preorder[0];
//	int i = 0;
//	for (; i < n; i++)
//	{
//		if (inorder[i] == root)
//		{
//			break;
//		}
//	}
//	//��������ֳ�2����
//	int llen = i;
//	int rlen = n - 1 - i;
//	//�Ѹ��ڵ�ŵ����ʵ�λ��
//	postorder[n-1] = root;
//	//�ݹ������������
//	if(!proper_rebuid(llen, preorder+1, inorder, postorder)) return false;
//	if(!proper_rebuid(rlen, preorder+llen+1, inorder+llen+1,  postorder+llen)) return false;
//}
//
//int main(){
//#ifndef _OJ_
//	freopen("input_rebuild2.txt", "r", stdin);
//	//freopen("output_lh.txt", "w", stdout);
//#endif
//	int n;
//	scanf("%d\r\n", &n);
//	int *preorder = new int[n];
//	int *postorder = new int[n];
//	int *inorder = new int[n];
//	for (int i = 0; i < n; i++)
//	{
//		scanf("%d", &preorder[i]);
//	}
//	getchar();
//	for (int i = 0; i < n; i++)
//	{
//		scanf("%d", &inorder[i]);
//	}
//
//	if(proper_rebuid(n, preorder, inorder, postorder))
//	{
//		for (int i = 0; i < n; i++)
//		{
//			printf("%d ", postorder[i]);
//		}
//	}
//	else 
//	{
//		printf("-1");
//	}
//	//fclose(stdin);
//	//fclose(stdout);
//	return 0;
//}
