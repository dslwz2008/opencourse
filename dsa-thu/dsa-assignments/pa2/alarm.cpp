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
//typedef unsigned int uint;
//
//class Point
//{
//public:
//	Point():_x(0),_y(0){}
//	Point(uint x, uint y):_x(x),_y(y){}
//	uint _x,_y;
//};
//
//class Line
//{
//public:
//	Line():_pa(Point(0,0)),_pb(Point(0,0)) {}
//	Line(Point pa, Point pb):_pa(pa),_pb(pb) {}
//	~Line(){}
//	int isOnLine(Point p)
//	{
//		double dx = (double)_pb._x-(double)_pa._x;
//		double dy = (double)_pb._y-(double)_pa._y;
//		double result = ((double)p._y-(double)_pa._y)/dy - ((double)p._x-(double)_pa._x)/dx;
//		if (result > 0)
//		{
//			return 1;
//		}
//		else if(result < 0)
//		{
//			return -1;
//		}
//		else
//		{
//			return 0;
//		}
//	}
//public:
//	Point _pa;
//	Point _pb;
//};
//
//
//int main(){
//
//#ifndef _OJ_
//	freopen("input_alarm.txt", "r", stdin);
//	//freopen("output_lh.txt", "w", stdout);
//#endif
//	int n,m;
//	scanf("%d %d", &n,&m);
//	Line *lines = new Line[n];
//	for (int i = 0; i < n; i++)
//	{
//		int a,b;
//		scanf("%u %u", &a, &b);
//		lines[i]._pa = Point(a,0);
//		lines[i]._pb = Point(0,b);
//	}
//
//	Point *points = new Point[m];
//	for (int i = 0; i < m; i++)
//	{
//		int a,b;
//		scanf("%u %u", &a,&b);
//		points[i]._x = a;
//		points[i]._y = b;
//	}
//
//	for (int i = 0; i < m; i++)
//	{
//		int result = 0;
//		int lo = 0, hi = n+1;//n条线分平面为n+1个区域
//		while(lo < hi)
//		{
//			int mid = (lo + hi) / 2;
//			if (mid == 0)
//			{
//				result = mid;
//				hi = mid;
//				break;
//			}
//			else if (mid == n)
//			{
//				result = mid;
//				lo = mid;
//				break;
//			}
//			else
//			{
//				int upper = lines[mid].isOnLine(points[i]);
//				int bottom = lines[mid-1].isOnLine(points[i]);
//				if (upper<0 && bottom>=0)
//				{
//					result = mid;
//					break;
//				}
//				else if(bottom <= 0)
//				{
//					hi = mid;
//				}
//				else if(upper >= 0)
//				{
//					lo = mid;
//				}
//			}
//		}
//		printf("%d\n",result);
//	}
//	
//	//fclose(stdin);
//	//fclose(stdout);
//	return 0;
//}
