#ifndef LIST_H
#define LIST_H

#include "listNode.h" //引入列表节点类

//列表模板类
template <typename T> class List 
{ 

private:
	//规模、头哨兵、尾哨兵
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;

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

	//复制列表中自位置p起的n项
	void copyNodes ( ListNodePosi(T), int )
	{
		//p合法，且至少有n-1个真后继节点
		init(); //创建头、尾哨兵节点并做初始化
		while ( n-- ) { insertAsLast ( p->data ); p = p->succ; } //将起自p的n项依次作为末节点插入
	}

	//有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
	void merge ( ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int )
	{
		// assert:  this.valid(p) && rank(p) + n <= size && this.sorted(p, n)
		//          L.valid(q) && rank(q) + m <= L._size && L.sorted(q, m)
		// 注意：在归并排序之类的场合，有可能 this == L && rank(p) + n = rank(q)
		ListNodePosi(T) pp = p->pred; //借助前驱（可能是header），以便返回前 ...
		while ( 0 < m ) //在q尚未移出区间之前
			if ( ( 0 < n ) && ( p->data <= q->data ) ) //若p仍在区间内且v(p) <= v(q)，则
			{ if ( q == ( p = p->succ ) ) break; n--; } //p归入合并的列表，并替换为其直接后继
			else //若p已超出右界或v(q) < v(p)，则
			{ insertB ( p, L.remove ( ( q = q->succ )->pred ) ); m--; } //将q转移至p之前
			p = pp->succ; //确定归并后区间的（新）起点
	}

	//对从p开始连续的n个节点归并排序
	void mergeSort ( ListNodePosi(T)&, int )
	{ 
		//valid(p) && rank(p) + n <= size
		/*DSA*/printf ( "\tMERGEsort [%3d]\n", n );
		if ( n < 2 ) return; //若待排序范围已足够小，则直接返回；否则...
		int m = n >> 1; //以中点为界
		ListNodePosi(T) q = p; for ( int i = 0; i < m; i++ ) q = q->succ; //均分列表
		mergeSort ( p, m ); mergeSort ( q, n - m ); //对前、后子列表分别排序
		merge ( p, m, *this, q, n - m ); //归并
	} //注意：排序后，p依然指向归并后区间的（新）起点

public:
	// 构造函数
	List() { init(); } //默认

	//复制列表中自位置p起的n项（assert: p为合法位置，且至少有n-1个后继节点）
	List ( ListNodePosi(T) p, int n ) 
	{ 
		copyNodes ( p, n ); 
	}

	//整体复制列表L
	List ( List<T> const& L ) 
	{ 
		copyNodes ( L.first(), L._size ); 
	}

	//复制L中自第r项起的n项（assert: r+n <= L._size）
	List ( List<T> const& L, int r, int n ) 
	{ 
		copyNodes ( L[r], n ); 
	}

	//列表析构器
	~List()
	{
		//清空列表，释放头、尾哨兵节点
		clear(); delete header; delete trailer; 
	}

	// 只读访问接口
	Rank size() const { return _size; } //规模

	bool empty() const { return _size <= 0; } //判空

	//重载，支持循秩访问（效率低）
	T& operator[] ( Rank r ) const
	{ 
		//assert: 0 <= r < size
		ListNodePosi(T) p = first(); //从首节点出发
		while ( 0 < r-- ) p = p->succ; //顺数第r个节点即是
		return p->data; //目标节点，返回其中所存元素
	}

	ListNodePosi(T) first() const { return header->succ; } //首节点位置

	ListNodePosi(T) last() const { return trailer->pred; } //末节点位置

	bool valid ( ListNodePosi(T) p ) //判断位置p是否对外合法
	{ return p && ( trailer != p ) && ( header != p ); } //将头、尾节点等同于NULL

	//判断列表是否已排序
	int disordered() const
	{ 
		int n = 0; ListNode<T>* p = first();
		for ( int i = 0; i < _size - 1; p = p->succ, i++ )
			if ( p->data > p->succ->data ) n++;
		return n;
	}

	//无序列表查找
	ListNodePosi(T) find ( T const& e ) const 
	{ return find ( e, _size, trailer ); }

	//无序区间查找
	ListNodePosi(T) find ( T const& e, int n, ListNodePosi(T) p ) const
	{
		while ( 0 < n-- ) //（0 <= n <= rank(p) < _size）对于p的最近的n个前驱，从右向左
			if ( e == ( p = p->pred )->data ) return p; //逐个比对，直至命中或范围越界
		return NULL; //p越出左边界意味着区间内不含e，查找失败
	}

	//有序列表查找
	ListNodePosi(T) search ( T const& e ) const 
	{ return search ( e, _size, trailer ); }

	//有序区间查找
	ListNodePosi(T) search ( T const& e, int n, ListNodePosi(T) p ) const
	{
		// assert: 0 <= n <= rank(p) < _size
		while ( 0 <= n-- ) //对于p的最近的n个前驱，从右向左逐个比较
		{ 
			if ( ( ( p = p->pred )->data ) <= e )
				break; //直至命中、数值越界或范围越界
		}
		// assert: 至此位置p必符合输出语义约定——尽管此前最后一次关键码比较可能没有意义（等效于与-inf比较）
		return p; //返回查找终止的位置
	} //失败时，返回区间左边界的前驱（可能是header）——调用者可通过valid()判断成功与否

	//在p及其n-1个后继中选出最大者
	ListNodePosi(T) selectMax ( ListNodePosi(T) p, int n )
	{
		ListNodePosi(T) max = p; //最大者暂定为首节点p
		for ( ListNodePosi(T) cur = p; 1 < n; n-- ) //从首节点p出发，将后续节点逐一与max比较
			if ( !lt ( ( cur = cur->succ )->data, max->data ) ) //若当前元素不小于max，则
				max = cur; //更新最大元素位置记录
		return max; //返回最大节点位置
	}

	ListNodePosi(T) selectMax() { return selectMax ( header->succ, _size ); } //整体最大者

	// 可写访问接口
	//将e当作首节点插入
	ListNodePosi(T) insertAsFirst ( T const& e )
	{
		_size++; return header->insertAsSucc ( e );
	}

	//将e当作末节点插入
	ListNodePosi(T) insertAsLast ( T const& e )
	{
		_size++; return trailer->insertAsPred ( e );  
	}

	//将e当作p的后继插入
	ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e )
	{
		_size++; return p->insertAsSucc ( e );
	}
	
	//将e当作p的前驱插入
	ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e )
	{
		_size++; return p->insertAsPred ( e );
	}

	//删除合法位置p处的节点,返回被删除节点
	T remove ( ListNodePosi(T) p )
	{
		T e = p->data; //备份待删除节点的数值（假定T类型可直接赋值）
		p->pred->succ = p->succ; p->succ->pred = p->pred; //后继、前驱
		delete p; _size--; //释放节点，更新规模
		return e; //返回备份的数值
	}

	void merge ( List<T>& L ) { merge ( first(), size, L, L.first(), L._size ); } //全列表归并

	void sort ( ListNodePosi(T) p, int n ) //列表区间排序
	{
		mergeSort ( p, n );
	}

	void sort() { sort ( first(), _size ); } //列表整体排序

	//无序去重
	int deduplicate()
	{
		if ( _size < 2 ) return 0; //平凡列表自然无重复
		int oldSize = _size; //记录原规模
		ListNodePosi(T) p = header; Rank r = 0; //p从首节点开始
		while ( trailer != ( p = p->succ ) ) { //依次直到末节点
			ListNodePosi(T) q = find ( p->data, r, p ); //在p的r个（真）前驱中查找雷同者
			q ? remove ( q ) : r++; //若的确存在，则删除之；否则秩加一
		} //assert: 循环过程中的任意时刻，p的所有前驱互不相同
		return oldSize - _size; //列表规模变化量，即被删除元素总数
	}

	//有序去重
	int uniquify()
	{
		if ( _size < 2 ) return 0; //平凡列表自然无重复
		int oldSize = _size; //记录原规模
		ListNodePosi(T) p = first(); ListNodePosi(T) q; //p为各区段起点，q为其后继
		while ( trailer != ( q = p->succ ) ) //反复考查紧邻的节点对(p, q)
			if ( p->data != q->data ) p = q; //若互异，则转向下一区段
			else remove ( q ); //否则（雷同），删除后者
			return oldSize - _size; //列表规模变化量，即被删除元素总数
	}

	//前后倒置（习题）
	void reverse()
	{
		ListNodePosi(T) p = header; ListNodePosi(T) q = trailer; //头、尾节点
		for ( int i = 1; i < _size; i += 2 ) //（从首、末节点开始）由外而内，捉对地
			swap ( ( p = p->succ )->data, ( q = q->pred )->data ); //交换对称节点的数据项
	}

	// 遍历
	void traverse ( void (* visit) ( T& ) )
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }

	template <typename VST> //操作器
	void traverse ( VST& visit)
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
}; //List

#endif