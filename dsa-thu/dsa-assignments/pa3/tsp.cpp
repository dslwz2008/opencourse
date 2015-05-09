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
//template <typename T> struct ListNode {
//	//��ֵ��ǰ�������
//	T data;
//	ListNodePosi(T) pred;
//	ListNodePosi(T) succ;
//
//	// ���캯��
//	//���header��trailer�Ĺ���
//	ListNode() {} 
//	ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
//		: data ( e ), pred ( p ), succ ( s ) {} //Ĭ�Ϲ�����
//
//	// �����ӿ�
//	//������ǰ�ڵ�֮ǰ�����½ڵ�
//	ListNodePosi(T) insertAsPred ( T const& e ) 
//	{
//		ListNodePosi(T) x = new ListNode ( e, pred, this ); //�����½ڵ�
//		pred->succ = x; pred = x; //������������
//		return x; //�����½ڵ��λ��
//	}
//
//	//���浱ǰ�ڵ�֮������½ڵ�
//	ListNodePosi(T) insertAsSucc ( T const& e )
//	{
//		ListNodePosi(T) x = new ListNode ( e, this, succ ); //�����½ڵ�
//		succ->pred = x; succ = x; //������������
//		return x; //�����½ڵ��λ��
//	}
//};
//
////�б�ģ����
//template <typename T> class List 
//{
//private:
//	//��ģ��ͷ�ڱ���β�ڱ�
//	int _size;
//	ListNodePosi(T) header;
//	ListNodePosi(T) trailer;
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
//
//	//�б�������
//	~List()
//	{
//		//����б��ͷ�ͷ��β�ڱ��ڵ�
//		clear(); delete header; delete trailer; 
//	}
//
//	// ֻ�����ʽӿ�
//	Rank size() const { return _size; } //��ģ
//
//	bool empty() const { return _size <= 0; } //�п�
//
//	//���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
//	T& operator[] ( Rank r ) const
//	{ 
//		//assert: 0 <= r < size
//		ListNodePosi(T) p = first(); //���׽ڵ����
//		while ( 0 < r-- ) p = p->succ; //˳����r���ڵ㼴��
//		return p->data; //Ŀ��ڵ㣬������������Ԫ��
//	}
//
//	ListNodePosi(T) first() const { return header->succ; } //�׽ڵ�λ��
//
//	ListNodePosi(T) last() const { return trailer->pred; } //ĩ�ڵ�λ��
//
//	// ��д���ʽӿ�
//	//��e�����׽ڵ����
//	ListNodePosi(T) insertAsFirst ( T const& e )
//	{
//		_size++; return header->insertAsSucc ( e );
//	}
//
//	//��e����ĩ�ڵ����
//	ListNodePosi(T) insertAsLast ( T const& e )
//	{
//		_size++; return trailer->insertAsPred ( e );  
//	}
//
//	//��e����p�ĺ�̲���
//	ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e )
//	{
//		_size++; return p->insertAsSucc ( e );
//	}
//
//	//��e����p��ǰ������
//	ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e )
//	{
//		_size++; return p->insertAsPred ( e );
//	}
//
//	//ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
//	T remove ( ListNodePosi(T) p )
//	{
//		T e = p->data; //���ݴ�ɾ���ڵ����ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ��
//		p->pred->succ = p->succ; p->succ->pred = p->pred; //��̡�ǰ��
//		delete p; _size--; //�ͷŽڵ㣬���¹�ģ
//		return e; //���ر��ݵ���ֵ
//	}
//
//	// ����
//	void traverse ( void (* visit) ( T& ) )
//	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
//
//	template <typename VST> //������
//	void traverse ( VST& visit)
//	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
//}; //List
//
////����ģ���ࣨ�̳�Listԭ�нӿڣ�
//template <typename T> class Queue: public List<T> 
//{ 
//public: //size()��empty()�Լ��������Žӿھ���ֱ������
//	void enqueue ( T const& e ) 
//	{ 
//		this->insertAsLast ( e ); 
//	} //��ӣ�β������
//
//	T dequeue() 
//	{ 
//		return this->remove ( this->first() ); 
//	} //���ӣ��ײ�ɾ��
//
//	T& front() 
//	{ 
//		return this->first()->data; 
//	} //����
//};
//
//
//struct AdjListNode
//{
//	int _v;
//	int _weight;
//	AdjListNode() {_v=-1;_weight=-1;}
//	AdjListNode(int v, int w)  { _v = v;  _weight = w;}
//	int getV()       {  return _v;  }
//	int getWeight()  {  return _weight; }
//};
//
////����ͼ��Ĭ��Ȩ��1
//class Graph
//{
//	int _numV;
//	List<AdjListNode> *adj;
//	void tSort(int v, bool visited[], Queue<int> &queue);
//public:
//	Graph(int V);
//	void addEdge(int u, int v);
//	int longestPath();
//};
//
//Graph::Graph(int V)
//{
//	this->_numV = V;
//	adj = new List<AdjListNode>[V];
//}
//
//void Graph::addEdge(int u, int v)
//{
//	AdjListNode node(v, 1);
//	adj[u].insertAsLast(node);
//}
//
////��������
//void Graph::tSort(int v, bool visited[], Queue<int> &queue)
//{
//	visited[v] = true;
//	for (int i = 0; i < adj[v].size(); ++i)
//	{
//		AdjListNode node = adj[v][i];
//		if (!visited[node.getV()])
//			tSort(node.getV(), visited, queue);
//	}
//	queue.enqueue(v);
//}
//
//int Graph::longestPath()
//{
//	Queue<int> queue;
//	int *dist = new int[_numV];
//	bool *visited = new bool[_numV];
//	for (int i = 0; i < _numV; i++)
//	{
//		visited[i] = false;
//		dist[i] = 0;
//	}
//
//	for (int i = 0; i < _numV; i++)
//	{
//		if (visited[i] == false)
//		{
//			tSort(i, visited, queue);
//		}
//	}
//	
//	while (!queue.empty())
//	{
//		int u = queue.dequeue();
//		if (adj[u].size() == 0)//����Ϊ0�Ľڵ�
//		{
//			dist[u] = 1;
//		}
//		else
//		{
//			int maxdist = 0;
//			for (int j = 0; j < adj[u].size(); ++j)
//			{
//				if (dist[adj[u][j].getV()] > maxdist)
//				{
//					maxdist = dist[adj[u][j].getV()];
//				}
//			}
//			dist[u] = maxdist + 1;
//		}
//	}
//
//	int maxlen = 0;
//	for (int i = 0; i < _numV; i++)
//	{
//		if (dist[i] > maxlen)
//		{
//			maxlen = dist[i];
//		}
//	}
//	return maxlen;
//}
//
////int main()
////{
////	Graph g(4);
////	g.addEdge(0, 3);
////	g.addEdge(1, 3);
////	g.addEdge(3, 2);
////
////	printf("%d\n",g.longestPath());
////
////	return 0;
////}
////
//
//int main(){
//#ifndef _OJ_
//	freopen("input_tsp.txt", "r", stdin);
//	//freopen("output_lh.txt", "w", stdout);
//#endif
//	int n,m;
//	scanf("%d %d", &n, &m);
//	int *from  = new int[m];
//	int *to = new int[m];
//	for (int i = 0; i < m; i++)
//	{
//		scanf("%d %d", &from[i], &to[i]);
//	}
//	
//	Graph g(n);
//	for (int i = 0; i < m; i++)
//	{
//		g.addEdge(from[i] - 1, to[i] - 1);
//	}
//
//	printf("%d",g.longestPath());
//	//fclose(stdin);
//	//fclose(stdout);
//	return 0;
//}
