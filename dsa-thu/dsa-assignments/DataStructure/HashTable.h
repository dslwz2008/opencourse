/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Dictionary.h" //����ʵ�ADT

template <typename K, typename V> struct Entry { //����ģ����
	K key; V value; //�ؼ��롢��ֵ
	Entry ( K k = K(), V v = V() ) : key ( k ), value ( v ) {}; //Ĭ�Ϲ��캯��
	Entry ( Entry<K, V> const& e ) : key ( e.key ), value ( e.value ) {}; //���ڿ�¡�Ĺ��캯��
	bool operator< ( Entry<K, V> const& e ) { return key <  e.key; }  //�Ƚ�����С��
	bool operator> ( Entry<K, V> const& e ) { return key >  e.key; }  //�Ƚ���������
	bool operator== ( Entry<K, V> const& e ) { return key == e.key; } //�е���������
	bool operator!= ( Entry<K, V> const& e ) { return key != e.key; } //�е�����������
};

template <typename K, typename V>
class Hashtable : public Dictionary<K, V> { //����Dictionary�ӿڵ�Hashtableģ����

private:
   Entry<K, V>** ht; //Ͱ���飬��Ŵ���ָ��
   int M; //Ͱ��������
   int N; //��������
   int *_primes;
   int _curIdx;
   const int _count;

protected:
	//�عؼ���k��Ӧ�Ĳ��������ҵ�����ƥ���Ͱ
   int probe4Hit ( const K& k )
   {
	   int r = hashCode ( k ) % M; //����ʼͰ�������෨ȷ��������
	   while (  ht[r] && ( *k != *(ht[r]->key )) )
		   r = ( r + 1 ) % M; //�ز�����������̽���������г�ͻ��Ͱ
	   return r; //�����߸���ht[r]�Ƿ�Ϊ�գ������жϲ����Ƿ�ɹ�
   }

	//�عؼ���k��Ӧ�Ĳ��������ҵ��׸����ÿ�Ͱ
   int probe4Free ( const K& k )
   { 
	   int r = hashCode ( k ) % M; //����ʼͰ�������෨ȷ��������
	   while ( ht[r] ) 
		   r = ( r + 1 ) % M; //�ز�������Ͱ��̽��ֱ���׸���Ͱ
	   return r; //Ϊ��֤��Ͱ�����ҵ���װ�����Ӽ�ɢ�б���Ҫ��������
   }

	//��ɢ���㷨������Ͱ���飬��֤װ�������ھ���������
   void rehash() 
   {
	   int old_capacity = M; 
	   Entry<K, V>** old_ht = ht;
	   M = minPrime( 2 * M); //�������ټӱ�
	   N = 0; 
	   ht = new Entry<K, V>*[M];
	   memset ( ht, 0, sizeof ( Entry<K, V>* ) * M ); //��Ͱ����
	   for ( int i = 0; i < old_capacity; i++ ) //ɨ��ԭͰ����
		   if ( old_ht[i] ) //���ǿ�Ͱ�еĴ�����һ
			   put ( old_ht[i]->key, old_ht[i]->value ); //�������µ�Ͱ����
	   delete old_ht; //�ͷ�ԭͰ���顪����������ԭ�ȴ�ŵĴ�������ת�ƣ���ֻ���ͷ�Ͱ���鱾��
   }

   int minPrime(int c)
   {
	   for (int i = _curIdx; i < _count; i++)
	   {
		   if (_primes[_curIdx] > c)
		   {
			   return _primes[_curIdx];
		   }
		   _curIdx++;
	   }
   }

	//�����ַ�����ѭ����λɢ���루cyclic shift hash code��
   size_t hashCode ( char s[] ) {
	   int h = 0; //ɢ����
	   for ( size_t n = strlen ( s ), i = 0; i < n; i++ ) //�������ң��������ÿһ�ַ�
	   { h = ( h << 5 ) | ( h >> 27 ); h += ( int ) s[i]; } //ɢ����ѭ������5λ�����ۼӵ�ǰ�ַ�
	   return ( size_t ) h; //������õ�ɢ���룬ʵ���Ͽ����Ϊ���Ƶġ�����ʽɢ���롱
   } //����Ӣ�ﵥ�ʣ�"ѭ������5λ"��ʵ��ͳ�Ƶó������ֵ

public:
   Hashtable ( int c = 5 ):_count(82025),_curIdx(0) //����һ��������С��c��ɢ�б�Ϊ������ʱѡ�ý�С��Ĭ��ֵ��
   {
	   _primes = new int[_count];//�ܹ���ô����
	   FILE *fp = fopen(file);
	   int temp = 0, int idx = 0;
	   while(fscanf(fp, "%d", &temp)){
		   _primes[idx++] = temp;
	   }
	   fclose(fp);
		M = minPrime(c); //��С��c������M
		N = 0; ht = new Entry<K, V>*[M]; //����Ͱ���飨����˶�����ɹ�������ʼװ������ΪN/M = 0%
		memset ( ht, 0, sizeof ( Entry<K, V>* ) *M ); //��ʼ����Ͱ
   }

   ~Hashtable() //�ͷ�Ͱ���鼰���и����ǿգ�Ԫ����ָ��Ĵ���
   {
		delete _primes; _primes = NULL;
		for ( int i = 0; i < M; i++ ) //��һ����Ͱ
		{   if ( ht[i] ) 
				delete ht[i]; //�ͷŷǿյ�Ͱ
		}
   }

   int size() const { return N; } // ��ǰ�Ĵ�����Ŀ

   bool put ( K, V )//���루��ֹ��ͬ�������ʿ���ʧ�ܣ�
   {
	   if ( ht[probe4Hit ( k ) ] ) 
		   return false; //��ͬԪ�ز����ظ�����
	   int r = probe4Free ( k ); //Ϊ�´����Ҹ���Ͱ��ֻҪװ�����ӿ��Ƶõ�����Ȼ�ɹ���
	   ht[r] = new Entry<K, V> ( k, v ); ++N; //���루ע�⣺����ɾ��������踴λ��
	   if ( N * 2 > M ) 
		   rehash(); //װ�����Ӹ���50%����ɢ��
	   return true;
   }

   V* get ( K k ) //��ȡ
   {
	   int r = probe4Hit ( k );
	   return ht[r] ? & ( ht[r]->value ) : NULL;
   }

   bool remove ( K k ) //ɾ��
   {
	   int r = probe4Hit ( k ); 
	   if ( !ht[r] ) 
		   return false; //��Ӧ����������ʱ���޷�ɾ��
	   delete ht[r];
	   ht[r] = NULL;
	   N--; 
	   return true;
   }
};


#endif

