#include <stdio.h>
#include <stdlib.h>

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

typedef unsigned int uint;

struct Point
{
	uint x,y;
};

class Line
{
public:
	Line(){}
	Line(Point pa, Point pb)
	{
		_pa=pa;
		_pb=pb;
	}
	~Line(){}
	int isOnLine(Point p)
	{
		long long int y = p.y + (_pb.y-_pa.y)*(p.x-_pa.x)/(_pb.x-_pa.x);
		if (y > 0)
		{
			return 1;
		}
		else if(y < 0)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
private:
	Point _pa;
	Point _pb;
};


int main(){

#ifndef _OJ_
	freopen("input_tunel.txt", "r", stdin);
	//freopen("output_lh.txt", "w", stdout);
#endif
	int n,m;
	scanf("%d %d", &n,&m);
	Line *lines = new Line[n];
	for (int i = 0; i < n; i++)
	{
		int a,b;
		scanf("%d %d", &a, &b);

	}
	
	
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
