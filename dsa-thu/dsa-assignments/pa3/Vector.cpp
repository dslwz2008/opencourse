#include "Vector.h"
#include "Fib.h"

//重载下标操作符
template <typename T> T& Vector<T>::operator[] ( Rank r ) const
{
	return _elem[r];
} // assert: 0 <= r < _size

//重载
template <typename T> Vector<T>& Vector<T>::operator= ( Vector<T> const& V ) 
{
	if ( _elem ) delete [] _elem; //释放原有内容
	copyFrom ( V._elem, 0, V.size() ); //整体复制
	return *this; //返回当前对象的引用，以便链式赋值
}

//以数组区间A[lo, hi)为蓝本复制向量
template <typename T> //元素类型
void Vector<T>::copyFrom ( T const* A, Rank lo, Rank hi ) 
{ 
	_elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //分配空间，规模清零
	while ( lo < hi ) //A[lo, hi)内的元素逐一
		_elem[_size++] = A[lo++]; //复制至_elem[0, hi - lo)
}

//向量空间不足时扩容
template <typename T> void Vector<T>::expand() 
{
	if ( _size < _capacity ) return; //尚未满员时，不必扩容
	if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //不低于最小容量
	T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //容量加倍
	for ( int i = 0; i < _size; i++ )
		_elem[i] = oldElem[i]; //复制原向量内容（T为基本类型，或已重载赋值操作符'='）
	/*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
	delete [] oldElem; //释放原空间
}

//装填因子过小时压缩向量所占空间
template <typename T> void Vector<T>::shrink() 
{
	if ( _capacity < DEFAULT_CAPACITY << 1 ) return; //不致收缩到DEFAULT_CAPACITY以下
	if ( _size << 2 > _capacity ) return; //以25%为界
	T* oldElem = _elem;  _elem = new T[_capacity >>= 1]; //容量减半
	for ( int i = 0; i < _size; i++ ) _elem[i] = oldElem[i]; //复制原向量内容
	delete [] oldElem; //释放原空间
}

//将e作为秩为r元素插入
template <typename T> 
Rank Vector<T>::insert ( Rank r, T const& e ) 
{ //assert: 0 <= r <= size
	expand(); //若有必要，扩容
	for ( int i = _size; i > r; i-- ) _elem[i] = _elem[i-1]; //自后向前，后继元素顺次后移一个单元
	_elem[r] = e; _size++; //置入新元素并更新容量
	return r; //返回秩
}

//删除向量中秩为r的元素，0 <= r < size
template <typename T> T Vector<T>::remove ( Rank r ) 
{ 
	T e = _elem[r]; //备份被删除元素
	remove ( r, r + 1 ); //调用区间删除算法，等效于对区间[r, r + 1)的删除
	return e; //返回被删除元素
}

//删除区间[lo, hi)
template <typename T> int Vector<T>::remove ( Rank lo, Rank hi ) 
{
	if ( lo == hi ) return 0; //出于效率考虑，单独处理退化情况，比如remove(0, 0)
	while ( hi < _size ) _elem[lo++] = _elem[hi++]; //[hi, _size)顺次前移hi - lo个单元
	_size = lo; //更新规模，直接丢弃尾部[lo, _size = hi)区间
	shrink(); //若有必要，则缩容
	return hi - lo; //返回被删除元素的数目
}

//返回向量中逆序相邻元素对的总数
template <typename T> int Vector<T>::disordered() const 
{
	int n = 0; //计数器
	for ( int i = 1; i < _size; i++ ) //逐一检查_size - 1对相邻元素
		if ( _elem[i - 1] > _elem[i] ) n++; //逆序则计数
	return n; //向量有序当且仅当n = 0
}

//无序向量的顺序查找：返回最后一个元素e的位置；失败时，返回lo - 1
template <typename T> 
Rank Vector<T>::find ( T const& e, Rank lo, Rank hi ) const 
{ 
	//assert: 0 <= lo < hi <= _size
	while ( ( lo < hi-- ) && ( e != _elem[hi] ) ); //从后向前，顺序查找
	return hi; //若hi < lo，则意味着失败；否则hi即命中元素的秩
}

//在有序向量的区间[lo, hi)内，确定不大于e的最后一个节点的秩
template <typename T> 
Rank Vector<T>::search ( T const& e, Rank lo, Rank hi ) const 
{
	//assert: 0 <= lo < hi <= _size
	return ( rand() % 2 ) ? //按各50%的概率随机使用二分查找或Fibonacci查找
		binSearch ( _elem, e, lo, hi ) : fibSearch ( _elem, e, lo, hi );
}

// 二分查找算法（版本C）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
template <typename T> static Rank binSearch ( T* A, T const& e, Rank lo, Rank hi ) 
{
	while ( lo < hi ) { //每步迭代仅需做一次比较判断，有两个分支
		Rank mi = ( lo + hi ) >> 1; //以中点为轴点
		( e < A[mi] ) ? hi = mi : lo = mi + 1; //经比较后确定深入[lo, mi)或(mi, hi)
	} //成功查找不能提前终止
	return --lo; //循环结束时，lo为大于e的元素的最小秩，故lo - 1即不大于e的元素的最大秩
} //有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置

// Fibonacci查找算法（版本B）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
template <typename T> static Rank fibSearch ( T* A, T const& e, Rank lo, Rank hi ) {
	Fib fib ( hi - lo ); //用O(log_phi(n = hi - lo)时间创建Fib数列
	while ( lo < hi ) { //每步迭代仅仅做一次比较判断，有两个分支
		while ( hi - lo < fib.get() ) fib.prev(); //通过向前顺序查找（分摊O(1)）——至多迭代几次？
		Rank mi = lo + fib.get() - 1; //确定形如Fib(k) - 1的轴点
		( e < A[mi] ) ? hi = mi : lo = mi + 1; //比较后确定深入前半段[lo, mi)或后半段(mi, hi)
	} //成功查找不能提前终止
	return --lo; //循环结束时，lo为大于e的元素的最小秩，故lo - 1即不大于e的元素的最大秩
} //有多个命中元素时，总能保证返回最秩最大者；查找失败时，能够返回失败的位置

//借助函数指针机制遍历向量
template <typename T> void Vector<T>::traverse ( void ( *visit ) ( T& ) ) 
{ 
	for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); 
}

//元素类型、操作器遍历向量
template <typename T> template <typename VST> 
void Vector<T>::traverse ( VST& visit ) //借助函数对象机制
{ 
	for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); 
}

//等概率随机置乱区间[lo, hi)
template <typename T> void Vector<T>::unsort ( Rank lo, Rank hi ) 
{
	T* V = _elem + lo; //将子向量_elem[lo, hi)视作另一向量V[0, hi - lo)
	for ( Rank i = hi - lo; i > 0; i-- ) //自后向前
		swap ( V[i - 1], V[rand() % i] ); //将V[i - 1]与V[0, i)中某一元素随机交换
}

//向量区间[lo, hi)排序
template <typename T> void Vector<T>::sort ( Rank lo, Rank hi ) 
{
	switch ( rand() % 5 ) { //随机选取排序算法。可根据具体问题的特点灵活选取或扩充
	case 1:  bubbleSort ( lo, hi ); break; //起泡排序
	case 2:  selectionSort ( lo, hi ); break; //选择排序（习题）
	case 3:  mergeSort ( lo, hi ); break; //归并排序
	case 4:  heapSort ( lo, hi ); break; //堆排序（稍后介绍）
	default: quickSort ( lo, hi ); break; //快速排序（稍后介绍）
	}
}

//一趟扫描交换
template <typename T> bool Vector<T>::bubble ( Rank lo, Rank hi )
{
	bool sorted = true; //整体有序标志
	while ( ++lo < hi ) //自左向右，逐一检查各对相邻元素
		if ( _elem[lo - 1] > _elem[lo] ) { //若逆序，则
			sorted = false; //意味着尚未整体有序，并需要
			swap ( _elem[lo - 1], _elem[lo] ); //通过交换使局部有序
		}
		return sorted; //返回有序标志
}

//向量的起泡排序
template <typename T>
void Vector<T>::bubbleSort ( Rank lo, Rank hi ) //assert: 0 <= lo < hi <= size
{ 
	while ( !bubble ( lo, hi-- ) ); 
} //逐趟做扫描交换，直至全序

//向量选择排序
template <typename T> 
void Vector<T>::selectionSort ( Rank lo, Rank hi ) 
{ 
	//assert: 0 < lo <= hi <= size
	while ( lo < --hi )
		swap ( _elem[max ( lo, hi ) ], _elem[hi] ); //将[hi]与[lo, hi]中的最大者交换
}

//在[lo, hi]内找出最大者
template <typename T>
Rank Vector<T>::max ( Rank lo, Rank hi ) 
{ 
	Rank mx = hi;
	while ( lo < hi-- ) //逆向扫描
		if ( _elem[hi] > _elem[mx] ) //且严格比较
			mx = hi; //故能在max有多个时保证后者优先，进而保证selectionSort稳定
	return mx;
}

//有序向量的归并
template <typename T>
void Vector<T>::merge ( Rank lo, Rank mi, Rank hi ) 
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
template <typename T>
void Vector<T>::mergeSort ( Rank lo, Rank hi ) 
{
	//0 <= lo < hi <= size
	if ( hi - lo < 2 ) return; //单元素区间自然有序，否则...
	int mi = ( lo + hi ) >> 1; mergeSort ( lo, mi ); mergeSort ( mi, hi ); //以中点为界分别排序
	merge ( lo, mi, hi ); //归并
}

//轴点构造算法：通过调整元素位置构造区间[lo, hi]的轴点，并返回其秩
template <typename T> 
Rank Vector<T>::partition ( Rank lo, Rank hi ) 
{ 
	//版本B：可优化处理多个关键码雷同的退化情况
	swap ( _elem[lo], _elem[lo + rand() % ( hi - lo + 1 ) ] ); //任选一个元素与首元素交换
	T pivot = _elem[lo]; //以首元素为候选轴点——经以上交换，等效于随机选取
	while ( lo < hi ) { //从向量的两端交替地向中间扫描
		while ( lo < hi )
			if ( pivot < _elem[hi] ) //在大于pivot的前提下
				hi--; //向左拓展右端子向量
			else //直至遇到不大于pivot者
			{ _elem[lo++] = _elem[hi]; break; } //将其归入左端子向量
			while ( lo < hi )
				if ( _elem[lo] < pivot ) //在小于pivot的前提下
					lo++; //向右拓展左端子向量
				else //直至遇到不小于pivot者
				{ _elem[hi--] = _elem[lo]; break; } //将其归入右端子向量
	} //assert: lo == hi
	_elem[lo] = pivot; //将备份的轴点记录置于前、后子向量之间
	return lo; //返回轴点的秩
}

//向量快速排序
template <typename T> 
void Vector<T>::quickSort ( Rank lo, Rank hi ) { //0 <= lo < hi <= size
	/*DSA*/printf ( "\tQUICKsort [%3d, %3d)\n", lo, hi );
	if ( hi - lo < 2 ) return; //单元素区间自然有序，否则...
	Rank mi = partition ( lo, hi - 1 ); //在[lo, hi - 1]内构造轴点
	quickSort ( lo, mi ); //对前缀递归排序
	quickSort ( mi + 1, hi ); //对后缀递归排序
}

