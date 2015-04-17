#ifndef BINNODE_H
#define BINNODE_H

#include "Stack.h"

/******************************************************************************************
 * BinNode状态与性质的判断
 ******************************************************************************************/
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )

/******************************************************************************************
 * 与BinNode具有特定关系的节点及指针
 ******************************************************************************************/
#define sibling(p) /*兄弟*/ \
   ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc )

#define uncle(x) /*叔叔*/ \
   ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )

#define FromParentTo(x) /*来自父亲的引用*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )

//avl
#define HeightUpdated(x) /*高度更新常规条件*/ \
        ( (x).height == 1 + max( stature( (x).lc ), stature( (x).rc ) ) )
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //理想平衡条件
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //平衡因子
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVL平衡条件

//redblack
#define IsBlack(p) ( ! (p) || ( RB_BLACK == (p)->color ) ) //外部节点也视作黑节点
#define IsRed(p) ( ! IsBlack(p) ) //非黑即红
#define BlackHeightUpdated(x) ( /*RedBlack高度更新条件*/ \
	( stature( (x).lc ) == stature( (x).rc ) ) && \
	( (x).height == ( IsRed(& x) ? stature( (x).lc ) : stature( (x).lc ) + 1 ) ) \
	)

#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p) ? (p)->height : -1) //节点高度（与“空树高度为-1”的约定相统一）
typedef enum 
{ 
	RB_RED, 
	RB_BLACK
} RBColor; //节点颜色

