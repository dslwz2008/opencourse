#include <stdio.h>
#include <string.h>

typedef int Rank; //��
#define ListNodePosi(T) ListNode<T>* //�б�ڵ�λ��

void print_data(char data){
	printf("%c", data);
}

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
	ListNodePosi(T) first() const { return header->succ; } //�׽ڵ�λ��
	ListNodePosi(T) last() const { return trailer->pred; } //ĩ�ڵ�λ��
	// ��д���ʽӿ�
	ListNodePosi(T) insertAsFirst ( T const& e ) //��e�����׽ڵ����
	{  _size++; return header->insertAsSucc ( e );  }
	ListNodePosi(T) insertAsLast ( T const& e ) //��e����ĩ�ڵ����
	{  _size++; return trailer->insertAsPred ( e );  }
	ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e )
	{  _size++; return p->insertAsSucc ( e );  } //��e����p�ĺ�̲���
	ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e )
	{  _size++; return p->insertAsPred ( e );  }//��e����p��ǰ������
	ListNodePosi(T) insertAt ( Rank rank, T const& e)
	{
		Rank idx = 0;
		ListNodePosi(T) p = NULL;
		if (empty())
		{
			p = header;
		}
		else
		{
			p = first();
		}
		
		while (idx < rank && p != NULL)
		{
			p = p->succ; idx++;
		}		
		_size++; 
		return p->insertAsPred ( e );  
	} //��e����p�ĺ�̲���

	T remove ( ListNodePosi(T) p )//ɾ���Ϸ��ڵ�p����������ֵ
	{ 
		T e = p->data; //���ݴ�ɾ���ڵ����ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ��
		p->pred->succ = p->succ; p->succ->pred = p->pred; //��̡�ǰ��
		delete p; p = NULL; _size--; //�ͷŽڵ㣬���¹�ģ
		return e; //���ر��ݵ���ֵ
	}

	// ����
	void traverse ( void (* visit) ( T& ) )
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
	template <typename VST> //������
	void traverse ( VST& visit)
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
}; //List

bool check(ListNodePosi(char) node, ListNodePosi(char) *from, ListNodePosi(char) *to){
	ListNodePosi(char) curr = node;
	int x = 0, y = 0;
	while (curr->pred != NULL && curr->pred->data == node->data)
	{
		x++;
		curr = curr->pred;
	}
	*from = curr;
	curr = node;
	while (curr->succ != NULL && curr->succ->data == node->data)
	{
		y++;
		curr = curr->succ;
	}
	*to = curr->succ;//ָ���һ���仯��Ԫ��
	return x + y >= 2;
}

int main(){

#ifndef _OJ_
	freopen("input_zuma.txt", "r", stdin);
	//freopen("output_zuma.txt", "w", stdout);
#endif

	//read
	int n = 0;
	char s[10001];
	scanf("%s", &s);
	int length = strlen(s);
	List<char> list;
	ListNodePosi(char) cur = list.insertAsFirst(s[0]);
	for (int i = 1; i < length; i++)
	{
		cur = list.insertA(cur, s[i]);
	}

	//print list
	if (list.empty())
	{
		printf("-");
	}
	else
	{
		list.traverse(print_data);
	}
	printf("\n");

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int pos = -1;
		char c = '\0';
		scanf("%d %c", &pos, &c);
		//printf("%d %c", pos, c);
		ListNodePosi(char) node = list.insertAt(pos, c);
		ListNodePosi(char) from = NULL; ListNodePosi(char) to = NULL;
		while (check(node, &from, &to))
		{
			while (from != to)
			{
				from = from->succ;
				list.remove(from->pred);
			}
			node = from;
		}
		//print list
		if (list.empty())
		{
			printf("-");
		}
		else
		{
			list.traverse(print_data);
		}
		printf("\n");
	}

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