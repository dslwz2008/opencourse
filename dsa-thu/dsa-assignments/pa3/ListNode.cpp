#include "ListNode.h"

//��e���浱ǰ�ڵ�֮������ڵ�ǰ�ڵ������б������ڱ�β�ڵ�trailer��
template <typename T> 
ListNodePosi(T) ListNode<T>::insertAsSucc ( T const& e ) 
{
	ListNodePosi(T) x = new ListNode ( e, this, succ ); //�����½ڵ�
	succ->pred = x; succ = x; //������������
	return x; //�����½ڵ��λ��
}

//��e������ǰ�ڵ�֮ǰ�����ڵ�ǰ�ڵ������б������ڱ�ͷ�ڵ�header��
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred ( T const& e ) 
{
	ListNodePosi(T) x = new ListNode ( e, pred, this ); //�����½ڵ�
	pred->succ = x; pred = x; //������������
	return x; //�����½ڵ��λ��
}
