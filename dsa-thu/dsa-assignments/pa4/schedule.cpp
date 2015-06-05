#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <climits>

//fast io
const int SZ = 1<<20;
struct fastio{
	char inbuf[SZ];
	char outbuf[SZ];
	fastio(){
		setvbuf(stdin,inbuf,_IOFBF,SZ);
		setvbuf(stdout,outbuf,_IOFBF,SZ);
	}
}io;

typedef int Rank; //秩
#define DEFAULT_CAPACITY  4000000 //默认的初始容量（实际应用中可设置为更大）

//向量模板类
template <typename T> class Vector { 
protected:
	Rank _size; int _capacity;  T* _elem; //规模、容量、数据区

	//复制数组区间A[lo, hi)
	void copyFrom ( T const* A, Rank lo, Rank hi )
	{
		_elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //分配空间，规模清零
		while ( lo < hi ) //A[lo, hi)内的元素逐一
			_elem[_size++] = A[lo++]; //复制至_elem[0, hi - lo)
	}

	//空间不足时扩容
	void expand()
	{
		if ( _size < _capacity ) return; //尚未满员时，不必扩容
		if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //不低于最小容量
		T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //容量加倍
		for ( int i = 0; i < _size; i++ )
			_elem[i] = oldElem[i]; //复制原向量内容（T为基本类型，或已重载赋值操作符'='）
		delete [] oldElem; //释放原空间
	}

public:
	// 构造函数
	//容量为c、规模为s、所有元素初始为v
	Vector ( int c = DEFAULT_CAPACITY, int s = 0 )
	{ _elem = new T[_capacity = c]; _size = s; } //s<=c

	//数组整体复制
	Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } 

	//区间
	Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } 

	//向量整体复制
	Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); }

	//区间
	Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } 

	// 析构函数
	~Vector() { delete [] _elem; } //释放内部空间

	// 只读访问接口
	Rank size() const { return _size; } //规模

	bool empty() const { return !_size; } //判空


	// 可写访问接口
	T& operator[] ( Rank r ) const//重载下标操作符，可以类似于数组形式引用各元素
	{
		return _elem[r];
	}

	//重载赋值操作符，以便直接克隆向量
	Vector<T> & operator= ( Vector<T> const& V)
	{
		if ( _elem ) delete [] _elem; //释放原有内容
		copyFrom ( V._elem, 0, V.size() ); //整体复制
		return *this; //返回当前对象的引用，以便链式赋值
	}

	//插入元素
	Rank insert ( Rank r, T const& e )
	{
		//assert: 0 <= r <= size
		expand(); //若有必要，扩容
		for ( int i = _size; i > r; i-- )
			_elem[i] = _elem[i-1]; //自后向前，后继元素顺次后移一个单元
		_elem[r] = e; _size++; //置入新元素并更新容量
		return r; //返回秩
	}

	//默认作为末元素插入
	Rank insert ( T const& e ) { return insert ( _size, e ); } 

}; //Vector


