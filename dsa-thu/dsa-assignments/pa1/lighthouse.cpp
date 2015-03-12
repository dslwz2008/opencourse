#include <stdio.h>

typedef unsigned int uint;

typedef struct lighthouse
{
	uint x;
	uint y;
} LightHouse;

bool lightable(LightHouse lh1, LightHouse lh2){
	if ((lh2.x > lh1.x && lh2.y > lh1.y) || 
		(lh2.x < lh1.x && lh2.y < lh1.y))
	{
		return true;
	}
	return false;
}

int main(){

#ifndef _OJ_
	freopen("input_lh.txt", "r", stdin);
	//freopen("output_lh.txt", "w", stdout);
#endif

	uint n;
	scanf("%d", &n);
	LightHouse *lhs = new LightHouse[n];
	for (uint i = 0; i < n; i++)
	{
		LightHouse lh;
		scanf("%d %d", &lh.x, &lh.y);
		//printf("%d %d\n", lh.x, lh.y);
		lhs[i] = lh;
	}

	uint counter = 0;
	for (uint i = 0; i < n; i++)
	{
		for (uint j = i + 1; j < n; j++)
		{
			if (lightable(lhs[i], lhs[j]))
			{
				counter++;
			}
		}
	}

	printf("%d\n", counter);
	fclose(stdin);
	//fclose(stdout);
	return 0;
}