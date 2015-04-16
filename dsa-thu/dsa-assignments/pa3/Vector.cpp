#include "Vector.h"
#include "Fib.h"

//�����±������
template <typename T> T& Vector<T>::operator[] ( Rank r ) const
{
	return _elem[r];
} // assert: 0 <= r < _size

//����
template <typename T> Vector<T>& Vector<T>::operator= ( Vector<T> const& V ) 
{
	if ( _elem ) delete [] _elem; //�ͷ�ԭ������
	copyFrom ( V._elem, 0, V.size() ); //���帴��
	return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
}

//����������A[lo, hi)Ϊ������������
template <typename T> //Ԫ������
void Vector<T>::copyFrom ( T const* A, Rank lo, Rank hi ) 
{ 
	_elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //����ռ䣬��ģ����
	while ( lo < hi ) //A[lo, hi)�ڵ�Ԫ����һ
		_elem[_size++] = A[lo++]; //������_elem[0, hi - lo)
}

//�����ռ䲻��ʱ����
template <typename T> void Vector<T>::expand() 
{
	if ( _size < _capacity ) return; //��δ��Աʱ����������
	if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //��������С����
	T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //�����ӱ�
	for ( int i = 0; i < _size; i++ )
		_elem[i] = oldElem[i]; //����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='��
	/*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
	delete [] oldElem; //�ͷ�ԭ�ռ�
}

//װ�����ӹ�Сʱѹ��������ռ�ռ�
template <typename T> void Vector<T>::shrink() 
{
	if ( _capacity < DEFAULT_CAPACITY << 1 ) return; //����������DEFAULT_CAPACITY����
	if ( _size << 2 > _capacity ) return; //��25%Ϊ��
	T* oldElem = _elem;  _elem = new T[_capacity >>= 1]; //��������
	for ( int i = 0; i < _size; i++ ) _elem[i] = oldElem[i]; //����ԭ��������
	delete [] oldElem; //�ͷ�ԭ�ռ�
}

//��e��Ϊ��ΪrԪ�ز���
template <typename T> 
Rank Vector<T>::insert ( Rank r, T const& e ) 
{ //assert: 0 <= r <= size
	expand(); //���б�Ҫ������
	for ( int i = _size; i > r; i-- ) _elem[i] = _elem[i-1]; //�Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ
	_elem[r] = e; _size++; //������Ԫ�ز���������
	return r; //������
}

//ɾ����������Ϊr��Ԫ�أ�0 <= r < size
template <typename T> T Vector<T>::remove ( Rank r ) 
{ 
	T e = _elem[r]; //���ݱ�ɾ��Ԫ��
	remove ( r, r + 1 ); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
	return e; //���ر�ɾ��Ԫ��
}

//ɾ������[lo, hi)
template <typename T> int Vector<T>::remove ( Rank lo, Rank hi ) 
{
	if ( lo == hi ) return 0; //����Ч�ʿ��ǣ����������˻����������remove(0, 0)
	while ( hi < _size ) _elem[lo++] = _elem[hi++]; //[hi, _size)˳��ǰ��hi - lo����Ԫ
	_size = lo; //���¹�ģ��ֱ�Ӷ���β��[lo, _size = hi)����
	shrink(); //���б�Ҫ��������
	return hi - lo; //���ر�ɾ��Ԫ�ص���Ŀ
}

//������������������Ԫ�ضԵ�����
template <typename T> int Vector<T>::disordered() const 
{
	int n = 0; //������
	for ( int i = 1; i < _size; i++ ) //��һ���_size - 1������Ԫ��
		if ( _elem[i - 1] > _elem[i] ) n++; //���������
	return n; //���������ҽ���n = 0
}

//����������˳����ң��������һ��Ԫ��e��λ�ã�ʧ��ʱ������lo - 1
template <typename T> 
Rank Vector<T>::find ( T const& e, Rank lo, Rank hi ) const 
{ 
	//assert: 0 <= lo < hi <= _size
	while ( ( lo < hi-- ) && ( e != _elem[hi] ) ); //�Ӻ���ǰ��˳�����
	return hi; //��hi < lo������ζ��ʧ�ܣ�����hi������Ԫ�ص���
}

//����������������[lo, hi)�ڣ�ȷ��������e�����һ���ڵ����
template <typename T> 
Rank Vector<T>::search ( T const& e, Rank lo, Rank hi ) const 
{
	//assert: 0 <= lo < hi <= _size
	return ( rand() % 2 ) ? //����50%�ĸ������ʹ�ö��ֲ��һ�Fibonacci����
		binSearch ( _elem, e, lo, hi ) : fibSearch ( _elem, e, lo, hi );
}

// ���ֲ����㷨���汾C��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
template <typename T> static Rank binSearch ( T* A, T const& e, Rank lo, Rank hi ) 
{
	while ( lo < hi ) { //ÿ������������һ�αȽ��жϣ���������֧
		Rank mi = ( lo + hi ) >> 1; //���е�Ϊ���
		( e < A[mi] ) ? hi = mi : lo = mi + 1; //���ȽϺ�ȷ������[lo, mi)��(mi, hi)
	} //�ɹ����Ҳ�����ǰ��ֹ
	return --lo; //ѭ������ʱ��loΪ����e��Ԫ�ص���С�ȣ���lo - 1��������e��Ԫ�ص������
} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���ܹ�����ʧ�ܵ�λ��

// Fibonacci�����㷨���汾B��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
template <typename T> static Rank fibSearch ( T* A, T const& e, Rank lo, Rank hi ) {
	Fib fib ( hi - lo ); //��O(log_phi(n = hi - lo)ʱ�䴴��Fib����
	while ( lo < hi ) { //ÿ������������һ�αȽ��жϣ���������֧
		while ( hi - lo < fib.get() ) fib.prev(); //ͨ����ǰ˳����ң���̯O(1)����������������Σ�
		Rank mi = lo + fib.get() - 1; //ȷ������Fib(k) - 1�����
		( e < A[mi] ) ? hi = mi : lo = mi + 1; //�ȽϺ�ȷ������ǰ���[lo, mi)�����(mi, hi)
	} //�ɹ����Ҳ�����ǰ��ֹ
	return --lo; //ѭ������ʱ��loΪ����e��Ԫ�ص���С�ȣ���lo - 1��������e��Ԫ�ص������
} //�ж������Ԫ��ʱ�����ܱ�֤������������ߣ�����ʧ��ʱ���ܹ�����ʧ�ܵ�λ��

//��������ָ����Ʊ�������
template <typename T> void Vector<T>::traverse ( void ( *visit ) ( T& ) ) 
{ 
	for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); 
}

//Ԫ�����͡���������������
template <typename T> template <typename VST> 
void Vector<T>::traverse ( VST& visit ) //���������������
{ 
	for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); 
}

//�ȸ��������������[lo, hi)
template <typename T> void Vector<T>::unsort ( Rank lo, Rank hi ) 
{
	T* V = _elem + lo; //��������_elem[lo, hi)������һ����V[0, hi - lo)
	for ( Rank i = hi - lo; i > 0; i-- ) //�Ժ���ǰ
		swap ( V[i - 1], V[rand() % i] ); //��V[i - 1]��V[0, i)��ĳһԪ���������
}

//��������[lo, hi)����
template <typename T> void Vector<T>::sort ( Rank lo, Rank hi ) 
{
	switch ( rand() % 5 ) { //���ѡȡ�����㷨���ɸ��ݾ���������ص����ѡȡ������
	case 1:  bubbleSort ( lo, hi ); break; //��������
	case 2:  selectionSort ( lo, hi ); break; //ѡ������ϰ�⣩
	case 3:  mergeSort ( lo, hi ); break; //�鲢����
	case 4:  heapSort ( lo, hi ); break; //�������Ժ���ܣ�
	default: quickSort ( lo, hi ); break; //���������Ժ���ܣ�
	}
}

//һ��ɨ�轻��
template <typename T> bool Vector<T>::bubble ( Rank lo, Rank hi )
{
	bool sorted = true; //���������־
	while ( ++lo < hi ) //�������ң���һ����������Ԫ��
		if ( _elem[lo - 1] > _elem[lo] ) { //��������
			sorted = false; //��ζ����δ�������򣬲���Ҫ
			swap ( _elem[lo - 1], _elem[lo] ); //ͨ������ʹ�ֲ�����
		}
		return sorted; //���������־
}

//��������������
template <typename T>
void Vector<T>::bubbleSort ( Rank lo, Rank hi ) //assert: 0 <= lo < hi <= size
{ 
	while ( !bubble ( lo, hi-- ) ); 
} //������ɨ�轻����ֱ��ȫ��

//����ѡ������
template <typename T> 
void Vector<T>::selectionSort ( Rank lo, Rank hi ) 
{ 
	//assert: 0 < lo <= hi <= size
	while ( lo < --hi )
		swap ( _elem[max ( lo, hi ) ], _elem[hi] ); //��[hi]��[lo, hi]�е�����߽���
}

//��[lo, hi]���ҳ������
template <typename T>
Rank Vector<T>::max ( Rank lo, Rank hi ) 
{ 
	Rank mx = hi;
	while ( lo < hi-- ) //����ɨ��
		if ( _elem[hi] > _elem[mx] ) //���ϸ�Ƚ�
			mx = hi; //������max�ж��ʱ��֤�������ȣ�������֤selectionSort�ȶ�
	return mx;
}

//���������Ĺ鲢
template <typename T>
void Vector<T>::merge ( Rank lo, Rank mi, Rank hi ) 
{ 
	//���������������[lo, mi)��[mi, hi)
	T* A = _elem + lo; //�ϲ��������A[0, hi - lo) = _elem[lo, hi)
	int lb = mi - lo; T* B = new T[lb]; //ǰ������B[0, lb) = _elem[lo, mi)
	for ( Rank i = 0; i < lb; B[i] = A[i++] ); //����ǰ������
	int lc = hi - mi; T* C = _elem + mi; //��������C[0, lc) = _elem[mi, hi)
	for ( Rank i = 0, j = 0, k = 0; ( j < lb ) || ( k < lc ); ) { //B[j]��C[k]�е�С������Aĩβ
		if ( ( j < lb ) && ( ! ( k < lc ) || ( B[j] <= C[k] ) ) ) A[i++] = B[j++];
		if ( ( k < lc ) && ( ! ( j < lb ) || ( C[k] <  B[j] ) ) ) A[i++] = C[k++];
	}
	delete [] B; //�ͷ���ʱ�ռ�B
} //�鲢��õ���������������[lo, hi)

//�����鲢����
template <typename T>
void Vector<T>::mergeSort ( Rank lo, Rank hi ) 
{
	//0 <= lo < hi <= size
	if ( hi - lo < 2 ) return; //��Ԫ��������Ȼ���򣬷���...
	int mi = ( lo + hi ) >> 1; mergeSort ( lo, mi ); mergeSort ( mi, hi ); //���е�Ϊ��ֱ�����
	merge ( lo, mi, hi ); //�鲢
}

//��㹹���㷨��ͨ������Ԫ��λ�ù�������[lo, hi]����㣬����������
template <typename T> 
Rank Vector<T>::partition ( Rank lo, Rank hi ) 
{ 
	//�汾B�����Ż��������ؼ�����ͬ���˻����
	swap ( _elem[lo], _elem[lo + rand() % ( hi - lo + 1 ) ] ); //��ѡһ��Ԫ������Ԫ�ؽ���
	T pivot = _elem[lo]; //����Ԫ��Ϊ��ѡ��㡪�������Ͻ�������Ч�����ѡȡ
	while ( lo < hi ) { //�����������˽�������м�ɨ��
		while ( lo < hi )
			if ( pivot < _elem[hi] ) //�ڴ���pivot��ǰ����
				hi--; //������չ�Ҷ�������
			else //ֱ������������pivot��
			{ _elem[lo++] = _elem[hi]; break; } //����������������
			while ( lo < hi )
				if ( _elem[lo] < pivot ) //��С��pivot��ǰ����
					lo++; //������չ���������
				else //ֱ��������С��pivot��
				{ _elem[hi--] = _elem[lo]; break; } //��������Ҷ�������
	} //assert: lo == hi
	_elem[lo] = pivot; //�����ݵ�����¼����ǰ����������֮��
	return lo; //����������
}

//������������
template <typename T> 
void Vector<T>::quickSort ( Rank lo, Rank hi ) { //0 <= lo < hi <= size
	/*DSA*/printf ( "\tQUICKsort [%3d, %3d)\n", lo, hi );
	if ( hi - lo < 2 ) return; //��Ԫ��������Ȼ���򣬷���...
	Rank mi = partition ( lo, hi - 1 ); //��[lo, hi - 1]�ڹ������
	quickSort ( lo, mi ); //��ǰ׺�ݹ�����
	quickSort ( mi + 1, hi ); //�Ժ�׺�ݹ�����
}