//完全二叉堆
template <typename T> class PQ_ComplHeap : public Vector<T> 
{

protected:
	//下滤
	Rank percolateDown ( Rank n, Rank i )
	{
		Rank j; //i及其（至多两个）孩子中，堪为父者
		while ( i != ( j = ProperParent (n, i) ) ) //只要i非j，则
		{ swap ( this->_elem[i], this->_elem[j] ); i = j; } //二者换位，并继续考查下降后的i
		return i; //返回下滤抵达的位置（亦i亦j）
	}

	//上滤
	Rank percolateUp ( Rank i )
	{
		while ( parentValid ( i ) ) { //只要i有父亲（尚未抵达堆顶），则
			Rank j = parent ( i ); //将i之父记作j
			if ( lt ( this->_elem[i], this->_elem[j] ) ) break; //一旦当前父子不再逆序，上滤旋即完成
			swap ( this->_elem[i], this->_elem[j] ); i = j; //否则，父子交换位置，并继续考查上一层
		} //while
		return i; //返回上滤最终抵达的位置
	}

	bool lt(const T& l, const T& r)
	{
		return l < r;
	}

	void swap(T& a, T& b)
	{
		T t = a;
		a = b;
		b = t;
	}

	void heapify ( Rank n )//Floyd建堆算法
	{
		for ( int i = lastInternal ( n ); inHeap ( n, i ); i-- ) //自底而上，依次
		{
			percolateDown ( n, i ); //下滤各内部节点
		}
	}

	//判断PQ[i]是否合法
	bool inHeap(Rank n, Rank i)
	{
		return -1 < i && i < n;
	}
	//PQ[i]的父节点（floor((i-1)/2)，i无论正负）
	Rank parent(Rank i)
	{
		return (i-1) >> 1;
	}
	//最后一个内部节点（即末节点的父亲）
	Rank lastInternal(Rank n)
	{
		return parent(n-1);
	}
	Rank lChild(Rank i)
	{
		return 1 + (i << 1);
	}
	Rank rChild(Rank i)
	{
		return (1 + i) << 1;
	}
	//判断PQ[i]是否有父亲
	bool parentValid(Rank i)
	{
		return 0 < i;
	}
	bool lChildValid(Rank n, Rank i)
	{
		return inHeap(n, lChild(i));
	}
	bool rChildValid(Rank n, Rank i)
	{
		return inHeap(n, rChild(i));
	}
	//取优先级大者
	Rank bigger(Rank i, Rank j)
	{
		return this->_elem[i] < this->_elem[j] ? j : i;
	}

	 /*父子（至多）三者中的大者*/
	Rank ProperParent(Rank n, Rank i)
	{
		if (rChildValid(n, i))
		{
			return bigger(bigger(i, lChild(i)), rChild(i));
		}
		else if (lChildValid(n, i))
		{
			return bigger(i, lChild(i));
		}
		else
		{
			return i;
		}
	}

public:
	PQ_ComplHeap() { }

	PQ_ComplHeap ( T* A, Rank n ) { copyFrom ( A, 0, n ); heapify ( n ); } //批量构造

	//按照比较器确定的优先级次序，插入词条
	void insert ( T e ) { //将词条插入完全二叉堆中
		Vector<T>::insert ( e ); //首先将新词条接至向量末尾
		percolateUp ( this->_size - 1 ); //再对该词条实施上滤调整
	}

	T getMax() {  return this->_elem[0];  } //取优先级最高的词条

	T delMax() { //删除非空完全二叉堆中优先级最高的词条
		T maxElem = this->_elem[0]; this->_elem[0] = this->_elem[ --this->_size ]; //摘除堆顶（首词条），代之以末词条
		percolateDown ( this->_size, 0 ); //对新堆顶实施下滤
		return maxElem; //返回此前备份的最大词条
	}

};

typedef unsigned int uint;

struct Job
{
	uint _id;
	char* _name;
	Job():_id(0), _name(NULL){}
	Job(uint id, char *name):_id(id), _name(name){}

	Job& operator = (const Job &j)
	{
		_id = j._id; _name = j._name;
		return *this;
	}

	//id越小，优先级越高
	bool operator< (const Job &j) const
	{
		if(_id < j._id)
		{
			return false;
		}
		else if(_id == j._id)
		{
			//字典序小者优先
			if (strcmp(_name, j._name)<0)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
};


int main(){
#ifndef _OJ_
	freopen("input_schedule.txt", "r", stdin);
	//freopen("output_lh.txt", "w", stdout);
#endif

	int n,m;
	scanf("%d %d\r\n",&n, &m);
	//if (m == 0 || n==0)
	//{
	//	return 0;
	//}

	Job *jobs = new Job[n];
	for(int i=0; i<n; i++)
	{
		char *temp = new char[9];
		scanf("%u %s", &jobs[i]._id, temp);
		jobs[i]._name = temp;
		//getchar();
	}

	PQ_ComplHeap<Job> pqJobs(jobs, n);
	int idx = 0;
	while(idx < m && !pqJobs.empty())
	{
		Job jTemp = pqJobs.delMax();
		printf("%s\n", jTemp._name);
		if (jTemp._id < UINT_MAX/2)
		{
			jTemp._id = jTemp._id << 1;
			pqJobs.insert(jTemp);
		}
		idx++;
	}
	
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
