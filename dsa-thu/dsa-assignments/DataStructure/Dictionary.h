#ifndef DICTIONARY_H
#define DICTIONARY_H

template <typename K, typename V> struct Dictionary { //�ʵ�Dictionaryģ����
	virtual int size() const = 0; //��ǰ��������
	virtual bool put ( K, V ) = 0; //�����������ֹ��ͬ����ʱ����ʧ�ܣ�
	virtual V* get ( K k ) = 0; //��ȡ����
	virtual bool remove ( K k ) = 0; //ɾ������
};

#endif