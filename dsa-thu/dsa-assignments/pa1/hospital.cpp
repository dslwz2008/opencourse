//#include <stdio.h>
//#include <stdlib.h>
//#include <memory.h>
//
//#define NUM 32768
//typedef unsigned long long ulint;
//
////计算其中一点到其他点的权重距离乘积的总和
//ulint calcwgt(int cor, int *pos, ulint *wgt, int n)
//{
//	ulint total = 0;
//	for (int i = 0; i< n;i++)
//	{
//		int d = pos[i]-pos[cor];
//		d = d>0?d:-d;
//		total += (d*wgt[i]);
//	}
//	return total;
//}
//
//int main(){
//	#ifndef _OJ_
//		freopen("input_hospital.txt", "r", stdin);
//		//freopen("output_team.txt", "w", stdout);
//	#endif
//	
//	int n = 0;
//	scanf("%d", &n);
//	int *pos = new int[NUM];
//	memset(pos,0,sizeof(int)*NUM);
//	ulint *totalwgt = new ulint[NUM];//注意：有重复的点坐标
//	memset(totalwgt,0,sizeof(ulint)*NUM);
//	for (int i = 0; i < n; i++)
//	{
//		int p,w;
//		scanf("%d %d", &p, &w);
//		//pos[i]=p;
//		totalwgt[p]+=w;
//	}
//
//	//跳出来不为0的
//	ulint *wgt = new ulint[NUM];
//	//memset(wgt,0,sizeof(ulint)*NUM);
//	int count = 0;
//	for (int i = 0; i < NUM; i++)
//	{
//		if (totalwgt[i] != 0)
//		{
//			wgt[count]=totalwgt[i];
//			pos[count]=i;
//			++count;
//		}
//	}
//
//	int left = 0, right=count-1, mid = 0, midmid=0;
//	ulint mid_wgt=0, midmid_wgt=0;
//	while(right-left>1)
//	{
//		mid = (right + left)/2;
//		midmid = (mid + right)/2;
//		mid_wgt = calcwgt(mid, pos, wgt, count);
//		midmid_wgt = calcwgt(midmid, pos, wgt, count);
//		if (mid_wgt <= midmid_wgt)
//		{
//			right=midmid;
//		}
//		else
//		{
//			left=mid;
//		}		
//	}
//
//	int minPos = 0;
//	ulint minWgt = 0;
//	ulint left_wgt = calcwgt(left, pos, wgt, count);
//	ulint right_wgt = calcwgt(right, pos, wgt, count);
//	if (left_wgt<=right_wgt)
//	{
//		minPos=left; minWgt=left_wgt;
//	}
//	else
//	{
//		minPos=right;minWgt=right_wgt;
//	}	
//
//	printf("%d\n%llu",pos[minPos],minWgt);
//	//fclose(stdin);
//	//fclose(stdout);
//	return 0;
//}
