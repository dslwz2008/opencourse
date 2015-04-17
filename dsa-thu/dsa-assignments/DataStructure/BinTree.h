#ifndef BINTREE_H
#define BINTREE_H

#include "BinNode.h"

//������ģ����
template <typename T> 
class BinTree {
protected:
	int _size; BinNodePosi(T) _root; //��ģ�����ڵ�

	//���½ڵ�x�ĸ߶�
	virtual int updateHeight ( BinNodePosi(T) x )
	{
		return x->height = 1 + max ( stature ( x->lc ), stature ( x->rc ) ); 
	}

	//���½ڵ�x�������ȵĸ߶�
	void updateHeightAbove ( BinNodePosi(T) x )
	{ 
		while ( x ) { updateHeight ( x ); x = x->parent; } 
	} //��x�����������������ȡ����Ż�

public:
	BinTree() : _size ( 0 ), _root ( NULL ) { } //���캯��
	~BinTree() { if ( 0 < _size ) remove ( _root ); } //��������

	int size() const { return _size; } //��ģ
	bool empty() const { return !_root; } //�п�

	BinNodePosi(T) root() const { return _root; } //����

	//������ڵ�
	BinNodePosi(T) insertAsRoot ( T const& e )
	{
		_size = 1; return _root = new BinNode<T> ( e );
	}

	BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e )
	{
		_size++; x->insertAsLC ( e ); updateHeightAbove ( x ); return x->lc; 
	} //e����Ϊx������

	BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e )
	{
		_size++; x->insertAsRC ( e ); updateHeightAbove ( x ); return x->rc;
	} //e����Ϊx���Һ���

	//���������������㷨����S�����ڵ�x�����������룬S�����ÿ�	
	BinNodePosi(T) attachAsLC ( BinNodePosi(T) x, BinTree<T>* &S ) 
	{ 
		//x->lc == NULL
		if ( x->lc = S->_root ) x->lc->parent = x; //����
		_size += S->_size; updateHeightAbove ( x ); //����ȫ����ģ��x�������ȵĸ߶�
		S->_root = NULL; S->_size = 0; release ( S ); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
	}

	//���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
	BinNodePosi(T) attachAsRC ( BinNodePosi(T) x, BinTree<T>* &S )
	{ 
		//x->rc == NULL
		if ( x->rc = S->_root ) x->rc->parent = x; //����
		_size += S->_size; updateHeightAbove ( x ); //����ȫ����ģ��x�������ȵĸ߶�
		S->_root = NULL; S->_size = 0; release ( S ); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
	}



	//ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
	int BinTree<T>::remove ( BinNodePosi(T) x )
	{ 
		//assert: xΪ�������еĺϷ�λ��
		FromParentTo ( *x ) = NULL; //�ж����Ը��ڵ��ָ��
		updateHeightAbove ( x->parent ); //�������ȸ߶�
		int n = removeAt ( x ); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
	}

	//ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
	int removeAt ( BinNodePosi(T) x )
	{ 
		//assert: xΪ�������еĺϷ�λ��
		if ( !x ) return 0; //�ݹ��������
		int n = 1 + removeAt ( x->lc ) + removeAt ( x->rc ); //�ݹ��ͷ���������
		//release ( x->data ); //shenshen:�����ָ�����͵����ݣ����������й¶
		if ( x ) { delete x; } //������а���ָ�룬�ݹ��ͷ�
		return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
	}

	//���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
	BinTree<T>* secede ( BinNodePosi(T) x ) 
	{
		//assert: xΪ�������еĺϷ�λ��
		FromParentTo ( *x ) = NULL; //�ж����Ը��ڵ��ָ��
		updateHeightAbove ( x->parent ); //����ԭ�����������ȵĸ߶�
		BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //������xΪ��
		S->_size = x->size(); _size -= S->_size; return S; //���¹�ģ�����ط������������
	}

	template <typename VST> //������
	void travLevel ( VST& visit ) { if ( _root ) _root->travLevel ( visit ); } //��α���

	template <typename VST> //������
	void travPre ( VST& visit ) { if ( _root ) _root->travPre ( visit ); } //�������

	template <typename VST> //������
	void travIn ( VST& visit ) { if ( _root ) _root->travIn ( visit ); } //�������

	template <typename VST> //������
	void travPost ( VST& visit ) { if ( _root ) _root->travPost ( visit ); } //�������

	bool operator< ( BinTree<T> const& t ) //�Ƚ������������в��䣩
	{ return _root && t._root && lt ( _root, t._root ); }

	bool operator== ( BinTree<T> const& t ) //�е���
	{ return _root && t._root && ( _root == t._root ); }


	void stretchToLPath() { stretchByZag ( _root ); } //����zag��ת��ת��Ϊ������
	void stretchToRPath() { stretchByZig ( _root, _size ); } //����zig��ת��ת��Ϊ������
}; //BinTree

#endif