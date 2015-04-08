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
	// 构造函数
	List() { init(); }
	// 析构函数
	~List(){ clear(); delete header; delete trailer; }

	// 只读
	int size() const { return _size; }
	bool empty() const { return _size <= 0; }
	int operator[] ( int r ) const;
	ListNode* first() const { return header->succ; }
	ListNode* last() const { return trailer->pred; }
	bool valid ( ListNode* p )
	{ return p && ( trailer != p ) && ( header != p ); }

	// 可写
	ListNode* insertAsFirst ( int const& e ) //将e当作首节点插入
	{  
		_size++; 
		return header->insertAsSucc ( e );  
	}
	ListNode* insertAsLast ( int const& e ) //将e当作末节点插入
	{  
		_size++; 
		return trailer->insertAsPred ( e );  
	} 
	int remove (ListNode* p) //删除合法位置p处的节点,返回被删除节点
	{
		int e = p->data;
		p->pred->succ = p->succ; p->succ->pred = p->pred;
		delete p; _size--;
		return e;
	}
	//void traverse ( void ( *visit ) (int) ) //借助函数指针机制遍历
	//{  for (ListNode* p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
	//template <typename VST> //操作器
	//void traverse ( VST& visit)
	//{  for (ListNode* p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
};

class Stack
{
public:
	//注意：你不能添加更多的public函数或变量,如有需要可添加析构函数
	Stack();
	bool empty();
	void push(int);
	int pop();
	int top();
private:
	//此处可以扩展
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