//template <typename T> void Vector<T>::heapSort ( Rank lo, Rank hi ) 
//{ 
//	//0 <= lo < hi <= size
//	PQ_ComplHeap<T> H ( _elem + lo, hi - lo ); //将待排序区间建成一个完全二叉堆，O(n)
//	while ( !H.empty() ) //反复地摘除最大元并归入已排序的后缀，直至堆空
//		_elem[--hi] = H.delMax(); //等效于堆顶与末元素对换后下滤
//}

//有序向量重复元素剔除算法（高效版）
template <typename T> int Vector<T>::uniquify() 
{	
	Rank i = 0, j = 0; //各对互异“相邻”元素的秩
	while ( ++j < _size ) //逐一扫描，直至末元素
		if ( _elem[i] != _elem[j] ) //跳过雷同者
			_elem[++i] = _elem[j]; //发现不同元素时，向前移至紧邻于前者右侧
	_size = ++i; shrink(); //直接截除尾部多余元素
	return j - i; //向量规模变化量，即被删除元素总数
}

//删除无序向量中重复元素（高效版）
template <typename T> int Vector<T>::deduplicate() 
{ 
	int oldSize = _size; //记录原规模
	Rank i = 1; //从_elem[1]开始
	while ( i < _size ) //自前向后逐一考查各元素_elem[i]
		( find ( _elem[i], 0, i ) < 0 ) ? //在其前缀中寻找与之雷同者（至多一个）
		i++ : remove ( i ); //若无雷同则继续考查其后继，否则删除雷同者
	return oldSize - _size; //向量规模变化量，即被删除元素总数
}