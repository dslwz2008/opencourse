#include "List.h"

//重载下标操作符，以通过秩直接访问列表节点（虽方便，效率低，需慎用）
template <typename T> 
T& List<T>::operator[] ( Rank r ) const 
{ 
	//assert: 0 <= r < size
	ListNodePosi(T) p = first(); //从首节点出发
	while ( 0 < r-- ) p = p->succ; //顺数第r个节点即是
	return p->data; //目标节点，返回其中所存元素
}

