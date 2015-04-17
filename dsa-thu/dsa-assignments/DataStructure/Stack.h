#ifndef STACK_H
#define STACK_H

#include "List.h" //���б�Ϊ���࣬������ջģ����
template <typename T> class Stack: public List<T> 
{ 
	//���б����/ĩ����Ϊջ��/��
public: 
	//size()��empty()�Լ��������Žӿڣ�����ֱ������
	//��ջ����Ч�ڽ���Ԫ����Ϊ�б����Ԫ�ز���
	void push ( T const& e ) 
	{ 
		insertAsLast ( e ); 
	}

	//��ջ����Ч��ɾ���б����Ԫ��
	T pop()
	{
		return remove ( last() ); 
	}

	//ȡ����ֱ�ӷ����б����Ԫ��
	T& top()
	{ 
		return last()->data; 
	} 
};

#endif