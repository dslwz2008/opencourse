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
//template <typename K, typename V> struct Dictionary { //词典Dictionary模板类
//	virtual int size() const = 0; //当前词条总数
//	virtual bool put ( K, V ) = 0; //插入词条（禁止雷同词条时可能失败）
//	virtual V* get ( K k ) = 0; //读取词条
//	virtual bool remove ( K k ) = 0; //删除词条
//};
//
//template <typename K, typename V> struct Entry { //词条模板类
//	K key; V value; //关键码、数值
//	Entry ( K k = K(), V v = V() ) : key ( k ), value ( v ) {}; //默认构造函数
//	Entry ( Entry<K, V> const& e ) : key ( e.key ), value ( e.value ) {}; //基于克隆的构造函数
//	bool operator< ( Entry<K, V> const& e ) { return key <  e.key; }  //比较器：小于
//	bool operator> ( Entry<K, V> const& e ) { return key >  e.key; }  //比较器：大于
//	bool operator== ( Entry<K, V> const& e ) { return key == e.key; } //判等器：等于
//	bool operator!= ( Entry<K, V> const& e ) { return key != e.key; } //判等器：不等于
//};
//
//template <typename K, typename V>
//class Hashtable : public Dictionary<K, V> { //符合Dictionary接口的Hashtable模板类
//
//private:
//	Entry<K, V>** ht; //桶数组，存放词条指针
//	int M; //桶数组容量
//	int N; //词条数量
//	int *_primes;
//	int _curIdx;
//	const int _count;
//
//protected:
//	//沿关键码k对应的查找链，找到词条匹配的桶
//	int probe4Hit ( const K& k )
//	{
//		int r = hashCode ( k ) % M; //从起始桶（按除余法确定）出发
//		while (  ht[r] && strcmp( k, ht[r]->key )!=0 )
//			r = ( r + 1 ) % M; //沿查找链线性试探：跳过所有冲突的桶
//		return r; //调用者根据ht[r]是否为空，即可判断查找是否成功
//	}
//
//	//沿关键码k对应的查找链，找到首个可用空桶
//	int probe4Free ( const K& k )
//	{ 
//		int r = hashCode ( k ) % M; //从起始桶（按除余法确定）出发
//		while ( ht[r] ) 
//			r = ( r + 1 ) % M; //沿查找链逐桶试探，直到首个空桶
//		return r; //为保证空桶总能找到，装填因子及散列表长需要合理设置
//	}
//
//	//重散列算法：扩充桶数组，保证装填因子在警戒线以下
//	void rehash() 
//	{
//		int old_capacity = M; 
//		Entry<K, V>** old_ht = ht;
//		M = minPrime( 2 * M); //容量至少加倍
//		N = 0; 
//		ht = new Entry<K, V>*[M];
//		memset ( ht, 0, sizeof ( Entry<K, V>* ) * M ); //新桶数组
//		for ( int i = 0; i < old_capacity; i++ ) //扫描原桶数组
//			if ( old_ht[i] ) //将非空桶中的词条逐一
//				put ( old_ht[i]->key, old_ht[i]->value ); //插入至新的桶数组
//		delete old_ht; //释放原桶数组——由于其中原先存放的词条均已转移，故只需释放桶数组本身
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
//	//生成字符串的循环移位散列码（cyclic shift hash code）
//	size_t hashCode ( char s[] ) {
//		int h = 0; //散列码
//		for ( size_t n = strlen ( s ), i = 0; i < n; i++ ) //自左向右，逐个处理每一字符
//		{ h = ( h << 5 ) | ( h >> 27 ); h += ( int ) s[i]; } //散列码循环左移5位，再累加当前字符
//		return ( size_t ) h; //如此所得的散列码，实际上可理解为近似的“多项式散列码”
//	} //对于英语单词，"循环左移5位"是实验统计得出的最佳值
//
//public:
//	Hashtable ( int c = 5 ):_count(49098),_curIdx(0) //创建一个容量不小于c的散列表（为测试暂时选用较小的默认值）
//	{
//		//_primes = new int[_count];//总共这么多数
//		//FILE *fp = fopen("primes600000.txt", "r");
//		//int temp = 0, idx = 0;
//		//while(idx < 49098){
//		//	fscanf(fp, "%d", &temp);
//		//	_primes[idx++] = temp;
//		//}
//		//fclose(fp);
//		M = 599999*4;//minPrime(c); //不小于c的素数M
//		N = 0; ht = new Entry<K, V>*[M]; //开辟桶数组（还需核对申请成功），初始装填因子为N/M = 0%
//		memset ( ht, 0, sizeof ( Entry<K, V>* ) *M ); //初始化各桶
//	}
//
//	~Hashtable() //释放桶数组及其中各（非空）元素所指向的词条
//	{
//		//delete _primes; _primes = NULL;
//		for ( int i = 0; i < M; i++ ) //逐一检查各桶
//		{   
//			if ( ht[i] )
//			{
//				delete ht[i]; //释放非空的桶
//			}
//		}
//	}
//
//	int size() const { return N; } // 当前的词条数目
//
//	bool put ( K k, V v)//插入（禁止雷同词条，故可能失败）
//	{
//		if ( ht[probe4Hit ( k ) ] ) 
//			return false; //雷同元素不必重复插入
//		int r = probe4Free ( k ); //为新词条找个空桶（只要装填因子控制得当，必然成功）
//		ht[r] = new Entry<K, V> ( k, v ); ++N; //插入（注意：懒惰删除标记无需复位）
//		if ( N * 2 > M ) 
//			rehash(); //装填因子高于50%后重散列
//		return true;
//	}
//
//	V* get ( K k ) //读取
//	{
//		int r = probe4Hit ( k );
//		return ht[r] ? & ( ht[r]->value ) : NULL;
//	}
//
//	bool remove ( K k ) //删除
//	{
//		int r = probe4Hit ( k ); 
//		if ( !ht[r] ) 
//			return false; //对应词条不存在时，无法删除
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
//		if (!hashtable.put(data[i], 1))//雷同的话
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
