//#include <stdio.h>
//#include <stdlib.h>
//#include <memory.h>
//#include <string.h>
//
////fast io
//const int SZ = 1<<20;
//struct fastio{
//	char inbuf[SZ];
//	char outbuf[SZ];
//	fastio(){
//		setvbuf(stdin,inbuf,_IOFBF,SZ);
//		setvbuf(stdout,outbuf,_IOFBF,SZ);
//	}
//}io;
//
//template <typename K, typename V> struct Dictionary { //�ʵ�Dictionaryģ����
//	virtual int size() const = 0; //��ǰ��������
//	virtual bool put ( K, V ) = 0; //�����������ֹ��ͬ����ʱ����ʧ�ܣ�
//	virtual V* get ( K k ) = 0; //��ȡ����
//	virtual bool remove ( K k ) = 0; //ɾ������
//};
//
//template <typename K, typename V> struct Entry { //����ģ����
//	K key; V value; //�ؼ��롢��ֵ
//	Entry ( K k = K(), V v = V() ) : key ( k ), value ( v ) {}; //Ĭ�Ϲ��캯��
//	Entry ( Entry<K, V> const& e ) : key ( e.key ), value ( e.value ) {}; //���ڿ�¡�Ĺ��캯��
//	bool operator< ( Entry<K, V> const& e ) { return key <  e.key; }  //�Ƚ�����С��
//	bool operator> ( Entry<K, V> const& e ) { return key >  e.key; }  //�Ƚ���������
//	bool operator== ( Entry<K, V> const& e ) { return key == e.key; } //�е���������
//	bool operator!= ( Entry<K, V> const& e ) { return key != e.key; } //�е�����������
//};
//
//template <typename K, typename V>
//class Hashtable : public Dictionary<K, V> { //����Dictionary�ӿڵ�Hashtableģ����
//
//private:
//	Entry<K, V>** ht; //Ͱ���飬��Ŵ���ָ��
//	int M; //Ͱ��������
//	int N; //��������
//	int *_primes;
//	int _curIdx;
//	const int _count;
//
//protected:
//	//�عؼ���k��Ӧ�Ĳ��������ҵ�����ƥ���Ͱ
//	int probe4Hit ( const K& k )
//	{
//		int r = hashCode ( k ) % M; //����ʼͰ�������෨ȷ��������
//		while (  ht[r] && strcmp( k, ht[r]->key )!=0 )
//			r = ( r + 1 ) % M; //�ز�����������̽���������г�ͻ��Ͱ
//		return r; //�����߸���ht[r]�Ƿ�Ϊ�գ������жϲ����Ƿ�ɹ�
//	}
//
//	//�عؼ���k��Ӧ�Ĳ��������ҵ��׸����ÿ�Ͱ
//	int probe4Free ( const K& k )
//	{ 
//		int r = hashCode ( k ) % M; //����ʼͰ�������෨ȷ��������
//		while ( ht[r] ) 
//			r = ( r + 1 ) % M; //�ز�������Ͱ��̽��ֱ���׸���Ͱ
//		return r; //Ϊ��֤��Ͱ�����ҵ���װ�����Ӽ�ɢ�б���Ҫ��������
//	}
//
//	//��ɢ���㷨������Ͱ���飬��֤װ�������ھ���������
//	void rehash() 
//	{
//		int old_capacity = M; 
//		Entry<K, V>** old_ht = ht;
//		M = minPrime( 2 * M); //�������ټӱ�
//		N = 0; 
//		ht = new Entry<K, V>*[M];
//		memset ( ht, 0, sizeof ( Entry<K, V>* ) * M ); //��Ͱ����
//		for ( int i = 0; i < old_capacity; i++ ) //ɨ��ԭͰ����
//			if ( old_ht[i] ) //���ǿ�Ͱ�еĴ�����һ
//				put ( old_ht[i]->key, old_ht[i]->value ); //�������µ�Ͱ����
//		delete old_ht; //�ͷ�ԭͰ���顪����������ԭ�ȴ�ŵĴ�������ת�ƣ���ֻ���ͷ�Ͱ���鱾��
//	}
//
//	int minPrime(int c)
//	{
//		for (int i = _curIdx; i < _count; i++)
//		{
//			if (_primes[_curIdx] > c)
//			{
//				return _primes[_curIdx];
//			}
//			_curIdx++;
//		}
//	}
//
//	//�����ַ�����ѭ����λɢ���루cyclic shift hash code��
//	size_t hashCode ( char s[] ) {
//		int h = 0; //ɢ����
//		for ( size_t n = strlen ( s ), i = 0; i < n; i++ ) //�������ң��������ÿһ�ַ�
//		{ h = ( h << 5 ) | ( h >> 27 ); h += ( int ) s[i]; } //ɢ����ѭ������5λ�����ۼӵ�ǰ�ַ�
//		return ( size_t ) h; //������õ�ɢ���룬ʵ���Ͽ����Ϊ���Ƶġ�����ʽɢ���롱
//	} //����Ӣ�ﵥ�ʣ�"ѭ������5λ"��ʵ��ͳ�Ƶó������ֵ
//
//public:
//	Hashtable ( int c = 5 ):_count(49098),_curIdx(0) //����һ��������С��c��ɢ�б�Ϊ������ʱѡ�ý�С��Ĭ��ֵ��
//	{
//		//_primes = new int[_count];//�ܹ���ô����
//		//FILE *fp = fopen("primes600000.txt", "r");
//		//int temp = 0, idx = 0;
//		//while(idx < 49098){
//		//	fscanf(fp, "%d", &temp);
//		//	_primes[idx++] = temp;
//		//}
//		//fclose(fp);
//		M = 599999*4;//minPrime(c); //��С��c������M
//		N = 0; ht = new Entry<K, V>*[M]; //����Ͱ���飨����˶�����ɹ�������ʼװ������ΪN/M = 0%
//		memset ( ht, 0, sizeof ( Entry<K, V>* ) *M ); //��ʼ����Ͱ
//	}
//
//	~Hashtable() //�ͷ�Ͱ���鼰���и����ǿգ�Ԫ����ָ��Ĵ���
//	{
//		//delete _primes; _primes = NULL;
//		for ( int i = 0; i < M; i++ ) //��һ����Ͱ
//		{   
//			if ( ht[i] )
//			{
//				delete ht[i]; //�ͷŷǿյ�Ͱ
//			}
//		}
//	}
//
//	int size() const { return N; } // ��ǰ�Ĵ�����Ŀ
//
//	bool put ( K k, V v)//���루��ֹ��ͬ�������ʿ���ʧ�ܣ�
//	{
//		if ( ht[probe4Hit ( k ) ] ) 
//			return false; //��ͬԪ�ز����ظ�����
//		int r = probe4Free ( k ); //Ϊ�´����Ҹ���Ͱ��ֻҪװ�����ӿ��Ƶõ�����Ȼ�ɹ���
//		ht[r] = new Entry<K, V> ( k, v ); ++N; //���루ע�⣺����ɾ��������踴λ��
//		if ( N * 2 > M ) 
//			rehash(); //װ�����Ӹ���50%����ɢ��
//		return true;
//	}
//
//	V* get ( K k ) //��ȡ
//	{
//		int r = probe4Hit ( k );
//		return ht[r] ? & ( ht[r]->value ) : NULL;
//	}
//
//	bool remove ( K k ) //ɾ��
//	{
//		int r = probe4Hit ( k ); 
//		if ( !ht[r] ) 
//			return false; //��Ӧ����������ʱ���޷�ɾ��
//		delete ht[r];
//		ht[r] = NULL;
//		N--; 
//		return true;
//	}
//};
//
//
//int main(){
//#ifndef _OJ_
//	freopen("input_hashtable.txt", "r", stdin);
//	//freopen("output_lh.txt", "w", stdout);
//#endif
//	int n, len = 41, idx=0;
//	scanf("%d\r\n", &n);
//	char **data= new char*[n];
//	char *temp = NULL;
//	while (1)
//	{
//		temp = new char[len];
//		if(scanf("%s", temp) != EOF)
//		{
//			if (strlen(temp) != 0)
//			{
//				data[idx++] = temp;
//			}
//		}
//		else
//		{
//			break;
//		}
//	}
//
//	Hashtable<char *, int> hashtable;
//	for (int i = 0; i < n; i++)
//	{
//		if (!hashtable.put(data[i], 1))//��ͬ�Ļ�
//		{
//			int *v = hashtable.get(data[i]);
//			if (*v < 2)
//			{
//				(*v)++;
//				printf("%s\n", data[i]);
//			}
//		}
//	}
//
//
//	//fclose(stdin);
//	//fclose(stdout);
//	return 0;
//}
