#ifndef GRAPH_H
#define GRAPH_H

#include "Vector.h"
#include "Stack.h"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //边在遍历树中所属的类型

//图Graph模板类
template <typename Tv, typename Te> //顶点类型、边类型
class Graph 
{
private:
	//所有顶点、边的辅助信息复位
	void reset() {
		//所有顶点的
		for ( int i = 0; i < n; i++ ) { 
			status ( i ) = UNDISCOVERED; dTime ( i ) = fTime ( i ) = -1; //状态，时间标签
			parent ( i ) = -1; priority ( i ) = INT_MAX; //（在遍历树中的）父节点，优先级数
			//所有边的
			for ( int j = 0; j < n; j++ )
				if ( exists ( i, j ) ) 
					type ( i, j ) = UNDETERMINED; //类型
		}
	}


	//广度优先搜索BFS算法（单个连通域）
	void BFS ( int v, int& clock )
	{ 
		//assert: 0 <= v < n
		Queue<int> Q; //引入辅助队列
		status ( v ) = DISCOVERED; Q.enqueue ( v ); //初始化起点
		while ( !Q.empty() ) { //在Q变空之前，不断
			int v = Q.dequeue(); dTime ( v ) = ++clock; //取出队首顶点v
			for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //枚举v的所有邻居u
				if ( UNDISCOVERED == status ( u ) ) { //若u尚未被发现，则
					status ( u ) = DISCOVERED; Q.enqueue ( u ); //发现该顶点
					type ( v, u ) = TREE; parent ( u ) = v; //引入树边拓展支撑树
				} else { //若u已被发现，或者甚至已访问完毕，则
					type ( v, u ) = CROSS; //将(v, u)归类于跨边
				}
				status ( v ) = VISITED; //至此，当前顶点访问完毕
		}
	}

	//深度优先搜索DFS算法（单个连通域）
	void DFS ( int v, int& clock ) 
	{ 
		//assert: 0 <= v < n
		dTime ( v ) = ++clock; status ( v ) = DISCOVERED; //发现当前顶点v
		for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //枚举v的所有邻居u
			switch ( status ( u ) ) { //并视其状态分别处理
			case UNDISCOVERED: //u尚未发现，意味着支撑树可在此拓展
				type ( v, u ) = TREE; parent ( u ) = v; DFS ( u, clock ); break;
			case DISCOVERED: //u已被发现但尚未访问完毕，应属被后代指向的祖先
				type ( v, u ) = BACKWARD; break;
			default: //u已访问完毕（VISITED，有向图），则视承袭关系分为前向边或跨边
				type ( v, u ) = ( dTime ( v ) < dTime ( u ) ) ? FORWARD : CROSS; break;
		}
		status ( v ) = VISITED; fTime ( v ) = ++clock; //至此，当前顶点v方告访问完毕
	}


#define hca(x) (fTime(x)) //利用此处闲置的fTime[]充当hca[]
	//顶点类型、边类型
	void BCC ( int v, int& clock, Stack<int>& S ) { //assert: 0 <= v < n
		hca ( v ) = dTime ( v ) = ++clock; status ( v ) = DISCOVERED; S.push ( v ); //v被发现并入栈
		for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //枚举v的所有邻居u
			switch ( status ( u ) ) { //并视u的状态分别处理
			case UNDISCOVERED:
				parent ( u ) = v; type ( v, u ) = TREE; BCC ( u, clock, S ); //从顶点u处深入
				if ( hca ( u ) < dTime ( v ) ) //遍历返回后，若发现u（通过后向边）可指向v的真祖先
					hca ( v ) = min ( hca ( v ), hca ( u ) ); //则v亦必如此
				else { //否则，以v为关节点（u以下即是一个BCC，且其中顶点此时正集中于栈S的顶部）
					/*DSA*/printf ( "BCC rooted at %c:", vertex ( v ) );
					/*DSA*/Stack<int> temp; do { temp.push ( S.pop() ); print ( vertex ( temp.top() ) ); } while ( v != temp.top() ); while ( !temp.empty() ) S.push ( temp.pop() );
					while ( v != S.pop() ); //依次弹出当前BCC中的节点，亦可根据实际需求转存至其它结构
					S.push ( v ); //最后一个顶点（关节点）重新入栈——总计至多两次
					/*DSA*/printf ( "\n" );
				}
				break;
			case DISCOVERED:
				type ( v, u ) = BACKWARD; //标记(v, u)，并按照“越小越高”的准则
				if ( u != parent ( v ) ) hca ( v ) = min ( hca ( v ), dTime ( u ) ); //更新hca[v]
				break;
			default: //VISITED (digraphs only)
				type ( v, u ) = ( dTime ( v ) < dTime ( u ) ) ? FORWARD : CROSS;
				break;
		}
		status ( v ) = VISITED; //对v的访问结束
	}
#undef hca

