#ifndef FIB_H
#define FIB_H

//Fibonacci数列类
class Fib {
private:
	int f, g; //f = fib(k - 1), g = fib(k)。均为int型，很快就会数值溢出
public:
	//初始化为不小于n的最小Fibonacci项
	Fib ( int n ) 
	{ 
		f = 1; g = 0; while ( g < n ) next(); 
	} //fib(-1), fib(0)，O(log_phi(n))时间

	int get()
	{
		return g; 
	} //获取当前Fibonacci项，O(1)时间

	int next()
	{ 
		g += f; f = g - f; return g; 
	} //转至下一Fibonacci项，O(1)时间

	int prev()
	{
		f = g - f; g -= f; return g; 
	} //转至上一Fibonacci项，O(1)时间
};

#endif
