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
//void proper_rebuid(int n, int *preorder, int *postorder, int *inorder)
//{
//	if (n == 1)
//	{
//		*inorder = *preorder;
//		return;
//	}
//	int root = preorder[0];
//	int lroot = preorder[1];
//	int i = 0;
//	for (; i < n; i++)
//	{
//		if (postorder[i] == lroot)
//		{
//			break;
//		}
//	}
//	//��������ֳ�2����
//	int llen = i + 1;
//	int rlen = n - 2 - i;
//	//�Ѹ��ڵ�ŵ����ʵ�λ��
//	inorder[i+1] = root;
//	//�ݹ������������
//	proper_rebuid(llen, preorder+1, postorder, inorder);
//	proper_rebuid(rlen, preorder+llen+1, postorder+llen, inorder+llen+1);
//}
//
//int main(){
//#ifndef _OJ_
//	freopen("input_rebuild.txt", "r", stdin);
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
//		scanf("%d", &postorder[i]);
//	}
//
//	proper_rebuid(n, preorder, postorder, inorder);
//
//	for (int i = 0; i < n; i++)
//	{
//		printf("%d ", inorder[i]);
//	}
//	//fclose(stdin);
//	//fclose(stdout);
//	return 0;
//}
