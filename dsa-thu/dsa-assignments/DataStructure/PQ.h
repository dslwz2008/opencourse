
#ifndef PQ_H
#define PQ_H

template <typename T> struct PQ { //���ȼ�����PQģ����
	virtual void insert ( T ) = 0; //���ձȽ���ȷ�������ȼ�����������
	virtual T getMax() = 0; //ȡ�����ȼ���ߵĴ���
	virtual T delMax() = 0; //ɾ�����ȼ���ߵĴ���
};

#endif
