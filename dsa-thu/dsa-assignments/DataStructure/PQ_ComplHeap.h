#ifndef PQ_COMPLHEAP
#define PQ_COMPLHEAP

#include "Vector.h"
#include "PQ.h"

#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //判断PQ[i]是否合法
#define  Parent(i)         ( ( i - 1 ) >> 1 ) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define  LastInternal(n)   Parent( n - 1 ) //最后一个内部节点（即末节点的父亲）
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]的左孩子
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]的右孩子
#define  ParentValid(i)    ( 0 < i ) //判断PQ[i]是否有父亲
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //判断PQ[i]是否有两个孩子
#define  Bigger(PQ, i, j)  ( lt( PQ[i], PQ[j] ) ? j : i ) //取大者（等时前者优先）
#define  ProperParent(PQ, n, i) /*父子（至多）三者中的大者*/ \
	( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
	( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
	) \
	) //相等时父节点优先，如此可避免不必要的交换

//完全二叉堆
template <typename T> class PQ_ComplHeap : public PQ<T>, public Vector<T> 
{

protected:
	//下滤
	Rank percolateDown ( Rank n, Rank i )
	{
		Rank j; //i及其（至多两个）孩子中，堪为父者
		while ( i != ( j = ProperParent ( _elem, n, i ) ) ) //只要i非j，则
		{ swap ( _elem[i], _elem[j] ); i = j; } //二者换位，并继续考查下降后的i
		return i; //返回下滤抵达的位置（亦i亦j）
	}

	//上滤
	Rank percolateUp ( Rank i )
	{
		while ( ParentValid ( i ) ) { //只要i有父亲（尚未抵达堆顶），则
			Rank j = Parent ( i ); //将i之父记作j
			if ( lt ( _elem[i], _elem[j] ) ) break; //一旦当前父子不再逆序，上滤旋即完成
			swap ( _elem[i], _elem[j] ); i = j; //否则，父子交换位置，并继续考查上一层
		} //while
		return i; //返回上滤最终抵达的位置
	}

	void heapify ( Rank n )//Floyd建堆算法
	{
		for ( int i = LastInternal ( n ); InHeap ( n, i ); i-- ) //自底而上，依次
		{
			percolateDown ( n, i ); //下滤各内部节点
		}
	}

public:
	PQ_ComplHeap() { }

	PQ_ComplHeap ( T* A, Rank n ) { copyFrom ( A, 0, n ); heapify ( n ); } //批量构造

	 //按照比较器确定的优先级次序，插入词条
	void insert ( T )
	{
		Vector<T>::insert ( e ); //首先将新词条接至向量末尾
		percolateUp ( _size - 1 ); //再对该词条实施上滤调整
	}

	//读取优先级最高的词条
	T getMax()
	{
		return _elem[0];
	}

	//删除最大元素
	T delMax()
	{
		T maxElem = _elem[0]; _elem[0] = _elem[ --_size ]; //摘除堆顶（首词条），代之以末词条
		percolateDown ( _size, 0 ); //对新堆顶实施下滤
		return maxElem; //返回此前备份的最大词条
	}
};

#endif