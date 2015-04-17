#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"

//����ģ���ࣨ�̳�Listԭ�нӿڣ�
template <typename T> class Queue: public List<T> 
{ 
public: //size()��empty()�Լ��������Žӿھ���ֱ������
	void enqueue ( T const& e ) 
	{ 
		insertAsLast ( e ); 
	} //��ӣ�β������

	T dequeue() 
	{ 
		return remove ( first() ); 
	} //���ӣ��ײ�ɾ��

	T& front() 
	{ 
		return first()->data; 
	} //����
};

#endif