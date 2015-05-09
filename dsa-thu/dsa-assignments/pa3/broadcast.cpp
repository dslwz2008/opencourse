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

typedef int Rank; //秩
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）

#define ListNodePosi(T) ListNode<T>* //列表节点位置

template <typename T> struct ListNode {
	//数值、前驱、后继
	T data;
	ListNodePosi(T) pred;
	ListNodePosi(T) succ;

	// 构造函数
	//针对header和trailer的构造
	ListNode() {} 
	ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
		: data ( e ), pred ( p ), succ ( s ) {} //默认构造器

	// 操作接口
	//紧靠当前节点之前插入新节点
	ListNodePosi(T) insertAsPred ( T const& e ) 
	{
		ListNodePosi(T) x = new ListNode ( e, pred, this ); //创建新节点
		pred->succ = x; pred = x; //设置正向链接
		return x; //返回新节点的位置
	}

	//紧随当前节点之后插入新节点
	ListNodePosi(T) insertAsSucc ( T const& e )
	{
		ListNodePosi(T) x = new ListNode ( e, this, succ ); //创建新节点
		succ->pred = x; succ = x; //设置逆向链接
		return x; //返回新节点的位置
	}
};

//列表模板类
template <typename T> class List 
{
private:
	//规模、头哨兵、尾哨兵
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;

protected:
	void init()
	{
		header = new ListNode<T>; //创建头哨兵节点
		trailer = new ListNode<T>; //创建尾哨兵节点
		header->succ = trailer; header->pred = NULL;
		trailer->pred = header; trailer->succ = NULL;
		_size = 0; //记录规模
	}

	int clear()
	{
		int oldSize = _size;
		while ( 0 < _size ) remove ( header->succ ); //反复删除首节点，直至列表变空
		return oldSize;
	}

public:
	// 构造函数
	List() { init(); } //默认

	//列表析构器
	~List()
	{
		//清空列表，释放头、尾哨兵节点
		clear(); delete header; delete trailer; 
	}

	// 只读访问接口
	Rank size() const { return _size; } //规模

	bool empty() const { return _size <= 0; } //判空

	//重载，支持循秩访问（效率低）
	T& operator[] ( Rank r ) const
	{ 
		//assert: 0 <= r < size
		ListNodePosi(T) p = first(); //从首节点出发
		while ( 0 < r-- ) p = p->succ; //顺数第r个节点即是
		return p->data; //目标节点，返回其中所存元素
	}

	ListNodePosi(T) first() const { return header->succ; } //首节点位置

	ListNodePosi(T) last() const { return trailer->pred; } //末节点位置

	// 可写访问接口
	//将e当作首节点插入
	ListNodePosi(T) insertAsFirst ( T const& e )
	{
		_size++; return header->insertAsSucc ( e );
	}

	//将e当作末节点插入
	ListNodePosi(T) insertAsLast ( T const& e )
	{
		_size++; return trailer->insertAsPred ( e );  
	}

	//将e当作p的后继插入
	ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e )
	{
		_size++; return p->insertAsSucc ( e );
	}

	//将e当作p的前驱插入
	ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e )
	{
		_size++; return p->insertAsPred ( e );
	}

	//删除合法位置p处的节点,返回被删除节点
	T remove ( ListNodePosi(T) p )
	{
		T e = p->data; //备份待删除节点的数值（假定T类型可直接赋值）
		p->pred->succ = p->succ; p->succ->pred = p->pred; //后继、前驱
		delete p; _size--; //释放节点，更新规模
		return e; //返回备份的数值
	}

	// 遍历
	void traverse ( void (* visit) ( T& ) )
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }

	template <typename VST> //操作器
	void traverse ( VST& visit)
	{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
}; //List

//队列模板类（继承List原有接口）
template <typename T> class Queue: public List<T> 
{ 
public: //size()、empty()以及其它开放接口均可直接沿用
	void enqueue ( T const& e ) 
	{ 
		this->insertAsLast ( e ); 
	} //入队：尾部插入

	T dequeue() 
	{ 
		return this->remove ( this->first() ); 
	} //出队：首部删除

	T& front() 
	{ 
		return this->first()->data; 
	} //队首
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
