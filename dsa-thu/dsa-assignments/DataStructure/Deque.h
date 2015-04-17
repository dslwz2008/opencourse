#ifndef DEQUE_H
#define DEQUE_H

#include "List.h"

//˫�˶���ģ���ࣨ�̳�Listԭ�нӿڣ�
template <typename T> class Deque: public List<T> 
{ 
public: 
	void insertFront ( T const& e ) 
	{
		this->insertAsFirst ( e ); 
	} //��ǰ�����

	T removeFront() 
	{
		return this->remove ( this->first() ); 
	} //��ǰ��ɾ��

	void insertRear ( T const& e ) 
	{
		this->insertAsLast ( e ); 
	} //β������

	T removeRear() 
	{
		return this->remove ( this->last() ); 
	} //β��ɾ��

	T& front() 
	{
		return this->first()->data; 
	} //����

	T& rear() 
	{
		return this->last()->data; 
	}
};

#endif