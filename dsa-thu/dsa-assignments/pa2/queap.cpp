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

struct ListNode {
	int data; ListNode* pred; ListNode* succ; 
	ListNode() {}
	ListNode ( int e, ListNode* p = NULL, ListNode* s = NULL )
		: data ( e ), pred ( p ), succ ( s ) {}
	ListNode* insertAsPred ( int const& e ){
		ListNode* x = new ListNode ( e, pred, this );
		pred->succ = x; pred = x;
		return x;
	}
	ListNode* insertAsSucc ( int const& e ){
		ListNode* x = new ListNode ( e, this, succ );
		succ->pred = x; succ = x;
		return x;
	}
};

class List {
private:
	int _size; ListNode* header; ListNode* trailer;

protected:
	void init()
	{
		header = new ListNode;
		trailer = new ListNode;
		header->succ = trailer; header->pred = NULL;
		trailer->pred = header; trailer->succ = NULL;
		_size = 0;
	}

	int clear()
	{
		int oldSize = _size;
		while ( 0 < _size ) remove(header->succ);
		return oldSize;
	}

public:
	// ���캯��
	List() { init(); }
	// ��������
	~List(){ clear(); delete header; delete trailer; }

	// ֻ��
	int size() const { return _size; }
	bool empty() const { return _size <= 0; }
	int operator[] ( int r ) const;
	ListNode* first() const { return header->succ; }
	ListNode* last() const { return trailer->pred; }
	bool valid ( ListNode* p )
	{ return p && ( trailer != p ) && ( header != p ); }

	// ��д
	ListNode* insertAsFirst ( int const& e ) //��e�����׽ڵ����
	{  
		_size++; 
		return header->insertAsSucc ( e );  
	}
	ListNode* insertAsLast ( int const& e ) //��e����ĩ�ڵ����
	{  
		_size++; 
		return trailer->insertAsPred ( e );  
	} 
	int remove (ListNode* p) //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
	{
		int e = p->data;
		p->pred->succ = p->succ; p->succ->pred = p->pred;
		delete p; _size--;
		return e;
	}
	//void traverse ( void ( *visit ) (int) ) //��������ָ����Ʊ���
	//{  for (ListNode* p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
	//template <typename VST> //������
	//void traverse ( VST& visit)
	//{  for (ListNode* p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
};

class Stack
{
public:
	//ע�⣺�㲻����Ӹ����public���������,������Ҫ�������������
	Stack();
	bool empty();
	void push(int);
	int pop();
	int top();
private:
	//�˴�������չ
	void init();
	int remove(ListNode* p);
	int _size;
	ListNode* header;
	ListNode* trailer;
};

Stack::Stack()
{
	init();
}

int Stack::remove(ListNode* p)
{
	int e = p->data;
	p->pred->succ = p->succ; p->succ->pred = p->pred;
	delete p; _size--;
	return e;
}

void Stack::init()
{
	header = new ListNode;
	trailer = new ListNode;
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;
}

bool Stack::empty()
{
	return _size <= 0;
}

void Stack::push(int value)
{
	_size++; 
	trailer->insertAsPred (value);
}

int Stack::pop()
{
	return remove(trailer->pred);
}

int Stack::top()
{
	return trailer->pred->data;
}

class Queap
{
public:
	Queap();
	void enqueap(int);
	int dequeap();
	int min();
private:
	Stack inStack;
	Stack outStack;
	List minList;
};

Queap::Queap()
{
}

void Queap::enqueap(int value)
{
	inStack.push(value);
	minList.insertAsLast(value);
	ListNode *temp = minList.last();
	while(temp != NULL && temp->data >= value)
	{
		temp->data = value;
		temp = temp->pred;
	}
}

int Queap::dequeap()
{
	if (outStack.empty())
	{
		while(!inStack.empty())
		{
			outStack.push(inStack.pop());
		}
	}
	minList.remove(minList.first());
	return outStack.pop();
}

int Queap::min()
{
	return minList.first()->data;
}

int main()
{
#ifndef _OJ_
	freopen("input_tunel.txt", "r", stdin);
	//freopen("output_lh.txt", "w", stdout);
#endif
	int n;
	scanf("%d\r\n", &n);
	char *action = new char[n];
	int *height = new int[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%c", &action[i]);
		switch (action[i])
		{
		case 'E':
			scanf("%d", &height[i]);
			break;
		case 'D':
		case 'M':
		default:
			break;
		}
		getchar();
		//getchar();
	}
	
	Queap queap;
	for (int i = 0; i < n; i++)
	{
		switch (action[i])
		{
		case 'E':
			{
				queap.enqueap(height[i]);
				break;
			}
		case 'D':
			{
				int h = queap.dequeap();
				printf("%d\n",h);
				break;
			}
		case 'M':
			printf("%d\n",queap.min());		
			break;
		default:
			break;
		}
	}
	
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
