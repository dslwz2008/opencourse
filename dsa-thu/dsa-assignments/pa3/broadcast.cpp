#include <stdio.h>
#include <stdlib.h>

//fast io
const int SZ = 1<<20;
struct fastio{
	char inbuf[SZ];
	char outbuf[SZ];
	fastio(){
		setvbuf(stdin,inbuf,_IOFBF,SZ);
		setvbuf(stdout,outbuf,_IOFBF,SZ);
	}
}io;

typedef int Rank; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

#define ListNodePosi(T) ListNode<T>* //�б�ڵ�λ��

template <typename T> struct ListNode {
	//��ֵ��ǰ�������
	T data;
	ListNodePosi(T) pred;
	ListNodePosi(T) succ;

	// ���캯��
	//���header��trailer�Ĺ���
	ListNode() {} 
	ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
		: data ( e ), pred ( p ), succ ( s ) {} //Ĭ�Ϲ�����

	// �����ӿ�
	//������ǰ�ڵ�֮ǰ�����½ڵ�
	ListNodePosi(T) insertAsPred ( T const& e ) 
	{
		ListNodePosi(T) x = new ListNode ( e, pred, this ); //�����½ڵ�
		pred->succ = x; pred = x; //������������
		return x; //�����½ڵ��λ��
	}

	//���浱ǰ�ڵ�֮������½ڵ�
	ListNodePosi(T) insertAsSucc ( T const& e )
	{
		ListNodePosi(T) x = new ListNode ( e, this, succ ); //�����½ڵ�
		succ->pred = x; succ = x; //������������
		return x; //�����½ڵ��λ��
	}
};

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

public:
	// ���캯��
	List() { init(); } //Ĭ��

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

	// ����
	void traverse ( void (* visit) ( T& ) )
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }

	template <typename VST> //������
	void traverse ( VST& visit)
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
}; //List

//����ģ���ࣨ�̳�Listԭ�нӿڣ�
template <typename T> class Queue: public List<T> 
{ 
public: //size()��empty()�Լ��������Žӿھ���ֱ������
	void enqueue ( T const& e ) 
	{ 
		this->insertAsLast ( e ); 
	} //��ӣ�β������

	T dequeue() 
	{ 
		return this->remove ( this->first() ); 
	} //���ӣ��ײ�ɾ��

	T& front() 
	{ 
		return this->first()->data; 
	} //����
};

class Graph
{
	int V;    // No. of vertices
	List<int> *adj;    // Pointer to an array containing adjacency lists
public:
	Graph(int V);  // Constructor
	void addEdge(int v, int w); // function to add an edge to graph
	bool BFS(int n);  // prints BFS traversal from a given source s
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new List<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].insertAsLast(w);
}

bool Graph::BFS(int n)
{
	bool *visited = new bool[V];
	for(int i = 0; i < V; i++)
		visited[i] = false;

	//for (int n =0; n < V; n++)
	//{
	//	if (!visited[n])
	//	{	
			Queue<int> queue;
			visited[n] = true;
			queue.enqueue(n);

			while(!queue.empty())
			{
				int v = queue.dequeue();
				//printf("%d\t",v);
				if (adj[v].size() > 2)
				{
					return false;
				}
				for(int i = 0; i < adj[v].size(); ++i)
				{
					if(!visited[adj[v][i]])
					{
						visited[adj[v][i]] = true;
						queue.enqueue(adj[v][i]);
					}
				}
			}
	//	}
	//}

	return true;
}
//int main()
//{
//	// Create a graph given in the above diagram
//	Graph g(2);
//	g.addEdge(0, 1);
//	g.addEdge(1, 0);
//
//	g.addEdge(2, 4);
//	g.addEdge(4, 2);
//	g.addEdge(2, 3);
//	g.addEdge(3, 2);
//	g.addEdge(3, 4);
//	g.addEdge(4, 3);
//	g.addEdge(3, 5);
//	g.addEdge(5, 3);
//
//	bool result = g.BFS();
//	printf("%d", result ? 1: 0);
//
//	return 0;
//}

int main(){
#ifndef _OJ_
	freopen("input_broadcast.txt", "r", stdin);
	//freopen("output_lh.txt", "w", stdout);
#endif
	int n,m;
	scanf("%d %d", &n, &m);
	int *from  = new int[m];
	int *to = new int[m];
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &from[i], &to[i]);
	}

	Graph g(n);
	for (int i = 0; i < m; i++)
	{
		g.addEdge(from[i] - 1, to[i] - 1);
		g.addEdge(to[i] - 1, from[i] - 1);
	}

	bool result = g.BFS(0);
	printf("%d", result ? 1: -1);
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
