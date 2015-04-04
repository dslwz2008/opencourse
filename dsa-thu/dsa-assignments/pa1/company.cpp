//#include <stdio.h>
//#include <stdlib.h>
//#include <memory.h>
//
//typedef long long lint;
//
//int main(){
//	#ifndef _OJ_
//		freopen("input_company.txt", "r", stdin);
//		//freopen("output_team.txt", "w", stdout);
//	#endif
//	//printf("%d",sizeof(long long));
//	int n = 0, m = 0;
//	scanf("%d %d\n",&n,&m);
//	char *action = new char[m];
//	int *staff = new int[m];
//	lint *code = new lint[m];
//	lint i;
//	for (i=0; i < m; i++)
//	{
//		scanf("%c", &action[i]);
//		switch (action[i])
//		{
//		case 'I':
//			scanf("%d %lld", &staff[i],&code[i]);
//			break;
//		case 'O':
//		case 'Q':
//			scanf("%d", &staff[i]);
//			code[i] = 0;
//			break;
//		case 'C':
//		case 'N':
//			staff[i]=code[i]=0;
//			break;
//		default:
//			break;
//		}
//		getchar();
//		getchar();
//	}
//
//	lint *states = new lint[n];//code value
//	memset(states, -1, sizeof(lint)*n);
//	int *workers = new int[m];//working people
//	//memset(workers, -1, sizeof(uint)*m);
//	lint result = 0,working = 0;
//	for(i = 0; i < m; i++)
//	{
//		char c = action[i];
//		switch(c)
//		{
//		case 'I':
//			if (states[staff[i]-1] == -1)//处理重复登录或登出
//			{
//				workers[working++]=staff[i]-1;
//			}
//			states[staff[i]-1]=code[i];
//			break;
//		case 'O':
//			if (states[staff[i]-1] != -1)
//			{
//				working--;
//			}
//			states[staff[i]-1]=-1;
//			break;
//		case 'C':
//			//memset(states, -1, sizeof(int)*n);
//			for (int j = 0; j < working; j++)
//			{
//				states[workers[j]]=-1;
//			}
//			working = 0;
//			break;
//		case 'Q':
//			result += states[staff[i]-1];
//			break;
//		case 'N':
//			result += working;
//		default:
//			break;
//		}
//	}
//
//	printf("%d",result);
//	//fclose(stdin);
//	//fclose(stdout);
//	return 0;
//}
