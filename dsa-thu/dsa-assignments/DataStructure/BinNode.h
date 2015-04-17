#ifndef BINNODE_H
#define BINNODE_H

#include "Stack.h"

/******************************************************************************************
 * BinNode״̬�����ʵ��ж�
 ******************************************************************************************/
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //����ӵ��һ������
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //ͬʱӵ����������
#define IsLeaf(x) ( ! HasChild(x) )

/******************************************************************************************
 * ��BinNode�����ض���ϵ�Ľڵ㼰ָ��
 ******************************************************************************************/
#define sibling(p) /*�ֵ�*/ \
   ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc )

#define uncle(x) /*����*/ \
   ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )

#define FromParentTo(x) /*���Ը��׵�����*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )

//avl
#define HeightUpdated(x) /*�߶ȸ��³�������*/ \
        ( (x).height == 1 + max( stature( (x).lc ), stature( (x).rc ) ) )
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //����ƽ������
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //ƽ������
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVLƽ������

//redblack
#define IsBlack(p) ( ! (p) || ( RB_BLACK == (p)->color ) ) //�ⲿ�ڵ�Ҳ�����ڽڵ�
#define IsRed(p) ( ! IsBlack(p) ) //�Ǻڼ���
#define BlackHeightUpdated(x) ( /*RedBlack�߶ȸ�������*/ \
	( stature( (x).lc ) == stature( (x).rc ) ) && \
	( (x).height == ( IsRed(& x) ? stature( (x).lc ) : stature( (x).lc ) + 1 ) ) \
	)

#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(p) ((p) ? (p)->height : -1) //�ڵ�߶ȣ��롰�����߶�Ϊ-1����Լ����ͳһ��
typedef enum 
{ 
	RB_RED, 
	RB_BLACK
} RBColor; //�ڵ���ɫ

