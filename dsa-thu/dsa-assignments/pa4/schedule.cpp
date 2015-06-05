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

typedef int Rank; //��
#define DEFAULT_CAPACITY  4000000 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

//����ģ����
template <typename T> class Vector { 
protected:
	Rank _size; int _capacity;  T* _elem; //��ģ��������������

	//������������A[lo, hi)
	void copyFrom ( T const* A, Rank lo, Rank hi )
	{
		_elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //����ռ䣬��ģ����
		while ( lo < hi ) //A[lo, hi)�ڵ�Ԫ����һ
			_elem[_size++] = A[lo++]; //������_elem[0, hi - lo)
	}

	//�ռ䲻��ʱ����
	void expand()
	{
		if ( _size < _capacity ) return; //��δ��Աʱ����������
		if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //��������С����
		T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //�����ӱ�
		for ( int i = 0; i < _size; i++ )
			_elem[i] = oldElem[i]; //����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='��
		delete [] oldElem; //�ͷ�ԭ�ռ�
	}

public:
	// ���캯��
	//����Ϊc����ģΪs������Ԫ�س�ʼΪv
	Vector ( int c = DEFAULT_CAPACITY, int s = 0 )
	{ _elem = new T[_capacity = c]; _size = s; } //s<=c

	//�������帴��
	Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } 

	//����
	Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } 

	//�������帴��
	Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); }

	//����
	Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } 

	// ��������
	~Vector() { delete [] _elem; } //�ͷ��ڲ��ռ�

	// ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ

	bool empty() const { return !_size; } //�п�


	// ��д���ʽӿ�
	T& operator[] ( Rank r ) const//�����±������������������������ʽ���ø�Ԫ��
	{
		return _elem[r];
	}

	//���ظ�ֵ���������Ա�ֱ�ӿ�¡����
	Vector<T> & operator= ( Vector<T> const& V)
	{
		if ( _elem ) delete [] _elem; //�ͷ�ԭ������
		copyFrom ( V._elem, 0, V.size() ); //���帴��
		return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
	}

	//����Ԫ��
	Rank insert ( Rank r, T const& e )
	{
		//assert: 0 <= r <= size
		expand(); //���б�Ҫ������
		for ( int i = _size; i > r; i-- )
			_elem[i] = _elem[i-1]; //�Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ
		_elem[r] = e; _size++; //������Ԫ�ز���������
		return r; //������
	}

	//Ĭ����ΪĩԪ�ز���
	Rank insert ( T const& e ) { return insert ( _size, e ); } 

}; //Vector


//��ȫ�����
template <typename T> class PQ_ComplHeap : public Vector<T> 
{

protected:
	//����
	Rank percolateDown ( Rank n, Rank i )
	{
		Rank j; //i���䣨���������������У���Ϊ����
		while ( i != ( j = ProperParent (n, i) ) ) //ֻҪi��j����
		{ swap ( this->_elem[i], this->_elem[j] ); i = j; } //���߻�λ�������������½����i
		return i; //�������˵ִ��λ�ã���i��j��
	}

	//����
	Rank percolateUp ( Rank i )
	{
		while ( parentValid ( i ) ) { //ֻҪi�и��ף���δ�ִ�Ѷ�������
			Rank j = parent ( i ); //��i֮������j
			if ( lt ( this->_elem[i], this->_elem[j] ) ) break; //һ����ǰ���Ӳ������������������
			swap ( this->_elem[i], this->_elem[j] ); i = j; //���򣬸��ӽ���λ�ã�������������һ��
		} //while
		return i; //�����������յִ��λ��
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

	void heapify ( Rank n )//Floyd�����㷨
	{
		for ( int i = lastInternal ( n ); inHeap ( n, i ); i-- ) //�Ե׶��ϣ�����
		{
			percolateDown ( n, i ); //���˸��ڲ��ڵ�
		}
	}

	//�ж�PQ[i]�Ƿ�Ϸ�
	bool inHeap(Rank n, Rank i)
	{
		return -1 < i && i < n;
	}
	//PQ[i]�ĸ��ڵ㣨floor((i-1)/2)��i����������
	Rank parent(Rank i)
	{
		return (i-1) >> 1;
	}
	//���һ���ڲ��ڵ㣨��ĩ�ڵ�ĸ��ף�
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
	//�ж�PQ[i]�Ƿ��и���
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
	//ȡ���ȼ�����
	Rank bigger(Rank i, Rank j)
	{
		return this->_elem[i] < this->_elem[j] ? j : i;
	}

	 /*���ӣ����ࣩ�����еĴ���*/
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

	PQ_ComplHeap ( T* A, Rank n ) { copyFrom ( A, 0, n ); heapify ( n ); } //��������

	//���ձȽ���ȷ�������ȼ����򣬲������
	void insert ( T e ) { //������������ȫ�������
		Vector<T>::insert ( e ); //���Ƚ��´�����������ĩβ
		percolateUp ( this->_size - 1 ); //�ٶԸô���ʵʩ���˵���
	}

	T getMax() {  return this->_elem[0];  } //ȡ���ȼ���ߵĴ���

	T delMax() { //ɾ���ǿ���ȫ����������ȼ���ߵĴ���
		T maxElem = this->_elem[0]; this->_elem[0] = this->_elem[ --this->_size ]; //ժ���Ѷ����״���������֮��ĩ����
		percolateDown ( this->_size, 0 ); //���¶Ѷ�ʵʩ����
		return maxElem; //���ش�ǰ���ݵ�������
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

	//idԽС�����ȼ�Խ��
	bool operator< (const Job &j) const
	{
		if(_id < j._id)
		{
			return false;
		}
		else if(_id == j._id)
		{
			//�ֵ���С������
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
