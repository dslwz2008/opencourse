#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SZ = 1<<20;
struct fastio{
	char inbuf[SZ];
	char outbuf[SZ];
	fastio(){
		setvbuf(stdin,inbuf,_IOFBF,SZ);
		setvbuf(stdout,outbuf,_IOFBF,SZ);
	}
}io;

int g_counts =  1;

struct Food
{
	int votes;
	char name[41];
	Food():votes(0)
	{
		name[0] = '\0';
	};
};

bool IsPrime(int n)
{
	for(int i=2; i<n/2; i++)
	{
		if(n%i==0)
			return false;
	}
	return true;
}

int nextPrime(int n)
{
	while(!IsPrime(n++));
	return --n;
}

int SDBMHash(char *str)
{
    unsigned int hash = 0;
 
    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
 
    return (hash & 0x7FFFFFFF)%g_counts;
}

int RSHash(char *str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
 
    while (*str)
    {
        hash = hash * a + (*str++);
        a *= b;
    }
    return (hash & 0x7FFFFFFF)%g_counts;
}

int JSHash(char *str)
{
    unsigned int hash = 1315423911;
 
    while (*str)
    {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }
 
    return (hash & 0x7FFFFFFF)%g_counts;
}

int main(){
#ifndef _OJ_
	freopen("input_hashtable.txt", "r", stdin);
	//freopen("output_lh.txt", "w", stdout);
#endif


	int n;
	scanf("%d\r\n",&n);
	g_counts = nextPrime(4*n);
	Food *ht = new Food[g_counts];

	for(int i=0; i<n; i++)
	{
		char str[41];
		scanf("%s",str);
		getchar();
		int hashNum = RSHash(str);

		//≥ÂÕª
		while(ht[hashNum].votes > 0)
		{
			//≤ªœ‡µ»
			if (strcmp(ht[hashNum].name, str)!=0)
			{
				hashNum = ++hashNum % g_counts;
			}
			else
			{
				if(ht[hashNum].votes == 1)
				{
					printf("%s\n",str);
				}
				break;
			}

		}
		ht[hashNum].votes++;

		if(ht[hashNum].votes == 1)
		{
			strcpy(ht[hashNum].name,str);
		}
	}
	
	delete []ht;
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
