#include <stdio.h>
#include <stdlib.h>

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

typedef int Rank; //��
typedef unsigned int uint;
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
	}
	ListNodePosi(T) insertAsSucc ( T const& e ){
		ListNodePosi(T) x = new ListNode ( e, this, succ ); //�����½ڵ�
		succ->pred = x; succ = x; //������������
		return x; //�����½ڵ��λ��
	}
};

template <typename T> class List { //�б�ģ����
private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //��ģ��ͷ�ڱ���β�ڱ�

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

public:
	// ���캯��
	List() { init(); } //Ĭ��
	List ( List<T> const& L ) { copyNodes ( L.first(), L._size ); } //���帴���б�L
	List ( List<T> const& L, Rank r, int n ){ copyNodes ( L[r], n ); } //�����б�L���Ե�r�����n��
	List ( ListNodePosi(T) p, int n ){ copyNodes ( p, n ); }//�����б�����λ��p���n��
	// ��������
	~List(){ clear(); delete header; delete trailer; } //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�

	// ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ
	bool empty() const { return _size <= 0; } //�п�
	T& operator[] ( Rank r ) const; //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
	ListNodePosi(T) first() const { return header->succ; } //�׽ڵ�λ��
	ListNodePosi(T) last() const { return trailer->pred; } //ĩ�ڵ�λ��
	bool valid ( ListNodePosi(T) p ) //�ж�λ��p�Ƿ����Ϸ�
	{ return p && ( trailer != p ) && ( header != p ); } //��ͷ��β�ڵ��ͬ��NULL

	// ��д���ʽӿ�
	ListNodePosi(T) insertAsFirst ( T const& e ) //��e�����׽ڵ����
	{  _size++; return header->insertAsSucc ( e );  }
	ListNodePosi(T) insertAsLast ( T const& e ) //��e����ĩ�ڵ����
	{  _size++; return trailer->insertAsPred ( e );  } 
	T remove ( ListNodePosi(T) p ) //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
	{
		T e = p->data; //���ݴ�ɾ���ڵ����ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ��
		p->pred->succ = p->succ; p->succ->pred = p->pred; //��̡�ǰ��
		delete p; _size--; //�ͷŽڵ㣬���¹�ģ
		return e; //���ر��ݵ���ֵ
	}
	void traverse ( void ( *visit ) ( T& ) ) //��������ָ����Ʊ���
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
	template <typename VST> //������
	void traverse ( VST& visit)
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
}; //List

template <typename T> class Queue: public List<T> { //����ģ���ࣨ�̳�Listԭ�нӿڣ�
public: //size()��empty()�Լ��������Žӿھ���ֱ������
	void enqueue ( T const& e ) { this->insertAsLast ( e ); } //��ӣ�β������
	T dequeue() { return this->remove ( this->first() ); } //���ӣ��ײ�ɾ��
	T& front() { return this->first()->data; } //����
};

template <typename T> class Deque: public List<T> { //˫�˶���ģ���ࣨ�̳�Listԭ�нӿڣ�
public: 
	void insertFront ( T const& e ) { this->insertAsFirst ( e ); } //��ǰ�����
	T removeFront() { return this->remove ( this->first() ); } //��ǰ��ɾ��
	void insertRear ( T const& e ) { this->insertAsLast ( e ); } //β������
	T removeRear() { return this->remove ( this->last() ); } //β��ɾ��
	T& front() { return this->first()->data; } //����
	T& rear() { return this->last()->data; }
};

struct ElemEx{
	uint key;
	uint counter;
}elemex;

int main(){

#ifndef _OJ_
	freopen("input_tunel.txt", "r", stdin);
	//freopen("output_lh.txt", "w", stdout);
#endif
	int n;
	scanf("%d\r\n", &n);
	char *action = new char[n];
	uint *height = new uint[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%c", &action[i]);
		switch (action[i])
		{
		case 'E':
			scanf("%u", &height[i]);
			break;
		case 'D':
		case 'M':
		default:
			break;
		}
		getchar();
		//getchar();
	}

	Queue<uint> q;
	Deque<ElemEx> p1;
	for (int i = 0; i < n; i++)
	{
		switch (action[i])
		{
		case 'E':
			{
				q.enqueue(height[i]);
				int a = 1;
				while(!p1.empty() && p1.rear().key <= height[i])
				{
					a += p1.removeRear().counter;
				}
				ElemEx elem; elem.key=height[i]; elem.counter=a;
				p1.insertRear(elem);
				break;
			}
		case 'D':
			{
				uint h = q.dequeue();
				if(!(--p1.front().counter))
				{
					p1.removeFront();
				}
				printf("%u\n",h);
				break;
			}
		case 'M':
			printf("%u\n",p1.front().key);
			break;
		default:
			break;
		}
	}

	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
