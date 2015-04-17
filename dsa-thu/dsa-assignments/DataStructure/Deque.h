#ifndef DEQUE_H
#define DEQUE_H

#include "List.h"

//双端队列模板类（继承List原有接口）
template <typename T> class Deque: public List<T> 
{ 
public: 
	void insertFront ( T const& e ) 
	{
		this->insertAsFirst ( e ); 
	} //从前面插入

	T removeFront() 
	{
		return this->remove ( this->first() ); 
	} //从前面删除

	void insertRear ( T const& e ) 
	{
		this->insertAsLast ( e ); 
	} //尾部插入

	T removeRear() 
	{
		return this->remove ( this->last() ); 
	} //尾部删除

	T& front() 
	{
		return this->first()->data; 
	} //队首

	T& rear() 
	{
		return this->last()->data; 
	}
};

#endif