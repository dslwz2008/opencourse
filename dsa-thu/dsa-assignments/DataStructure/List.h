#ifndef LIST_H
#define LIST_H

#include "listNode.h" //�����б�ڵ���

//�б�ģ����
template <typename T> class List 
{ 

private:
	//��ģ��ͷ�ڱ���β�ڱ�
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;

protected:
	void init()
	{
		header = new ListNode<T>; //����ͷ�ڱ��ڵ�
		trailer = new ListNode<T>; //����β�ڱ��ڵ�
		header->succ = trailer; header->pred = NULL;
		trailer->pred = header; trailer->succ = NULL;
		_size = 0; //��¼��ģ
	}

	int clear()
	{
		int oldSize = _size;
		while ( 0 < _size ) remove ( header->succ ); //����ɾ���׽ڵ㣬ֱ���б���
		return oldSize;
	}

	//�����б�����λ��p���n��
	void copyNodes ( ListNodePosi(T), int )
	{
		//p�Ϸ�����������n-1�����̽ڵ�
		init(); //����ͷ��β�ڱ��ڵ㲢����ʼ��
		while ( n-- ) { insertAsLast ( p->data ); p = p->succ; } //������p��n��������Ϊĩ�ڵ����
	}

	//�����б�Ĺ鲢����ǰ�б�����p���n��Ԫ�أ����б�L����q���m��Ԫ�ع鲢
	void merge ( ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int )
	{
		// assert:  this.valid(p) && rank(p) + n <= size && this.sorted(p, n)
		//          L.valid(q) && rank(q) + m <= L._size && L.sorted(q, m)
		// ע�⣺�ڹ鲢����֮��ĳ��ϣ��п��� this == L && rank(p) + n = rank(q)
		ListNodePosi(T) pp = p->pred; //����ǰ����������header�����Ա㷵��ǰ ...
		while ( 0 < m ) //��q��δ�Ƴ�����֮ǰ
			if ( ( 0 < n ) && ( p->data <= q->data ) ) //��p������������v(p) <= v(q)����
			{ if ( q == ( p = p->succ ) ) break; n--; } //p����ϲ����б����滻Ϊ��ֱ�Ӻ��
			else //��p�ѳ����ҽ��v(q) < v(p)����
			{ insertB ( p, L.remove ( ( q = q->succ )->pred ) ); m--; } //��qת����p֮ǰ
			p = pp->succ; //ȷ���鲢������ģ��£����
	}

	//�Դ�p��ʼ������n���ڵ�鲢����
	void mergeSort ( ListNodePosi(T)&, int )
	{ 
		//valid(p) && rank(p) + n <= size
		/*DSA*/printf ( "\tMERGEsort [%3d]\n", n );
		if ( n < 2 ) return; //��������Χ���㹻С����ֱ�ӷ��أ�����...
		int m = n >> 1; //���е�Ϊ��
		ListNodePosi(T) q = p; for ( int i = 0; i < m; i++ ) q = q->succ; //�����б�
		mergeSort ( p, m ); mergeSort ( q, n - m ); //��ǰ�������б�ֱ�����
		merge ( p, m, *this, q, n - m ); //�鲢
	} //ע�⣺�����p��Ȼָ��鲢������ģ��£����

public:
	// ���캯��
	List() { init(); } //Ĭ��

	//�����б�����λ��p���n�assert: pΪ�Ϸ�λ�ã���������n-1����̽ڵ㣩
	List ( ListNodePosi(T) p, int n ) 
	{ 
		copyNodes ( p, n ); 
	}

	//���帴���б�L
	List ( List<T> const& L ) 
	{ 
		copyNodes ( L.first(), L._size ); 
	}

	//����L���Ե�r�����n�assert: r+n <= L._size��
	List ( List<T> const& L, int r, int n ) 
	{ 
		copyNodes ( L[r], n ); 
	}

	//�б�������
	~List()
	{
		//����б��ͷ�ͷ��β�ڱ��ڵ�
		clear(); delete header; delete trailer; 
	}

	// ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ

	bool empty() const { return _size <= 0; } //�п�

	//���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
	T& operator[] ( Rank r ) const
	{ 
		//assert: 0 <= r < size
		ListNodePosi(T) p = first(); //���׽ڵ����
		while ( 0 < r-- ) p = p->succ; //˳����r���ڵ㼴��
		return p->data; //Ŀ��ڵ㣬������������Ԫ��
	}

	ListNodePosi(T) first() const { return header->succ; } //�׽ڵ�λ��

	ListNodePosi(T) last() const { return trailer->pred; } //ĩ�ڵ�λ��

	bool valid ( ListNodePosi(T) p ) //�ж�λ��p�Ƿ����Ϸ�
	{ return p && ( trailer != p ) && ( header != p ); } //��ͷ��β�ڵ��ͬ��NULL

	//�ж��б��Ƿ�������
	int disordered() const
	{ 
		int n = 0; ListNode<T>* p = first();
		for ( int i = 0; i < _size - 1; p = p->succ, i++ )
			if ( p->data > p->succ->data ) n++;
		return n;
	}

	//�����б����
	ListNodePosi(T) find ( T const& e ) const 
	{ return find ( e, _size, trailer ); }

	//�����������
	ListNodePosi(T) find ( T const& e, int n, ListNodePosi(T) p ) const
	{
		while ( 0 < n-- ) //��0 <= n <= rank(p) < _size������p�������n��ǰ������������
			if ( e == ( p = p->pred )->data ) return p; //����ȶԣ�ֱ�����л�ΧԽ��
		return NULL; //pԽ����߽���ζ�������ڲ���e������ʧ��
	}

	//�����б����
	ListNodePosi(T) search ( T const& e ) const 
	{ return search ( e, _size, trailer ); }

	//�����������
	ListNodePosi(T) search ( T const& e, int n, ListNodePosi(T) p ) const
	{
		// assert: 0 <= n <= rank(p) < _size
		while ( 0 <= n-- ) //����p�������n��ǰ����������������Ƚ�
		{ 
			if ( ( ( p = p->pred )->data ) <= e )
				break; //ֱ�����С���ֵԽ���ΧԽ��
		}
		// assert: ����λ��p�ط����������Լ���������ܴ�ǰ���һ�ιؼ���ȽϿ���û�����壨��Ч����-inf�Ƚϣ�
		return p; //���ز�����ֹ��λ��
	} //ʧ��ʱ������������߽��ǰ����������header�����������߿�ͨ��valid()�жϳɹ����

	//��p����n-1�������ѡ�������
	ListNodePosi(T) selectMax ( ListNodePosi(T) p, int n )
	{
		ListNodePosi(T) max = p; //������ݶ�Ϊ�׽ڵ�p
		for ( ListNodePosi(T) cur = p; 1 < n; n-- ) //���׽ڵ�p�������������ڵ���һ��max�Ƚ�
			if ( !lt ( ( cur = cur->succ )->data, max->data ) ) //����ǰԪ�ز�С��max����
				max = cur; //�������Ԫ��λ�ü�¼
		return max; //�������ڵ�λ��
	}

	ListNodePosi(T) selectMax() { return selectMax ( header->succ, _size ); } //���������

	// ��д���ʽӿ�
	//��e�����׽ڵ����
	ListNodePosi(T) insertAsFirst ( T const& e )
	{
		_size++; return header->insertAsSucc ( e );
	}

	//��e����ĩ�ڵ����
	ListNodePosi(T) insertAsLast ( T const& e )
	{
		_size++; return trailer->insertAsPred ( e );  
	}

	//��e����p�ĺ�̲���
	ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e )
	{
		_size++; return p->insertAsSucc ( e );
	}
	
	//��e����p��ǰ������
	ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e )
	{
		_size++; return p->insertAsPred ( e );
	}

	//ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
	T remove ( ListNodePosi(T) p )
	{
		T e = p->data; //���ݴ�ɾ���ڵ����ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ��
		p->pred->succ = p->succ; p->succ->pred = p->pred; //��̡�ǰ��
		delete p; _size--; //�ͷŽڵ㣬���¹�ģ
		return e; //���ر��ݵ���ֵ
	}

	void merge ( List<T>& L ) { merge ( first(), size, L, L.first(), L._size ); } //ȫ�б�鲢

	void sort ( ListNodePosi(T) p, int n ) //�б���������
	{
		mergeSort ( p, n );
	}

	void sort() { sort ( first(), _size ); } //�б���������

	//����ȥ��
	int deduplicate()
	{
		if ( _size < 2 ) return 0; //ƽ���б���Ȼ���ظ�
		int oldSize = _size; //��¼ԭ��ģ
		ListNodePosi(T) p = header; Rank r = 0; //p���׽ڵ㿪ʼ
		while ( trailer != ( p = p->succ ) ) { //����ֱ��ĩ�ڵ�
			ListNodePosi(T) q = find ( p->data, r, p ); //��p��r�����棩ǰ���в�����ͬ��
			q ? remove ( q ) : r++; //����ȷ���ڣ���ɾ��֮�������ȼ�һ
		} //assert: ѭ�������е�����ʱ�̣�p������ǰ��������ͬ
		return oldSize - _size; //�б��ģ�仯��������ɾ��Ԫ������
	}

	//����ȥ��
	int uniquify()
	{
		if ( _size < 2 ) return 0; //ƽ���б���Ȼ���ظ�
		int oldSize = _size; //��¼ԭ��ģ
		ListNodePosi(T) p = first(); ListNodePosi(T) q; //pΪ��������㣬qΪ����
		while ( trailer != ( q = p->succ ) ) //����������ڵĽڵ��(p, q)
			if ( p->data != q->data ) p = q; //�����죬��ת����һ����
			else remove ( q ); //������ͬ����ɾ������
			return oldSize - _size; //�б��ģ�仯��������ɾ��Ԫ������
	}

	//ǰ���ã�ϰ�⣩
	void reverse()
	{
		ListNodePosi(T) p = header; ListNodePosi(T) q = trailer; //ͷ��β�ڵ�
		for ( int i = 1; i < _size; i += 2 ) //�����ס�ĩ�ڵ㿪ʼ��������ڣ�׽�Ե�
			swap ( ( p = p->succ )->data, ( q = q->pred )->data ); //�����Գƽڵ��������
	}

	// ����
	void traverse ( void (* visit) ( T& ) )
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }

	template <typename VST> //������
	void traverse ( VST& visit)
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
}; //List

#endif