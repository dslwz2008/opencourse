#include "List.h"

//�����±����������ͨ����ֱ�ӷ����б�ڵ㣨�䷽�㣬Ч�ʵͣ������ã�
template <typename T> 
T& List<T>::operator[] ( Rank r ) const 
{ 
	//assert: 0 <= r < size
	ListNodePosi(T) p = first(); //���׽ڵ����
	while ( 0 < r-- ) p = p->succ; //˳����r���ڵ㼴��
	return p->data; //Ŀ��ڵ㣬������������Ԫ��
}