//�������ڵ�ģ����
template <typename T> struct BinNode 
{
	T data; //��ֵ
	//���ڵ㼰���Һ���
	BinNodePosi(T) parent; 
	BinNodePosi(T) lc; 
	BinNodePosi(T) rc;
	int height; //�߶ȣ�ͨ�ã�
	int npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
	RBColor color; //��ɫ���������
	// ���캯��
	BinNode() :
	parent ( NULL ), lc ( NULL ), rc ( NULL ), height ( 0 ), npl ( 1 ), color ( RB_RED ) { }

	BinNode ( T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED ) :
	data ( e ), parent ( p ), lc ( lc ), rc ( rc ), height ( h ), npl ( l ), color ( c ) { }

	// �����ӿ�
	//ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
	int size()
	{
		int s = 1; //���뱾��
		if ( lc ) s += lc->size(); //�ݹ������������ģ
		if ( rc ) s += rc->size(); //�ݹ������������ģ
		return s;
	}

	//��e��Ϊ��ǰ�ڵ�����Ӳ��������
	BinNodePosi(T) insertAsLC ( T const& e )
	{ return lc = new BinNode ( e, this ); } 

	//��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������
	BinNodePosi(T) insertAsRC ( T const& e )
	{ return rc = new BinNode ( e, this ); } 

	//��λ�ڵ�v��ֱ�Ӻ��
	BinNodePosi(T) succ() { 
		BinNodePosi(T) s = this; //��¼��̵���ʱ����
		if ( rc ) { //�����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
			s = rc; //��������
			while ( HasLChild ( *s ) ) s = s->lc; //�����С���Ľڵ�
		} else { //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���
			while ( IsRChild ( *s ) ) s = s->parent; //������������֧�����ϳ����Ϸ��ƶ�
			s = s->parent; //����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
		}
		return s;
	}


	//��������������㷨
	template <typename VST>
	void travPre ( VST& visit ) 
	{ 
		Stack<BinNodePosi(T)> S; //����ջ
		while ( true ) {
			visitAlongLeftBranch ( this, visit, S ); //�ӵ�ǰ�ڵ��������������
			if ( S.empty() ) break; //ֱ��ջ��
			this = S.pop(); //������һ�������
		}
	}


	//��������������㷨
	template <typename VST>
	void travIn ( VST& visit ) 
	{ 
		Stack<BinNodePosi(T)> S; //����ջ
		while ( true ) {
			goAlongLeftBranch ( this, S ); //�ӵ�ǰ�ڵ������������ջ
			if ( S.empty() ) break; //ֱ�����нڵ㴦�����
			this = S.pop(); visit ( this->data ); //����ջ���ڵ㲢����֮
			this = this->rc; //ת��������
		}
	}


	//�������ĺ�������������棩
	template <typename VST>
	void travPost ( VST& visit ) 
	{ 
		Stack<BinNodePosi(T)> S; //����ջ
		if ( this ) S.push ( this ); //���ڵ���ջ
		while ( !S.empty() ) {
			if ( S.top() != this->parent ) //��ջ���ǵ�ǰ�ڵ�֮�������Ϊ�����֣�����ʱ��
				gotoHLVFL ( S ); //����������Ϊ��֮�����У��ҵ�HLVFL���൱�ڵݹ��������У�
			this = S.pop(); visit ( this->data ); //����ջ������ǰһ�ڵ�֮��̣���������֮
		}
	}

	//��������α����㷨
	template <typename VST> 
	void travLevel ( VST& visit ) {
		Queue<BinNodePosi(T)> Q; //��������
		Q.enqueue ( this ); //���ڵ����
		while ( !Q.empty() ) { //�ڶ����ٴα��֮ǰ����������
			BinNodePosi(T) x = Q.dequeue(); visit ( x->data ); //ȡ�����׽ڵ㲢����֮
			if ( HasLChild ( *x ) ) Q.enqueue ( x->lc ); //�������
			if ( HasRChild ( *x ) ) Q.enqueue ( x->rc ); //�Һ������
		}
	}

	// �Ƚ������е�����������һ���������в��䣩
	bool operator< ( BinNode const& bn ) { return data < bn.data; } //С��
	bool operator== ( BinNode const& bn ) { return data == bn.data; } //����


	//˳ʱ����ת
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

	//��ʱ����ת
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

	//ͨ��zig��ת������������x��������Ҳ�ͨ·
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

	//ͨ��zag��ת������������x����������ͨ·
	void stretchByZag ( BinNodePosi(T) & x ) 
	{
		int c = 0; //��¼��ת����
		int h = 0;
		BinNodePosi(T) p = x; while ( p->rc ) p = p->rc; //���ڵ㣬�����������յĸ�
		while ( x->lc ) x = x->lc; x->height = h++; //ת����ʼ�����ͨ·��ĩ��
		for ( ; x != p; x = x->parent, x->height = h++ ) { //��x�������ѿգ�������һ��
			while ( x->rc ) //���򣬷�����
			{
				x->zag(); //��xΪ����zag��ת
				c++;
			}
		} //ֱ���ִ������ĸ�
	}


private:
	//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
	void goAlongLeftBranch ( BinNodePosi(T) x, Stack<BinNodePosi(T)>& S ) 
	{
		while ( x ) { S.push ( x ); x = x->lc; } //��ǰ�ڵ���ջ���漴������֧���룬����ֱ��������
	}

	//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ㣻��;�ڵ���������������
	template <typename VST>
	void visitAlongLeftBranch ( BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S ) 
	{
		while ( x ) {
			visit ( x->data ); //���ʵ�ǰ�ڵ�
			S.push ( x->rc ); //�Һ�����ջ�ݴ棨���Ż���ͨ���жϣ�����յ��Һ�����ջ��
			x = x->lc;  //�����֧����һ��
		}
	}

	//����Sջ���ڵ�Ϊ���������У��ҵ�������ɼ�Ҷ�ڵ�
	void gotoHLVFL ( Stack<BinNodePosi(T)>& S )
	{ 
		//��;�����ڵ�������ջ
		while ( BinNodePosi(T) x = S.top() ) //�Զ����£�������鵱ǰ�ڵ㣨��ջ����
			if ( HasLChild ( *x ) ) { //����������
				if ( HasRChild ( *x ) ) S.push ( x->rc ); //�����Һ��ӣ�������ջ
				S.push ( x->lc ); //Ȼ���ת������
			} else //ʵ������
				S.push ( x->rc ); //������
			S.pop(); //����֮ǰ������ջ���Ŀսڵ�
	}

};

#endif