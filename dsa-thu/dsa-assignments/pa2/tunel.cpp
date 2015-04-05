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

typedef int Rank; //秩
typedef unsigned int uint;
#define ListNodePosi(T) ListNode<T>* //列表节点位置

template <typename T> struct ListNode { //列表节点模板类（以双向链表形式实现）
	// 成员
	T data; ListNodePosi(T) pred; ListNodePosi(T) succ; //数值、前驱、后继
	// 构造函数
	ListNode() {} //针对header和trailer的构造
	ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
		: data ( e ), pred ( p ), succ ( s ) {} //默认构造器

	// 操作接口
	ListNodePosi(T) insertAsPred ( T const& e ){
		ListNodePosi(T) x = new ListNode ( e, pred, this ); //创建新节点
		pred->succ = x; pred = x; //设置正向链接
		return x; //返回新节点的位置
	}
	ListNodePosi(T) insertAsSucc ( T const& e ){
		ListNodePosi(T) x = new ListNode ( e, this, succ ); //创建新节点
		succ->pred = x; succ = x; //设置逆向链接
		return x; //返回新节点的位置
	}
};

template <typename T> class List { //列表模板类
private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //规模、头哨兵、尾哨兵

protected:
	void init()
	{
		header = new ListNode<T>; //创建头哨兵节点
		trailer = new ListNode<T>; //创建尾哨兵节点
		header->succ = trailer; header->pred = NULL;
		trailer->pred = header; trailer->succ = NULL;
		_size = 0; //记录规模
	}

	int clear()
	{
		int oldSize = _size;
		while ( 0 < _size ) remove ( header->succ ); //反复删除首节点，直至列表变空
		return oldSize;
	}

public:
	// 构造函数
	List() { init(); } //默认
	List ( List<T> const& L ) { copyNodes ( L.first(), L._size ); } //整体复制列表L
	List ( List<T> const& L, Rank r, int n ){ copyNodes ( L[r], n ); } //复制列表L中自第r项起的n项
	List ( ListNodePosi(T) p, int n ){ copyNodes ( p, n ); }//复制列表中自位置p起的n项
	// 析构函数
	~List(){ clear(); delete header; delete trailer; } //释放（包含头、尾哨兵在内的）所有节点

	// 只读访问接口
	Rank size() const { return _size; } //规模
	bool empty() const { return _size <= 0; } //判空
	T& operator[] ( Rank r ) const; //重载，支持循秩访问（效率低）
	ListNodePosi(T) first() const { return header->succ; } //首节点位置
	ListNodePosi(T) last() const { return trailer->pred; } //末节点位置
	bool valid ( ListNodePosi(T) p ) //判断位置p是否对外合法
	{ return p && ( trailer != p ) && ( header != p ); } //将头、尾节点等同于NULL

	// 可写访问接口
	ListNodePosi(T) insertAsFirst ( T const& e ) //将e当作首节点插入
	{  _size++; return header->insertAsSucc ( e );  }
	ListNodePosi(T) insertAsLast ( T const& e ) //将e当作末节点插入
	{  _size++; return trailer->insertAsPred ( e );  } 
	T remove ( ListNodePosi(T) p ) //删除合法位置p处的节点,返回被删除节点
	{
		T e = p->data; //备份待删除节点的数值（假定T类型可直接赋值）
		p->pred->succ = p->succ; p->succ->pred = p->pred; //后继、前驱
		delete p; _size--; //释放节点，更新规模
		return e; //返回备份的数值
	}
	void traverse ( void ( *visit ) ( T& ) ) //借助函数指针机制遍历
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
	template <typename VST> //操作器
	void traverse ( VST& visit)
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
}; //List

template <typename T> class Queue: public List<T> { //队列模板类（继承List原有接口）
public: //size()、empty()以及其它开放接口均可直接沿用
	void enqueue ( T const& e ) { this->insertAsLast ( e ); } //入队：尾部插入
	T dequeue() { return this->remove ( this->first() ); } //出队：首部删除
	T& front() { return this->first()->data; } //队首
};

template <typename T> class Deque: public List<T> { //双端队列模板类（继承List原有接口）
public: 
	void insertFront ( T const& e ) { this->insertAsFirst ( e ); } //从前面插入
	T removeFront() { return this->remove ( this->first() ); } //从前面删除
	void insertRear ( T const& e ) { this->insertAsLast ( e ); } //尾部插入
	T removeRear() { return this->remove ( this->last() ); } //尾部删除
	T& front() { return this->first()->data; } //队首
	T& rear() { return this->last()->data; }
};

struct ElemEx{
	uint key;
	uint counter;
}elemex;

int main(){

#ifndef _OJ_
	freopen("input_tunel.txt", "r", stdin);
	//freopen("output_lh.txt", "w", stdout);
#endif
	int n;
	scanf("%d\r\n", &n);
	char *action = new char[n];
	uint *height = new uint[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%c", &action[i]);
		switch (action[i])
		{
		case 'E':
			scanf("%u", &height[i]);
			break;
		case 'D':
		case 'M':
		default:
			break;
		}
		getchar();
		//getchar();
	}

	Queue<uint> q;
	Deque<ElemEx> p1;
	for (int i = 0; i < n; i++)
	{
		switch (action[i])
		{
		case 'E':
			{
				q.enqueue(height[i]);
				int a = 1;
				while(!p1.empty() && p1.rear().key <= height[i])
				{
					a += p1.removeRear().counter;
				}
				ElemEx elem; elem.key=height[i]; elem.counter=a;
				p1.insertRear(elem);
				break;
			}
		case 'D':
			{
				uint h = q.dequeue();
				if(!(--p1.front().counter))
				{
					p1.removeFront();
				}
				printf("%u\n",h);
				break;
			}
		case 'M':
			printf("%u\n",p1.front().key);
			break;
		default:
			break;
		}
	}

	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
