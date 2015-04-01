#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define NUM 32767

int main(){
	#ifndef _OJ_
		freopen("input_hospital.txt", "r", stdin);
		//freopen("output_team.txt", "w", stdout);
	#endif
	
	int n = 0;
	scanf("%d", &n);
	//int *pos = new int[NUM];
	//memset(pos,0,sizeof(int));
	int *wgt = new int[NUM];
	memset(wgt,0,sizeof(int)*NUM);
	for (int i = 0; i < n; i++)
	{
		int p,w;
		scanf("%d %d", &p, &w);
		wgt[p]+=w;
	}
	
	bool first = true;
	int minPos = 0, minWgt = 0;
	for (int i = 0; i < NUM; i++)
	{
		if (wgt[i]==0)
		{
			continue;
		}

		if (first){
			minPos = i;
			first = false;
		}
		
		int newPos = i;
		int newWgt = wgt[i];
		int d = newPos - minPos;
		d = d>0?d:-d;
		minWgt+=d*newWgt;

		//计算newpos到各点的最小代价
		int testPos = i, testWgt = 0;
		for (int j = i-1; j >= 0; j--)
		{
			if (wgt[j]==0)
			{
				continue;
			}
			int frontPos = j;
			int frontWgt = wgt[j];
			int d = testPos - frontPos;
			d = d>0?d:-d;
			testWgt+=d*frontWgt;
		}
		
		if (testWgt <minWgt || 
			(testWgt == minWgt && testPos<minPos))
		{
			minWgt=testWgt;
			minPos=testPos;
		}
	}

	printf("%d\n%d",minPos,minWgt);
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
