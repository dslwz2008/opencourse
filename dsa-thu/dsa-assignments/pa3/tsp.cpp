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
//typedef int Rank; //秩
//#define ListNodePosi(T) ListNode<T>* //列表节点位置
//
//template <typename T> struct ListNode {
//	//数值、前驱、后继
//	T data;
//	ListNodePosi(T) pred;
//	ListNodePosi(T) succ;
//
//	// 构造函数
//	//针对header和trailer的构造
//	ListNode() {} 
//	ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
//		: data ( e ), pred ( p ), succ ( s ) {} //默认构造器
//
//	// 操作接口
//	//紧靠当前节点之前插入新节点
//	ListNodePosi(T) insertAsPred ( T const& e ) 
//	{
//		ListNodePosi(T) x = new ListNode ( e, pred, this ); //创建新节点
//		pred->succ = x; pred = x; //设置正向链接
//		return x; //返回新节点的位置
//	}
//
//	//紧随当前节点之后插入新节点
//	ListNodePosi(T) insertAsSucc ( T const& e )
//	{
//		ListNodePosi(T) x = new ListNode ( e, this, succ ); //创建新节点
//		succ->pred = x; succ = x; //设置逆向链接
//		return x; //返回新节点的位置
//	}
//};
//
////列表模板类
//template <typename T> class List 
//{
//private:
//	//规模、头哨兵、尾哨兵
//	int _size;
//	ListNodePosi(T) header;
//	ListNodePosi(T) trailer;
//
//protected:
//	void init()
//	{
//		header = new ListNode<T>; //创建头哨兵节点
//		trailer = new ListNode<T>; //创建尾哨兵节点
//		header->succ = trailer; header->pred = NULL;
//		trailer->pred = header; trailer->succ = NULL;
//		_size = 0; //记录规模
//	}
//
//	int clear()
//	{
//		int oldSize = _size;
//		while ( 0 < _size ) remove ( header->succ ); //反复删除首节点，直至列表变空
//		return oldSize;
//	}
//
//public:
//	// 构造函数
//	List() { init(); } //默认
//
//	//列表析构器
//	~List()
//	{
//		//清空列表，释放头、尾哨兵节点
//		clear(); delete header; delete trailer; 
//	}
//
//	// 只读访问接口
//	Rank size() const { return _size; } //规模
//
//	bool empty() const { return _size <= 0; } //判空
//
//	//重载，支持循秩访问（效率低）
//	T& operator[] ( Rank r ) const
//	{ 
//		//assert: 0 <= r < size
//		ListNodePosi(T) p = first(); //从首节点出发
//		while ( 0 < r-- ) p = p->succ; //顺数第r个节点即是
//		return p->data; //目标节点，返回其中所存元素
//	}
//
//	ListNodePosi(T) first() const { return header->succ; } //首节点位置
//
//	ListNodePosi(T) last() const { return trailer->pred; } //末节点位置
//
//	// 可写访问接口
//	//将e当作首节点插入
//	ListNodePosi(T) insertAsFirst ( T const& e )
//	{
//		_size++; return header->insertAsSucc ( e );
//	}
//
//	//将e当作末节点插入
//	ListNodePosi(T) insertAsLast ( T const& e )
//	{
//		_size++; return trailer->insertAsPred ( e );  
//	}
//
//	//将e当作p的后继插入
//	ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e )
//	{
//		_size++; return p->insertAsSucc ( e );
//	}
//
//	//将e当作p的前驱插入
//	ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e )
//	{
//		_size++; return p->insertAsPred ( e );
//	}
//
//	//删除合法位置p处的节点,返回被删除节点
//	T remove ( ListNodePosi(T) p )
//	{
//		T e = p->data; //备份待删除节点的数值（假定T类型可直接赋值）
//		p->pred->succ = p->succ; p->succ->pred = p->pred; //后继、前驱
//		delete p; _size--; //释放节点，更新规模
//		return e; //返回备份的数值
//	}
//
//	// 遍历
//	void traverse ( void (* visit) ( T& ) )
//	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
//
//	template <typename VST> //操作器
//	void traverse ( VST& visit)
//	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
//}; //List
//
////队列模板类（继承List原有接口）
//template <typename T> class Queue: public List<T> 
//{ 
//public: //size()、empty()以及其它开放接口均可直接沿用
//	void enqueue ( T const& e ) 
//	{ 
//		this->insertAsLast ( e ); 
//	} //入队：尾部插入
//
//	T dequeue() 
//	{ 
//		return this->remove ( this->first() ); 
//	} //出队：首部删除
//
//	T& front() 
//	{ 
//		return this->first()->data; 
//	} //队首
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
////有向图，默认权重1
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
////拓扑排序
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
//		if (adj[u].size() == 0)//出度为0的节点
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
