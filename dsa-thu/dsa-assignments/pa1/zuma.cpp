#include <stdio.h>
#include <string.h>

typedef int Rank; //秩
#define ListNodePosi(T) ListNode<T>* //列表节点位置

void print_data(char data){
	printf("%c", data);
}

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
	ListNodePosi(T) first() const { return header->succ; } //首节点位置
	ListNodePosi(T) last() const { return trailer->pred; } //末节点位置
	// 可写访问接口
	ListNodePosi(T) insertAsFirst ( T const& e ) //将e当作首节点插入
	{  _size++; return header->insertAsSucc ( e );  }
	ListNodePosi(T) insertAsLast ( T const& e ) //将e当作末节点插入
	{  _size++; return trailer->insertAsPred ( e );  }
	ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e )
	{  _size++; return p->insertAsSucc ( e );  } //将e当作p的后继插入
	ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e )
	{  _size++; return p->insertAsPred ( e );  }//将e当作p的前驱插入
	ListNodePosi(T) insertAt ( Rank rank, T const& e)
	{
		Rank idx = 0;
		ListNodePosi(T) p = NULL;
		if (empty())
		{
			p = header;
		}
		else
		{
			p = first();
		}
		
		while (idx < rank && p != NULL)
		{
			p = p->succ; idx++;
		}		
		_size++; 
		return p->insertAsPred ( e );  
	} //将e当作p的后继插入

	T remove ( ListNodePosi(T) p )//删除合法节点p，返回其数值
	{ 
		T e = p->data; //备份待删除节点的数值（假定T类型可直接赋值）
		p->pred->succ = p->succ; p->succ->pred = p->pred; //后继、前驱
		delete p; p = NULL; _size--; //释放节点，更新规模
		return e; //返回备份的数值
	}

	// 遍历
	void traverse ( void (* visit) ( T& ) )
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
	template <typename VST> //操作器
	void traverse ( VST& visit)
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
}; //List

bool check(ListNodePosi(char) node, ListNodePosi(char) *from, ListNodePosi(char) *to){
	ListNodePosi(char) curr = node;
	int x = 0, y = 0;
	while (curr->pred != NULL && curr->pred->data == node->data)
	{
		x++;
		curr = curr->pred;
	}
	*from = curr;
	curr = node;
	while (curr->succ != NULL && curr->succ->data == node->data)
	{
		y++;
		curr = curr->succ;
	}
	*to = curr->succ;//指向第一个变化的元素
	return x + y >= 2;
}

int main(){

#ifndef _OJ_
	freopen("input_zuma.txt", "r", stdin);
	//freopen("output_zuma.txt", "w", stdout);
#endif

	//read
	int n = 0;
	char s[10001];
	scanf("%s", &s);
	int length = strlen(s);
	List<char> list;
	ListNodePosi(char) cur = list.insertAsFirst(s[0]);
	for (int i = 1; i < length; i++)
	{
		cur = list.insertA(cur, s[i]);
	}

	//print list
	if (list.empty())
	{
		printf("-");
	}
	else
	{
		list.traverse(print_data);
	}
	printf("\n");

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int pos = -1;
		char c = '\0';
		scanf("%d %c", &pos, &c);
		//printf("%d %c", pos, c);
		ListNodePosi(char) node = list.insertAt(pos, c);
		ListNodePosi(char) from = NULL; ListNodePosi(char) to = NULL;
		while (check(node, &from, &to))
		{
			while (from != to)
			{
				from = from->succ;
				list.remove(from->pred);
			}
			node = from;
		}
		//print list
		if (list.empty())
		{
			printf("-");
		}
		else
		{
			list.traverse(print_data);
		}
		printf("\n");
	}

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