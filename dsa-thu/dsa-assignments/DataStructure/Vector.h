#ifndef VECTOR_H
#define VECTOR_H

typedef int Rank; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

//����ģ����
template <typename T> class Vector { 
protected:
	Rank _size; int _capacity;  T* _elem; //��ģ��������������

	//������������A[lo, hi)
	void copyFrom ( T const* A, Rank lo, Rank hi )
	{
		_elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //����ռ䣬��ģ����
		while ( lo < hi ) //A[lo, hi)�ڵ�Ԫ����һ
			_elem[_size++] = A[lo++]; //������_elem[0, hi - lo)
	}

	//�ռ䲻��ʱ����
	void expand()
	{
		if ( _size < _capacity ) return; //��δ��Աʱ����������
		if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //��������С����
		T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //�����ӱ�
		for ( int i = 0; i < _size; i++ )
			_elem[i] = oldElem[i]; //����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='��
		/*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
		delete [] oldElem; //�ͷ�ԭ�ռ�
	}

	//װ�����ӹ�Сʱѹ��
	void shrink() 
	{
		if ( _size < _capacity ) return; //��δ��Աʱ����������
		if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //��������С����
		T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //�����ӱ�
		for ( int i = 0; i < _size; i++ )
			_elem[i] = oldElem[i]; //����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='��
		/*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
		delete [] oldElem; //�ͷ�ԭ�ռ�
	}

	//ѡȡ���Ԫ��
	Rank max ( Rank lo, Rank hi )
	{
		Rank mx = hi;
		while ( lo < hi-- ) //����ɨ��
			if ( _elem[hi] > _elem[mx] ) //���ϸ�Ƚ�
				mx = hi; //������max�ж��ʱ��֤�������ȣ�������֤selectionSort�ȶ�
		return mx;
	}

	//���������Ĺ鲢
	void merge ( Rank lo, Rank mi, Rank hi )
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
	void mergeSort ( Rank lo, Rank hi )
	{
		//0 <= lo < hi <= size
		if ( hi - lo < 2 ) return; //��Ԫ��������Ȼ���򣬷���...
		int mi = ( lo + hi ) >> 1; mergeSort ( lo, mi ); mergeSort ( mi, hi ); //���е�Ϊ��ֱ�����
		merge ( lo, mi, hi ); //�鲢
	}

	// ���ֲ����㷨���汾C��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
	Rank binSearch ( T const& e, Rank lo, Rank hi ) const
	{
		while ( lo < hi ) //ÿ������������һ�αȽ��жϣ���������֧
		{ 
			Rank mi = ( lo + hi ) >> 1; //���е�Ϊ���
			( e < _elem[mi] ) ? hi = mi : lo = mi + 1; //���ȽϺ�ȷ������[lo, mi)��(mi, hi)
		} //�ɹ����Ҳ�����ǰ��ֹ
		return --lo; //ѭ������ʱ��loΪ����e��Ԫ�ص���С�ȣ���lo - 1��������e��Ԫ�ص������
	} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���ܹ�����ʧ�ܵ�λ��

public:
	// ���캯��
	//����Ϊc����ģΪs������Ԫ�س�ʼΪv
	Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ) 
	{ _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } //s<=c

	//�������帴��
	Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } 

	//����
	Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } 

	//�������帴��
	Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); }

	//����
	Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } 

	// ��������
	~Vector() { delete [] _elem; } //�ͷ��ڲ��ռ�

	// ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ

	bool empty() const { return !_size; } //�п�
	
	//�ж������Ƿ�������
	int disordered() const
	{
		int n = 0; //������
		for ( int i = 1; i < _size; i++ ) //��һ���_size - 1������Ԫ��
			if ( _elem[i - 1] > _elem[i] ) n++; //���������
		return n; //���������ҽ���n = 0
	}

	//���������������
	Rank find ( T const& e ) const { return find ( e, 0, _size ); } 

	//���������������
	Rank find ( T const& e, Rank lo, Rank hi ) const
	{
		while ( ( lo < hi-- ) && ( e != _elem[hi] ) ); //�Ӻ���ǰ��˳�����
		return hi; //��hi < lo������ζ��ʧ�ܣ�����hi������Ԫ�ص���
	}

	//���������������
	Rank search ( T const& e ) const 
	{
		return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); 
	}

	//���������������
	Rank search ( T const& e, Rank lo, Rank hi ) const
	{
		return binSearch ( e, lo, hi );
	}

	// ��д���ʽӿ�
	T& operator[] ( Rank r ) const//�����±������������������������ʽ���ø�Ԫ��
	{
		return _elem[r];
	}

	//���ظ�ֵ���������Ա�ֱ�ӿ�¡����
	Vector<T> & operator= ( Vector<T> const& V)
	{
		if ( _elem ) delete [] _elem; //�ͷ�ԭ������
		copyFrom ( V._elem, 0, V.size() ); //���帴��
		return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
	}

	//ɾ����Ϊr��Ԫ��
	T remove ( Rank r )
	{
		T e = _elem[r]; //���ݱ�ɾ��Ԫ��
		remove ( r, r + 1 ); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
		return e; //���ر�ɾ��Ԫ��
	}

	//ɾ����������[lo, hi)֮�ڵ�Ԫ��
	int remove ( Rank lo, Rank hi )
	{
		if ( lo == hi ) return 0; //����Ч�ʿ��ǣ����������˻����������remove(0, 0)
		while ( hi < _size ) _elem[lo++] = _elem[hi++]; //[hi, _size)˳��ǰ��hi - lo����Ԫ
		_size = lo; //���¹�ģ��ֱ�Ӷ���β��[lo, _size = hi)����
		shrink(); //���б�Ҫ��������
		return hi - lo; //���ر�ɾ��Ԫ�ص���Ŀ
	}

	//����Ԫ��
	Rank insert ( Rank r, T const& e )
	{
		//assert: 0 <= r <= size
		expand(); //���б�Ҫ������
		for ( int i = _size; i > r; i-- )
			_elem[i] = _elem[i-1]; //�Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ
		_elem[r] = e; _size++; //������Ԫ�ز���������
		return r; //������
	}

	//Ĭ����ΪĩԪ�ز���
	Rank insert ( T const& e ) { return insert ( _size, e ); } 

	//��[lo, hi)����
	void sort ( Rank lo, Rank hi )
	{
		mergeSort ( lo, hi );
	}

	//��������
	void sort() { sort ( 0, _size ); } 

	//��[lo, hi)����
	void unsort ( Rank lo, Rank hi )
	{
		T* V = _elem + lo; //��������_elem[lo, hi)������һ����V[0, hi - lo)
		for ( Rank i = hi - lo; i > 0; i-- ) //�Ժ���ǰ
			swap ( V[i - 1], V[rand() % i] ); //��V[i - 1]��V[0, i)��ĳһԪ���������
	}

	//��������
	void unsort() { unsort ( 0, _size ); } 

	//����ȥ��
	int deduplicate()
	{
		int oldSize = _size; //��¼ԭ��ģ
		Rank i = 1; //��_elem[1]��ʼ
		while ( i < _size ) //��ǰ�����һ�����Ԫ��_elem[i]
			( find ( _elem[i], 0, i ) < 0 ) ? //����ǰ׺��Ѱ����֮��ͬ�ߣ�����һ����
			i++ : remove ( i ); //������ͬ������������̣�����ɾ����ͬ��
		return oldSize - _size; //������ģ�仯��������ɾ��Ԫ������
	}

	//����ȥ��
	int uniquify()
	{
		Rank i = 0, j = 0; //���Ի��조���ڡ�Ԫ�ص���
		while ( ++j < _size ) //��һɨ�裬ֱ��ĩԪ��
			if ( _elem[i] != _elem[j] ) //������ͬ��
				_elem[++i] = _elem[j]; //���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
		_size = ++i; shrink(); //ֱ�ӽس�β������Ԫ��
		return j - i; //������ģ�仯��������ɾ��Ԫ������
	}

	// ����
	//������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
	void traverse ( void (* ) ( T& ) )
	{
		for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); 
	}

	//������ʹ�ú������󣬿�ȫ�����޸ģ�
	template <typename VST> void traverse ( VST& )
	{
		for ( int i = 0; i < _size; i++ ) visit ( _elem[i] ); 
	}
}; //Vector

#endif