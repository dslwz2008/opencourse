//#include <stdio.h>
//#include <stdlib.h>
//
////fast io
//const int SZ = 1<<20;
//struct fastio{
//	char inbuf[SZ];
//	char outbuf[SZ];
//	fastio(){
//		setvbuf(stdin,inbuf,_IOFBF,SZ);
//		setvbuf(stdout,outbuf,_IOFBF,SZ);
//	}
//}io;
//
//typedef int Rank; //��
//#define ListNodePosi(T) ListNode<T>* //�б�ڵ�λ��
//
//template <typename T> struct ListNode { //�б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
//	// ��Ա
//	T data; ListNodePosi(T) pred; ListNodePosi(T) succ; //��ֵ��ǰ�������
//	// ���캯��
//	ListNode() {} //���header��trailer�Ĺ���
//	ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
//		: data ( e ), pred ( p ), succ ( s ) {} //Ĭ�Ϲ�����
//
//	// �����ӿ�
//	ListNodePosi(T) insertAsPred ( T const& e ){
//		ListNodePosi(T) x = new ListNode ( e, pred, this ); //�����½ڵ�
//		pred->succ = x; pred = x; //������������
//		return x; //�����½ڵ��λ��
//	}
//	ListNodePosi(T) insertAsSucc ( T const& e ){
//		ListNodePosi(T) x = new ListNode ( e, this, succ ); //�����½ڵ�
//		succ->pred = x; succ = x; //������������
//		return x; //�����½ڵ��λ��
//	}
//};
//
//template <typename T> class List { //�б�ģ����
//private:
//	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //��ģ��ͷ�ڱ���β�ڱ�
//
//protected:
//	void init()
//	{
//		header = new ListNode<T>; //����ͷ�ڱ��ڵ�
//		trailer = new ListNode<T>; //����β�ڱ��ڵ�
//		header->succ = trailer; header->pred = NULL;
//		trailer->pred = header; trailer->succ = NULL;
//		_size = 0; //��¼��ģ
//	}
//
//	int clear()
//	{
//		int oldSize = _size;
//		while ( 0 < _size ) remove ( header->succ ); //����ɾ���׽ڵ㣬ֱ���б���
//		return oldSize;
//	}
//
//public:
//	// ���캯��
//	List() { init(); } //Ĭ��
//	List ( List<T> const& L ) { copyNodes ( L.first(), L._size ); } //���帴���б�L
//	List ( List<T> const& L, Rank r, int n ){ copyNodes ( L[r], n ); } //�����б�L���Ե�r�����n��
//	List ( ListNodePosi(T) p, int n ){ copyNodes ( p, n ); }//�����б�����λ��p���n��
//	// ��������
//	~List(){ clear(); delete header; delete trailer; } //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
//
//	// ֻ�����ʽӿ�
//	Rank size() const { return _size; } //��ģ
//	bool empty() const { return _size <= 0; } //�п�
//	T& operator[] ( Rank r ) const; //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
//	ListNodePosi(T) first() const { return header->succ; } //�׽ڵ�λ��
//	ListNodePosi(T) last() const { return trailer->pred; } //ĩ�ڵ�λ��
//	bool valid ( ListNodePosi(T) p ) //�ж�λ��p�Ƿ����Ϸ�
//	{ return p && ( trailer != p ) && ( header != p ); } //��ͷ��β�ڵ��ͬ��NULL
//
//	// ��д���ʽӿ�
//	ListNodePosi(T) insertAsFirst ( T const& e ) //��e�����׽ڵ����
//	{  _size++; return header->insertAsSucc ( e );  }
//	ListNodePosi(T) insertAsLast ( T const& e ) //��e����ĩ�ڵ����
//	{  _size++; return trailer->insertAsPred ( e );  } 
//	T remove ( ListNodePosi(T) p ) //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
//	{
//		T e = p->data; //���ݴ�ɾ���ڵ����ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ��
//		p->pred->succ = p->succ; p->succ->pred = p->pred; //��̡�ǰ��
//		delete p; _size--; //�ͷŽڵ㣬���¹�ģ
//		return e; //���ر��ݵ���ֵ
//	}
//	void traverse ( void ( *visit ) ( T& ) ) //��������ָ����Ʊ���
//	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
//	template <typename VST> //������
//	void traverse ( VST& visit)
//	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
//}; //List
//
//template <typename T> class Stack: public List<T> { //���б����/ĩ����Ϊջ��/��
//public: //size()��empty()�Լ��������Žӿڣ�����ֱ������
//	void push ( T const& e ) { this->insertAsLast ( e ); } //��ջ����Ч�ڽ���Ԫ����Ϊ�б����Ԫ�ز���
//	T pop() { return this->remove ( this->last() ); } //��ջ����Ч��ɾ���б����Ԫ��
//	T& top() { return this->last()->data; } //ȡ����ֱ�ӷ����б����Ԫ��
//};
//
//void print_data(int data){
//	data == 0 ? printf("push\n") : printf("pop\n");
//}
//
//int main(){
//
//#ifndef _OJ_
//	freopen("input_train.txt", "r", stdin);
//	//freopen("output_lh.txt", "w", stdout);
//#endif
//	int n,m;
//	scanf("%d %d", &n, &m);
//	if (m == 0)
//	{
//		printf("No\n");
//		return 0;
//	}
//
//	int *target = new int[n];
//	Stack<int> A;
//	for (int i = 0; i < n; i++)
//	{
//		scanf("%d", &target[i]);
//		A.push(n-i);
//	}
//
//	Stack<int> S;
//	List<int> results;
//	bool dead = false;
//	for (int i = 0; i < n; i++)
//	{
//		while (S.empty() || S.top() < target[i])
//		{
//			if (S.size() < m)
//			{
//				S.push(A.pop());
//				results.insertAsLast(0);//printf("push\n");
//			}else
//			{
//				dead = true;
//				break;
//			}
//		}
//		if (dead)
//		{
//			break;
//		}
//		if (S.top() == target[i])
//		{
//			S.pop();
//			results.insertAsLast(1);//printf("pop\n");
//		}
//		else if (S.top() > target[i])
//		{
//			dead=true;//printf("No\n");
//			break;
//		}
//	}
//
//	if (dead)
//	{
//		printf("No\n");
//	}
//	else
//	{
//		results.traverse(print_data);
//	}
//
//	//fclose(stdin);
//	//fclose(stdout);
//	return 0;
//}