//二叉树节点模板类
template <typename T> struct BinNode 
{
	T data; //数值
	//父节点及左、右孩子
	BinNodePosi(T) parent; 
	BinNodePosi(T) lc; 
	BinNodePosi(T) rc;
	int height; //高度（通用）
	int npl; //Null Path Length（左式堆，也可直接用height代替）
	RBColor color; //颜色（红黑树）
	// 构造函数
	BinNode() :
	parent ( NULL ), lc ( NULL ), rc ( NULL ), height ( 0 ), npl ( 1 ), color ( RB_RED ) { }

	BinNode ( T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED ) :
	data ( e ), parent ( p ), lc ( lc ), rc ( rc ), height ( h ), npl ( l ), color ( c ) { }

	// 操作接口
	//统计当前节点后代总数，亦即以其为根的子树的规模
	int size()
	{
		int s = 1; //计入本身
		if ( lc ) s += lc->size(); //递归计入左子树规模
		if ( rc ) s += rc->size(); //递归计入右子树规模
		return s;
	}

	//将e作为当前节点的左孩子插入二叉树
	BinNodePosi(T) insertAsLC ( T const& e )
	{ return lc = new BinNode ( e, this ); } 

	//将e作为当前节点的右孩子插入二叉树
	BinNodePosi(T) insertAsRC ( T const& e )
	{ return rc = new BinNode ( e, this ); } 

	//定位节点v的直接后继
	BinNodePosi(T) succ() { 
		BinNodePosi(T) s = this; //记录后继的临时变量
		if ( rc ) { //若有右孩子，则直接后继必在右子树中，具体地就是
			s = rc; //右子树中
			while ( HasLChild ( *s ) ) s = s->lc; //最靠左（最小）的节点
		} else { //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
			while ( IsRChild ( *s ) ) s = s->parent; //逆向地沿右向分支，不断朝左上方移动
			s = s->parent; //最后再朝右上方移动一步，即抵达直接后继（如果存在）
		}
		return s;
	}


	//二叉树先序遍历算法
	template <typename VST>
	void travPre ( VST& visit ) 
	{ 
		Stack<BinNodePosi(T)> S; //辅助栈
		while ( true ) {
			visitAlongLeftBranch ( this, visit, S ); //从当前节点出发，逐批访问
			if ( S.empty() ) break; //直到栈空
			this = S.pop(); //弹出下一批的起点
		}
	}


	//二叉树中序遍历算法
	template <typename VST>
	void travIn ( VST& visit ) 
	{ 
		Stack<BinNodePosi(T)> S; //辅助栈
		while ( true ) {
			goAlongLeftBranch ( this, S ); //从当前节点出发，逐批入栈
			if ( S.empty() ) break; //直至所有节点处理完毕
			this = S.pop(); visit ( this->data ); //弹出栈顶节点并访问之
			this = this->rc; //转向右子树
		}
	}


	//二叉树的后序遍历（迭代版）
	template <typename VST>
	void travPost ( VST& visit ) 
	{ 
		Stack<BinNodePosi(T)> S; //辅助栈
		if ( this ) S.push ( this ); //根节点入栈
		while ( !S.empty() ) {
			if ( S.top() != this->parent ) //若栈顶非当前节点之父（则必为其右兄），此时需
				gotoHLVFL ( S ); //在以其右兄为根之子树中，找到HLVFL（相当于递归深入其中）
			this = S.pop(); visit ( this->data ); //弹出栈顶（即前一节点之后继），并访问之
		}
	}

	//二叉树层次遍历算法
	template <typename VST> 
	void travLevel ( VST& visit ) {
		Queue<BinNodePosi(T)> Q; //辅助队列
		Q.enqueue ( this ); //根节点入队
		while ( !Q.empty() ) { //在队列再次变空之前，反复迭代
			BinNodePosi(T) x = Q.dequeue(); visit ( x->data ); //取出队首节点并访问之
			if ( HasLChild ( *x ) ) Q.enqueue ( x->lc ); //左孩子入队
			if ( HasRChild ( *x ) ) Q.enqueue ( x->rc ); //右孩子入队
		}
	}

	// 比较器、判等器（各列其一，其余自行补充）
	bool operator< ( BinNode const& bn ) { return data < bn.data; } //小于
	bool operator== ( BinNode const& bn ) { return data == bn.data; } //等于


	//顺时针旋转
	BinNodePosi(T) zig() 
	{ 
		BinNodePosi(T) lChild = lc;
		lChild->parent = this->parent;
		if ( lChild->parent )
			( ( this == lChild->parent->rc ) ? lChild->parent->rc : lChild->parent->lc ) = lChild;
		lc = lChild->rc; if ( lc ) lc->parent = this;
		lChild->rc = this; this->parent = lChild;
		return lChild;
	}

	//逆时针旋转
	BinNodePosi(T) zag() 
	{ 
		BinNodePosi(T) rChild = rc;
		rChild->parent = this->parent;
		if ( rChild->parent )
			( ( this == rChild->parent->lc ) ? rChild->parent->lc : rChild->parent->rc ) = rChild;
		rc = rChild->lc; if ( rc ) rc->parent = this;
		rChild->lc = this; this->parent = rChild;
		return rChild;
	}

	//通过zig旋转调整，将子树x拉伸成最右侧通路
	void stretchByZig ( BinNodePosi(T) & x, int h ) 
	{
		int c = 0;
		for ( BinNodePosi(T) v = x; v; v = v->rc ) {
			while ( v->lc )
			{
				v = v->zig();
				c++;
			}
			v->height = --h;
		}
		while ( x->parent ) x = x->parent;
	}

	//通过zag旋转调整，将子树x拉伸成最左侧通路
	void stretchByZag ( BinNodePosi(T) & x ) 
	{
		int c = 0; //记录旋转次数
		int h = 0;
		BinNodePosi(T) p = x; while ( p->rc ) p = p->rc; //最大节点，必是子树最终的根
		while ( x->lc ) x = x->lc; x->height = h++; //转至初始最左侧通路的末端
		for ( ; x != p; x = x->parent, x->height = h++ ) { //若x右子树已空，则上升一层
			while ( x->rc ) //否则，反复地
			{
				x->zag(); //以x为轴做zag旋转
				c++;
			}
		} //直到抵达子树的根
	}


private:
	//从当前节点出发，沿左分支不断深入，直至没有左分支的节点
	void goAlongLeftBranch ( BinNodePosi(T) x, Stack<BinNodePosi(T)>& S ) 
	{
		while ( x ) { S.push ( x ); x = x->lc; } //当前节点入栈后随即向左侧分支深入，迭代直到无左孩子
	}

	//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
	template <typename VST>
	void visitAlongLeftBranch ( BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S ) 
	{
		while ( x ) {
			visit ( x->data ); //访问当前节点
			S.push ( x->rc ); //右孩子入栈暂存（可优化：通过判断，避免空的右孩子入栈）
			x = x->lc;  //沿左分支深入一层
		}
	}

	//在以S栈顶节点为根的子树中，找到最高左侧可见叶节点
	void gotoHLVFL ( Stack<BinNodePosi(T)>& S )
	{ 
		//沿途所遇节点依次入栈
		while ( BinNodePosi(T) x = S.top() ) //自顶而下，反复检查当前节点（即栈顶）
			if ( HasLChild ( *x ) ) { //尽可能向左
				if ( HasRChild ( *x ) ) S.push ( x->rc ); //若有右孩子，优先入栈
				S.push ( x->lc ); //然后才转至左孩子
			} else //实不得已
				S.push ( x->rc ); //才向右
			S.pop(); //返回之前，弹出栈顶的空节点
	}

};

#endif