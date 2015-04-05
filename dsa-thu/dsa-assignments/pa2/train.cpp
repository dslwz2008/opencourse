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
//typedef int Rank; //秩
//#define ListNodePosi(T) ListNode<T>* //列表节点位置
//
//template <typename T> struct ListNode { //列表节点模板类（以双向链表形式实现）
//	// 成员
//	T data; ListNodePosi(T) pred; ListNodePosi(T) succ; //数值、前驱、后继
//	// 构造函数
//	ListNode() {} //针对header和trailer的构造
//	ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
//		: data ( e ), pred ( p ), succ ( s ) {} //默认构造器
//
//	// 操作接口
//	ListNodePosi(T) insertAsPred ( T const& e ){
//		ListNodePosi(T) x = new ListNode ( e, pred, this ); //创建新节点
//		pred->succ = x; pred = x; //设置正向链接
//		return x; //返回新节点的位置
//	}
//	ListNodePosi(T) insertAsSucc ( T const& e ){
//		ListNodePosi(T) x = new ListNode ( e, this, succ ); //创建新节点
//		succ->pred = x; succ = x; //设置逆向链接
//		return x; //返回新节点的位置
//	}
//};
//
//template <typename T> class List { //列表模板类
//private:
//	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //规模、头哨兵、尾哨兵
//
//protected:
//	void init()
//	{
//		header = new ListNode<T>; //创建头哨兵节点
//		trailer = new ListNode<T>; //创建尾哨兵节点
//		header->succ = trailer; header->pred = NULL;
//		trailer->pred = header; trailer->succ = NULL;
//		_size = 0; //记录规模
//	}
//
//	int clear()
//	{
//		int oldSize = _size;
//		while ( 0 < _size ) remove ( header->succ ); //反复删除首节点，直至列表变空
//		return oldSize;
//	}
//
//public:
//	// 构造函数
//	List() { init(); } //默认
//	List ( List<T> const& L ) { copyNodes ( L.first(), L._size ); } //整体复制列表L
//	List ( List<T> const& L, Rank r, int n ){ copyNodes ( L[r], n ); } //复制列表L中自第r项起的n项
//	List ( ListNodePosi(T) p, int n ){ copyNodes ( p, n ); }//复制列表中自位置p起的n项
//	// 析构函数
//	~List(){ clear(); delete header; delete trailer; } //释放（包含头、尾哨兵在内的）所有节点
//
//	// 只读访问接口
//	Rank size() const { return _size; } //规模
//	bool empty() const { return _size <= 0; } //判空
//	T& operator[] ( Rank r ) const; //重载，支持循秩访问（效率低）
//	ListNodePosi(T) first() const { return header->succ; } //首节点位置
//	ListNodePosi(T) last() const { return trailer->pred; } //末节点位置
//	bool valid ( ListNodePosi(T) p ) //判断位置p是否对外合法
//	{ return p && ( trailer != p ) && ( header != p ); } //将头、尾节点等同于NULL
//
//	// 可写访问接口
//	ListNodePosi(T) insertAsFirst ( T const& e ) //将e当作首节点插入
//	{  _size++; return header->insertAsSucc ( e );  }
//	ListNodePosi(T) insertAsLast ( T const& e ) //将e当作末节点插入
//	{  _size++; return trailer->insertAsPred ( e );  } 
//	T remove ( ListNodePosi(T) p ) //删除合法位置p处的节点,返回被删除节点
//	{
//		T e = p->data; //备份待删除节点的数值（假定T类型可直接赋值）
//		p->pred->succ = p->succ; p->succ->pred = p->pred; //后继、前驱
//		delete p; _size--; //释放节点，更新规模
//		return e; //返回备份的数值
//	}
//	void traverse ( void ( *visit ) ( T& ) ) //借助函数指针机制遍历
//	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
//	template <typename VST> //操作器
//	void traverse ( VST& visit)
//	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
//}; //List
//
//template <typename T> class Stack: public List<T> { //将列表的首/末端作为栈顶/底
//public: //size()、empty()以及其它开放接口，均可直接沿用
//	void push ( T const& e ) { this->insertAsLast ( e ); } //入栈：等效于将新元素作为列表的首元素插入
//	T pop() { return this->remove ( this->last() ); } //出栈：等效于删除列表的首元素
//	T& top() { return this->last()->data; } //取顶：直接返回列表的首元素
//};
//
//void print_data(int data){
//	data == 0 ? printf("push\n") : printf("pop\n");
//}
//
//int main(){
//
//#ifndef _OJ_
//	freopen("input_train.txt", "r", stdin);
//	//freopen("output_lh.txt", "w", stdout);
//#endif
//	int n,m;
//	scanf("%d %d", &n, &m);
//	if (m == 0)
//	{
//		printf("No\n");
//		return 0;
//	}
//
//	int *target = new int[n];
//	Stack<int> A;
//	for (int i = 0; i < n; i++)
//	{
//		scanf("%d", &target[i]);
//		A.push(n-i);
//	}
//
//	Stack<int> S;
//	List<int> results;
//	bool dead = false;
//	for (int i = 0; i < n; i++)
//	{
//		while (S.empty() || S.top() < target[i])
//		{
//			if (S.size() < m)
//			{
//				S.push(A.pop());
//				results.insertAsLast(0);//printf("push\n");
//			}else
//			{
//				dead = true;
//				break;
//			}
//		}
//		if (dead)
//		{
//			break;
//		}
//		if (S.top() == target[i])
//		{
//			S.pop();
//			results.insertAsLast(1);//printf("pop\n");
//		}
//		else if (S.top() > target[i])
//		{
//			dead=true;//printf("No\n");
//			break;
//		}
//	}
//
//	if (dead)
//	{
//		printf("No\n");
//	}
//	else
//	{
//		results.traverse(print_data);
//	}
//
//	//fclose(stdin);
//	//fclose(stdout);
//	return 0;
//}
