#ifndef LISTNODE_H
#define LISTNODE_H

typedef int Rank; //秩
#define ListNodePosi(T) ListNode<T>* //列表节点位置

//列表节点模板类（以双向链表形式实现）
template <typename T> struct ListNode {
	//数值、前驱、后继
	T data;
	ListNodePosi(T) pred;
	ListNodePosi(T) succ;

	// 构造函数
	//针对header和trailer的构造
	ListNode() {} 
	ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
		: data ( e ), pred ( p ), succ ( s ) {} //默认构造器

	// 操作接口
	//紧靠当前节点之前插入新节点
	ListNodePosi(T) insertAsPred ( T const& e ) 
	{
		ListNodePosi(T) x = new ListNode ( e, pred, this ); //创建新节点
		pred->succ = x; pred = x; //设置正向链接
		return x; //返回新节点的位置
	}

	//紧随当前节点之后插入新节点
	ListNodePosi(T) insertAsSucc ( T const& e )
	{
		ListNodePosi(T) x = new ListNode ( e, this, succ ); //创建新节点
		succ->pred = x; succ = x; //设置逆向链接
		return x; //返回新节点的位置
	}
};

#endif