//template <typename T> void Vector<T>::heapSort ( Rank lo, Rank hi ) 
//{ 
//	//0 <= lo < hi <= size
//	PQ_ComplHeap<T> H ( _elem + lo, hi - lo ); //�����������佨��һ����ȫ����ѣ�O(n)
//	while ( !H.empty() ) //������ժ�����Ԫ������������ĺ�׺��ֱ���ѿ�
//		_elem[--hi] = H.delMax(); //��Ч�ڶѶ���ĩԪ�ضԻ�������
//}

//���������ظ�Ԫ���޳��㷨����Ч�棩
template <typename T> int Vector<T>::uniquify() 
{	
	Rank i = 0, j = 0; //���Ի��조���ڡ�Ԫ�ص���
	while ( ++j < _size ) //��һɨ�裬ֱ��ĩԪ��
		if ( _elem[i] != _elem[j] ) //������ͬ��
			_elem[++i] = _elem[j]; //���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
	_size = ++i; shrink(); //ֱ�ӽس�β������Ԫ��
	return j - i; //������ģ�仯��������ɾ��Ԫ������
}

//ɾ�������������ظ�Ԫ�أ���Ч�棩
template <typename T> int Vector<T>::deduplicate() 
{ 
	int oldSize = _size; //��¼ԭ��ģ
	Rank i = 1; //��_elem[1]��ʼ
	while ( i < _size ) //��ǰ�����һ�����Ԫ��_elem[i]
		( find ( _elem[i], 0, i ) < 0 ) ? //����ǰ׺��Ѱ����֮��ͬ�ߣ�����һ����
		i++ : remove ( i ); //������ͬ������������̣�����ɾ����ͬ��
	return oldSize - _size; //������ģ�仯��������ɾ��Ԫ������
}