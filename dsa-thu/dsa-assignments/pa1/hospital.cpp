#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef unsigned int uint;

int main(){
	#ifndef _OJ_
		freopen("input_company.txt", "r", stdin);
		//freopen("output_team.txt", "w", stdout);
	#endif
	//printf("%d",sizeof(uint));
	uint n = 0, m = 0;
	scanf("%u %u\n",&n,&m);
	char *action = new char[m];
	uint *staff = new uint[m];
	uint *code = new uint[m];
	uint i;
	for (i=0; i < m; i++)
	{
		scanf("%c", &action[i]);
		switch (action[i])
		{
		case 'I':
			scanf("%u %u", &staff[i],&code[i]);
			break;
		case 'O':
		case 'Q':
			scanf("%u", &staff[i]);
			code[i] = 0;
			break;
		case 'C':
		case 'N':
			staff[i]=code[i]=0;
			break;
		default:
			break;
		}
		getchar();
	}

	uint *states = new uint[n];
	memset(states, -1, sizeof(uint)*n);
	uint result = 0,working = 0;
	for(i = 0; i < m; i++)
	{
		char c = action[i];
		switch(c)
		{
		case 'I':
			if (states[staff[i]-1] == -1)//first time
			{
				working++;
			}
			states[staff[i]-1]=code[i];
			break;
		case 'O':
			if (states[staff[i]-1] != -1)
			{
				working--;
			}
			states[staff[i]-1]=-1;
			break;
		case 'C':
			memset(states, -1, sizeof(int)*n);
			working = 0;
			break;
		case 'Q':
			result += states[staff[i]-1];
			break;
		case 'N':
			result += working;
		default:
			break;
		}
	}

	printf("%d",result);
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
