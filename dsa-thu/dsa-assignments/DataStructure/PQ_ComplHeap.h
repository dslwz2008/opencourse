#ifndef PQ_COMPLHEAP
#define PQ_COMPLHEAP

#include "Vector.h"
#include "PQ.h"

#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //�ж�PQ[i]�Ƿ�Ϸ�
#define  Parent(i)         ( ( i - 1 ) >> 1 ) //PQ[i]�ĸ��ڵ㣨floor((i-1)/2)��i����������
#define  LastInternal(n)   Parent( n - 1 ) //���һ���ڲ��ڵ㣨��ĩ�ڵ�ĸ��ף�
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]������
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]���Һ���
#define  ParentValid(i)    ( 0 < i ) //�ж�PQ[i]�Ƿ��и���
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //�ж�PQ[i]�Ƿ���һ�����󣩺���
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //�ж�PQ[i]�Ƿ�����������
#define  Bigger(PQ, i, j)  ( lt( PQ[i], PQ[j] ) ? j : i ) //ȡ���ߣ���ʱǰ�����ȣ�
#define  ProperParent(PQ, n, i) /*���ӣ����ࣩ�����еĴ���*/ \
	( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
	( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
	) \
	) //���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���

//��ȫ�����
template <typename T> class PQ_ComplHeap : public PQ<T>, public Vector<T> 
{

protected:
	//����
	Rank percolateDown ( Rank n, Rank i )
	{
		Rank j; //i���䣨���������������У���Ϊ����
		while ( i != ( j = ProperParent ( _elem, n, i ) ) ) //ֻҪi��j����
		{ swap ( _elem[i], _elem[j] ); i = j; } //���߻�λ�������������½����i
		return i; //�������˵ִ��λ�ã���i��j��
	}

	//����
	Rank percolateUp ( Rank i )
	{
		while ( ParentValid ( i ) ) { //ֻҪi�и��ף���δ�ִ�Ѷ�������
			Rank j = Parent ( i ); //��i֮������j
			if ( lt ( _elem[i], _elem[j] ) ) break; //һ����ǰ���Ӳ������������������
			swap ( _elem[i], _elem[j] ); i = j; //���򣬸��ӽ���λ�ã�������������һ��
		} //while
		return i; //�����������յִ��λ��
	}

	void heapify ( Rank n )//Floyd�����㷨
	{
		for ( int i = LastInternal ( n ); InHeap ( n, i ); i-- ) //�Ե׶��ϣ�����
		{
			percolateDown ( n, i ); //���˸��ڲ��ڵ�
		}
	}

public:
	PQ_ComplHeap() { }

	PQ_ComplHeap ( T* A, Rank n ) { copyFrom ( A, 0, n ); heapify ( n ); } //��������

	 //���ձȽ���ȷ�������ȼ����򣬲������
	void insert ( T )
	{
		Vector<T>::insert ( e ); //���Ƚ��´�����������ĩβ
		percolateUp ( _size - 1 ); //�ٶԸô���ʵʩ���˵���
	}

	//��ȡ���ȼ���ߵĴ���
	T getMax()
	{
		return _elem[0];
	}

	//ɾ�����Ԫ��
	T delMax()
	{
		T maxElem = _elem[0]; _elem[0] = _elem[ --_size ]; //ժ���Ѷ����״���������֮��ĩ����
		percolateDown ( _size, 0 ); //���¶Ѷ�ʵʩ����
		return maxElem; //���ش�ǰ���ݵ�������
	}
};

#endif