	bool TSort ( int, int&, Stack<Tv>* ); //（连通域）基于DFS的拓扑排序算法
	template <typename PU> void PFS ( int, PU ); //（连通域）优先级搜索框架

public:
	// 顶点
	int n; //顶点总数
	virtual int insert ( Tv const& ) = 0; //插入顶点，返回编号
	virtual Tv remove ( int ) = 0; //删除顶点及其关联边，返回该顶点信息
	virtual Tv& vertex ( int ) = 0; //顶点v的数据（该顶点的确存在）
	virtual int inDegree ( int ) = 0; //顶点v的入度（该顶点的确存在）
	virtual int outDegree ( int ) = 0; //顶点v的出度（该顶点的确存在）
	virtual int firstNbr ( int ) = 0; //顶点v的首个邻接顶点
	virtual int nextNbr ( int, int ) = 0; //顶点v的（相对于顶点j的）下一邻接顶点
	virtual VStatus& status ( int ) = 0; //顶点v的状态
	virtual int& dTime ( int ) = 0; //顶点v的时间标签dTime
	virtual int& fTime ( int ) = 0; //顶点v的时间标签fTime
	virtual int& parent ( int ) = 0; //顶点v在遍历树中的父亲
	virtual int& priority ( int ) = 0; //顶点v在遍历树中的优先级数

	// 边：这里约定，无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
	int e; //边总数
	virtual bool exists ( int, int ) = 0; //边(v, u)是否存在
	virtual void insert ( Te const&, int, int, int ) = 0; //在顶点v和u之间插入权重为w的边e
	virtual Te remove ( int, int ) = 0; //删除顶点v和u之间的边e，返回该边信息
	virtual EType & type ( int, int ) = 0; //边(v, u)的类型
	virtual Te& edge ( int, int ) = 0; //边(v, u)的数据（该边的确存在）
	virtual int& weight ( int, int ) = 0; //边(v, u)的权重

	// 算法
	//广度优先搜索BFS算法（全图）
	void bfs ( int s ) 
	{ 
		//assert: 0 <= s < n
		reset(); int clock = 0; int v = s; //初始化
		do //逐一检查所有顶点
		if ( UNDISCOVERED == status ( v ) ) //一旦遇到尚未发现的顶点
			BFS ( v, clock ); //即从该顶点出发启动一次BFS
		while ( s != ( v = ( ++v % n ) ) ); //按序号检查，故不漏不重
	}

	//深度优先搜索DFS算法（全图）
	void dfs ( int s ) 
	{ 
		//assert: 0 <= s < n
		reset(); int clock = 0; int v = s; //初始化
		do //逐一检查所有顶点
		if ( UNDISCOVERED == status ( v ) ) //一旦遇到尚未发现的顶点
			DFS ( v, clock ); //即从该顶点出发启动一次DFS
		while ( s != ( v = ( ++v % n ) ) ); //按序号检查，故不漏不重
	}
	
	void bcc ( int s ) { //基于DFS的BCC分解算法
		reset(); int clock = 0; int v = s; Stack<int> S; //栈S用以记录已访问的顶点
		do
		if ( UNDISCOVERED == status ( v ) ) { //一旦发现未发现的顶点（新连通分量）
			BCC ( v, clock, S ); //即从该顶点出发启动一次BCC
			S.pop(); //遍历返回后，弹出栈中最后一个顶点——当前连通域的起点
		}
		while ( s != ( v = ( ++v % n ) ) );
	}

	
	Stack<Tv>* tSort ( int ); //基于DFS的拓扑排序算法
	void prim ( int ); //最小支撑树Prim算法
	void dijkstra ( int ); //最短路径Dijkstra算法
	template <typename PU> void pfs ( int, PU ); //优先级搜索框架
};


#endif