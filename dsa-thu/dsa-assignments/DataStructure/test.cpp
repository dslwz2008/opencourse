#include <stdio.h>
#include <stdlib.h>
#include <time.h> //通常用当前时刻设置随机种子
#include "Vector.h"
#include "List.h"
#include "GraphMatrix.h"

/******************************************************************************************
 * 在[0, range)内随机生成一个数
 ******************************************************************************************/
static int dice ( int range ) { return rand() % range; } //取[0, range)中的随机整数
static int dice ( int lo, int hi ) { return lo + rand() % ( hi - lo ); } //取[lo, hi)中的随机整数
static float dice ( float range ) { return rand() % ( 1000 * ( int ) range ) / ( float ) 1000.; }
static double dice ( double range ) { return rand() % ( 1000 * ( int ) range ) / ( double ) 1000.; }
static char dice ( char range ) { return ( char ) ( 32 + rand() % 96 ); }

void testVector()
{
	Vector<int> v;
	for(int i = 0; i < 100; i++)
	{
		v.insert(dice(100));
	}
	for (int i = 0; i < 100; i++)
	{
		printf("%d\t", v[i]);
		if ((i+1) % 10 == 0)
		{
			printf("\n");
		}
	}
	printf("%d\n", v.size());
	printf("%d\n", v.find(50));
	//printf("%d\n", v.search(49));
	v.remove(1, 100);
	printf("%d\n", v.size());
}

void testList()
{
	List<int> l;
	l.insertAsFirst(856);
}

void testGraph()
{
	GraphMatrix<char, int> g;
	int n = 8, e= 10;
	for (int i = 0; i < n; i++)
	{
		g.insert('a'+i);
	}
	//for ( int i = 0; i < n; i++ ) 
	//{
	//	g.vertex ( i ) = 'A' + i;
	//}
	g.insert(1,1,0,2);
	g.insert(1,1,0,5);
	g.insert(1,1,0,7);
	g.insert(1,1,1,2);
	g.insert(1,1,1,3);
	g.insert(1,1,1,6);
	g.insert(1,1,2,0);
	g.insert(1,1,2,1);
	g.insert(1,1,3,1);
	g.insert(1,1,3,7);
	g.insert(1,1,4,5);
	g.insert(1,1,4,6);
	g.insert(1,1,5,0);
	g.insert(1,1,5,6);
	g.insert(1,1,6,1);
	g.insert(1,1,6,4);
	g.insert(1,1,6,5);
	g.insert(1,1,7,0);
	g.insert(1,1,7,3);
	g.bfs();
}

int main()
{
	testVector();
	testList();
	testGraph();
	
	return 0;
}