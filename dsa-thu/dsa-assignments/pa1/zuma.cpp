#include <stdio.h>

typedef int Rank; //��
#define ListNodePosi(T) ListNode<T>* //�б�ڵ�λ��

template <typename T> struct ListNode { //�б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
	// ��Ա
	T data; ListNodePosi(T) pred; ListNodePosi(T) succ; //��ֵ��ǰ�������
	// ���캯��
	ListNode() {} //���header��trailer�Ĺ���
	ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
		: data ( e ), pred ( p ), succ ( s ) {} //Ĭ�Ϲ�����
	// �����ӿ�
	ListNodePosi(T) insertAsPred ( T const& e ){
		ListNodePosi(T) x = new ListNode ( e, pred, this ); //�����½ڵ�
		pred->succ = x; pred = x; //������������
		return x; //�����½ڵ��λ��
	} //������ǰ�ڵ�֮ǰ�����½ڵ�

	ListNodePosi(T) insertAsSucc ( T const& e ){
		ListNodePosi(T) x = new ListNode ( e, this, succ ); //�����½ڵ�
		succ->pred = x; succ = x; //������������
		return x; //�����½ڵ��λ��
	} //���浱ǰ�ڵ�֮������½ڵ�

};

template <typename T> class List {
private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //��ģ��ͷ�ڱ���β�ڱ�

protected:
	void init(){ //�б��ʼ�����ڴ����б����ʱͳһ����
		header = new ListNode<T>; //����ͷ�ڱ��ڵ�
		trailer = new ListNode<T>; //����β�ڱ��ڵ�
		header->succ = trailer; header->pred = NULL;
		trailer->pred = header; trailer->succ = NULL;
		_size = 0; //��¼��ģ
	}
	int clear(){ //����б�
		int oldSize = _size;
		while ( 0 < _size ) remove ( header->succ ); //����ɾ���׽ڵ㣬ֱ���б���
		return oldSize;
	}

public:
	// ���캯��
	List() { init(); } //Ĭ��
	// ��������
	~List(){ clear(); delete header; delete trailer; } //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
	// ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ
	bool empty() const { return _size <= 0; } //�п�
	// ��д���ʽӿ�
	ListNodePosi(T) insertAsFirst ( T const& e ); //��e�����׽ڵ����
	ListNodePosi(T) insertAsLast ( T const& e ); //��e����ĩ�ڵ����
	ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e ); //��e����p�ĺ�̲���
	ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e ); //��e����p��ǰ������
	T remove ( ListNodePosi(T) p ); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
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