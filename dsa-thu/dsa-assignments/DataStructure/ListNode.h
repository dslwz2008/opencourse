#ifndef LISTNODE_H
#define LISTNODE_H

typedef int Rank; //��
#define ListNodePosi(T) ListNode<T>* //�б�ڵ�λ��

//�б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
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

#endif