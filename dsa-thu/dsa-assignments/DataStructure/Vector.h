#ifndef VECTOR_H
#define VECTOR_H

typedef int Rank; //秩
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）

//向量模板类
template <typename T> class Vector { 
protected:
	Rank _size; int _capacity;  T* _elem; //规模、容量、数据区

	//复制数组区间A[lo, hi)
	void copyFrom ( T const* A, Rank lo, Rank hi )
	{
		_elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //分配空间，规模清零
		while ( lo < hi ) //A[lo, hi)内的元素逐一
			_elem[_size++] = A[lo++]; //复制至_elem[0, hi - lo)
	}

	//空间不足时扩容
	void expand()
	{
		if ( _size < _capacity ) return; //尚未满员时，不必扩容
		if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //不低于最小容量
		T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //容量加倍
		for ( int i = 0; i < _size; i++ )
			_elem[i] = oldElem[i]; //复制原向量内容（T为基本类型，或已重载赋值操作符'='）
		/*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
		delete [] oldElem; //释放原空间
	}

	//装填因子过小时压缩
	void shrink() 
	{
		if ( _size < _capacity ) return; //尚未满员时，不必扩容
		if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //不低于最小容量
		T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //容量加倍
		for ( int i = 0; i < _size; i++ )
			_elem[i] = oldElem[i]; //复制原向量内容（T为基本类型，或已重载赋值操作符'='）
		/*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
		delete [] oldElem; //释放原空间
	}

	//选取最大元素
	Rank max ( Rank lo, Rank hi )
	{
		Rank mx = hi;
		while ( lo < hi-- ) //逆向扫描
			if ( _elem[hi] > _elem[mx] ) //且严格比较
				mx = hi; //故能在max有多个时保证后者优先，进而保证selectionSort稳定
		return mx;
	}

	//有序向量的归并
	void merge ( Rank lo, Rank mi, Rank hi )
	{ 
		//各自有序的子向量[lo, mi)和[mi, hi)
		T* A = _elem + lo; //合并后的向量A[0, hi - lo) = _elem[lo, hi)
		int lb = mi - lo; T* B = new T[lb]; //前子向量B[0, lb) = _elem[lo, mi)
		for ( Rank i = 0; i < lb; B[i] = A[i++] ); //复制前子向量
		int lc = hi - mi; T* C = _elem + mi; //后子向量C[0, lc) = _elem[mi, hi)
		for ( Rank i = 0, j = 0, k = 0; ( j < lb ) || ( k < lc ); ) { //B[j]和C[k]中的小者续至A末尾
			if ( ( j < lb ) && ( ! ( k < lc ) || ( B[j] <= C[k] ) ) ) A[i++] = B[j++];
			if ( ( k < lc ) && ( ! ( j < lb ) || ( C[k] <  B[j] ) ) ) A[i++] = C[k++];
		}
		delete [] B; //释放临时空间B
	} //归并后得到完整的有序向量[lo, hi)

	//向量归并排序
	void mergeSort ( Rank lo, Rank hi )
	{
		//0 <= lo < hi <= size
		if ( hi - lo < 2 ) return; //单元素区间自然有序，否则...
		int mi = ( lo + hi ) >> 1; mergeSort ( lo, mi ); mergeSort ( mi, hi ); //以中点为界分别排序
		merge ( lo, mi, hi ); //归并
	}

	// 二分查找算法（版本C）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
	Rank binSearch ( T const& e, Rank lo, Rank hi ) const
	{
		while ( lo < hi ) //每步迭代仅需做一次比较判断，有两个分支
		{ 
			Rank mi = ( lo + hi ) >> 1; //以中点为轴点
			( e < _elem[mi] ) ? hi = mi : lo = mi + 1; //经比较后确定深入[lo, mi)或(mi, hi)
		} //成功查找不能提前终止
		return --lo; //循环结束时，lo为大于e的元素的最小秩，故lo - 1即不大于e的元素的最大秩
	} //有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置

public:
	// 构造函数
	//容量为c、规模为s、所有元素初始为v
	Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) 
	{ _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } //s<=c

	//数组整体复制
	Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } 

	//区间
	Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } 

	//向量整体复制
	Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); }

	//区间
	Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } 

	// 析构函数
	~Vector() { delete [] _elem; } //释放内部空间

	// 只读访问接口
	Rank size() const { return _size; } //规模

	bool empty() const { return !_size; } //判空
	
	//判断向量是否已排序
	int disordered() const
	{
		int n = 0; //计数器
		for ( int i = 1; i < _size; i++ ) //逐一检查_size - 1对相邻元素
			if ( _elem[i - 1] > _elem[i] ) n++; //逆序则计数
		return n; //向量有序当且仅当n = 0
	}

	//无序向量整体查找
	Rank find ( T const& e ) const { return find ( e, 0, _size ); } 

	//无序向量区间查找
	Rank find ( T const& e, Rank lo, Rank hi ) const
	{
		while ( ( lo < hi-- ) && ( e != _elem[hi] ) ); //从后向前，顺序查找
		return hi; //若hi < lo，则意味着失败；否则hi即命中元素的秩
	}

	//有序向量整体查找
	Rank search ( T const& e ) const 
	{
		return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); 
	}

	//有序向量区间查找
	Rank search ( T const& e, Rank lo, Rank hi ) const
	{
		return binSearch ( e, lo, hi );
	}

	// 可写访问接口
	T& operator[] ( Rank r ) const//重载下标操作符，可以类似于数组形式引用各元素
	{
		return _elem[r];
	}

	//重载赋值操作符，以便直接克隆向量
	Vector<T> & operator= ( Vector<T> const& V)
	{
		if ( _elem ) delete [] _elem; //释放原有内容
		copyFrom ( V._elem, 0, V.size() ); //整体复制
		return *this; //返回当前对象的引用，以便链式赋值
	}

	//删除秩为r的元素
	T remove ( Rank r )
	{
		T e = _elem[r]; //备份被删除元素
		remove ( r, r + 1 ); //调用区间删除算法，等效于对区间[r, r + 1)的删除
		return e; //返回被删除元素
	}

	//删除秩在区间[lo, hi)之内的元素
	int remove ( Rank lo, Rank hi )
	{
		if ( lo == hi ) return 0; //出于效率考虑，单独处理退化情况，比如remove(0, 0)
		while ( hi < _size ) _elem[lo++] = _elem[hi++]; //[hi, _size)顺次前移hi - lo个单元
		_size = lo; //更新规模，直接丢弃尾部[lo, _size = hi)区间
		shrink(); //若有必要，则缩容
		return hi - lo; //返回被删除元素的数目
	}

	//插入元素
	Rank insert ( Rank r, T const& e )
	{
		//assert: 0 <= r <= size
		expand(); //若有必要，扩容
		for ( int i = _size; i > r; i-- )
			_elem[i] = _elem[i-1]; //自后向前，后继元素顺次后移一个单元
		_elem[r] = e; _size++; //置入新元素并更新容量
		return r; //返回秩
	}

	//默认作为末元素插入
	Rank insert ( T const& e ) { return insert ( _size, e ); } 

	//对[lo, hi)排序
	void sort ( Rank lo, Rank hi )
	{
		mergeSort ( lo, hi );
	}

	//整体排序
	void sort() { sort ( 0, _size ); } 

	//对[lo, hi)置乱
	void unsort ( Rank lo, Rank hi )
	{
		T* V = _elem + lo; //将子向量_elem[lo, hi)视作另一向量V[0, hi - lo)
		for ( Rank i = hi - lo; i > 0; i-- ) //自后向前
			swap ( V[i - 1], V[rand() % i] ); //将V[i - 1]与V[0, i)中某一元素随机交换
	}

	//整体置乱
	void unsort() { unsort ( 0, _size ); } 

	//无序去重
	int deduplicate()
	{
		int oldSize = _size; //记录原规模
		Rank i = 1; //从_elem[1]开始
		while ( i < _size ) //自前向后逐一考查各元素_elem[i]
			( find ( _elem[i], 0, i ) < 0 ) ? //在其前缀中寻找与之雷同者（至多一个）
			i++ : remove ( i ); //若无雷同则继续考查其后继，否则删除雷同者
		return oldSize - _size; //向量规模变化量，即被删除元素总数
	}

	//有序去重
	int uniquify()
	{
		Rank i = 0, j = 0; //各对互异“相邻”元素的秩
		while ( ++j < _size ) //逐一扫描，直至末元素
			if ( _elem[i] != _elem[j] ) //跳过雷同者
				_elem[++i] = _elem[j]; //发现不同元素时，向前移至紧邻于前者右侧
		_size = ++i; shrink(); //直接截除尾部多余元素
		return j - i; //向量规模变化量，即被删除元素总数
	}

	// 遍历
	//遍历（使用函数指针，只读或局部性修改）
	void traverse ( void (* ) ( T& ) )
	{
		for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); 
	}

	//遍历（使用函数对象，可全局性修改）
	template <typename VST> void traverse ( VST& )
	{
		for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); 
	}
}; //Vector

#endif