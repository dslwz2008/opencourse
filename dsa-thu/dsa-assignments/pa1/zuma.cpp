#include <stdio.h>

typedef int Rank; //秩
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
	} //紧靠当前节点之前插入新节点

	ListNodePosi(T) insertAsSucc ( T const& e ){
		ListNodePosi(T) x = new ListNode ( e, this, succ ); //创建新节点
		succ->pred = x; succ = x; //设置逆向链接
		return x; //返回新节点的位置
	} //紧随当前节点之后插入新节点

};

template <typename T> class List {
private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //规模、头哨兵、尾哨兵

protected:
	void init(){ //列表初始化，在创建列表对象时统一调用
		header = new ListNode<T>; //创建头哨兵节点
		trailer = new ListNode<T>; //创建尾哨兵节点
		header->succ = trailer; header->pred = NULL;
		trailer->pred = header; trailer->succ = NULL;
		_size = 0; //记录规模
	}
	int clear(){ //清空列表
		int oldSize = _size;
		while ( 0 < _size ) remove ( header->succ ); //反复删除首节点，直至列表变空
		return oldSize;
	}

public:
	// 构造函数
	List() { init(); } //默认
	// 析构函数
	~List(){ clear(); delete header; delete trailer; } //释放（包含头、尾哨兵在内的）所有节点
	// 只读访问接口
	Rank size() const { return _size; } //规模
	bool empty() const { return _size <= 0; } //判空
	// 可写访问接口
	ListNodePosi(T) insertAsFirst ( T const& e ); //将e当作首节点插入
	ListNodePosi(T) insertAsLast ( T const& e ); //将e当作末节点插入
	ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e ); //将e当作p的后继插入
	ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e ); //将e当作p的前驱插入
	T remove ( ListNodePosi(T) p ); //删除合法位置p处的节点,返回被删除节点
}; //List

int main(){

#ifndef _OJ_
	freopen("input_zuma.txt", "r", stdin);
	freopen("output_zuma.txt", "w", stdout);
#endif

	////read
	//uint n = 0, m = 0;
	//scanf("%d %d", &n, &m);
	//uint *A = new uint[n];
	//for (uint i = 0; i < n; i++)
	//{
	//	scanf("%d", &A[i]);
	//}
	//quick_sort(A, n);
	//uint *M = new uint[2*m];
	//for (uint i = 0; i < 2*m; i+=2)
	//{
	//	scanf("%d %d", &M[i], &M[i+1]);
	//	if (M[i] > M[i+1])
	//	{
	//		swap(&M[i], &M[i+1]);
	//	}
	//}

	////compute
	//for (uint i = 0; i < 2*m; i+=2)
	//{
	//	bool founda = false, foundb = false;
	//	uint a = bin_search(A, n, M[i], &founda);
	//	uint b = bin_search(A, n, M[i+1], &foundb);
	//	uint count = (founda) ? b-a+1 : b-a;
	//	printf("%d\n", count);
	//}

	//fclose(stdin);
	//fclose(stdout);
	return 0;
}