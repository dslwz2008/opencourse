//#include <cstdio>
//#include <cstdlib>
//#include <cstring>
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
//typedef int Rank; //秩
//#define DEFAULT_CAPACITY  100 //默认的初始容量（实际应用中可设置为更大）
//
////向量模板类
//template <typename T> class Vector { 
//protected:
//	Rank _size; int _capacity;  T* _elem; //规模、容量、数据区
//
//	//复制数组区间A[lo, hi)
//	void copyFrom ( T const* A, Rank lo, Rank hi )
//	{
//		_elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //分配空间，规模清零
//		while ( lo < hi ) //A[lo, hi)内的元素逐一
//			_elem[_size++] = A[lo++]; //复制至_elem[0, hi - lo)
//	}
//
//	//空间不足时扩容
//	void expand()
//	{
//		if ( _size < _capacity ) return; //尚未满员时，不必扩容
//		if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //不低于最小容量
//		T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //容量加倍
//		for ( int i = 0; i < _size; i++ )
//			_elem[i] = oldElem[i]; //复制原向量内容（T为基本类型，或已重载赋值操作符'='）
//		delete [] oldElem; //释放原空间
//	}
//
//public:
//	// 构造函数
//	//容量为c、规模为s、所有元素初始为v
//	Vector ( int c = DEFAULT_CAPACITY, int s = 0 )
//	{ _elem = new T[_capacity = c]; _size = s; } //s<=c
//
//	//数组整体复制
//	Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } 
//
//	//区间
//	Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } 
//
//	//向量整体复制
//	Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); }
//
//	//区间
//	Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } 
//
//	// 析构函数
//	~Vector() { delete [] _elem; } //释放内部空间
//
//	// 只读访问接口
//	Rank size() const { return _size; } //规模
//
//	bool empty() const { return !_size; } //判空
//
//
//	// 可写访问接口
//	T& operator[] ( Rank r ) const//重载下标操作符，可以类似于数组形式引用各元素
//	{
//		return _elem[r];
//	}
//
//	//重载赋值操作符，以便直接克隆向量
//	Vector<T> & operator= ( Vector<T> const& V)
//	{
//		if ( _elem ) delete [] _elem; //释放原有内容
//		copyFrom ( V._elem, 0, V.size() ); //整体复制
//		return *this; //返回当前对象的引用，以便链式赋值
//	}
//
//	//插入元素
//	Rank insert ( Rank r, T const& e )
//	{
//		//assert: 0 <= r <= size
//		expand(); //若有必要，扩容
//		for ( int i = _size; i > r; i-- )
//			_elem[i] = _elem[i-1]; //自后向前，后继元素顺次后移一个单元
//		_elem[r] = e; _size++; //置入新元素并更新容量
//		return r; //返回秩
//	}
//
//	//默认作为末元素插入
//	Rank insert ( T const& e ) { return insert ( _size, e ); } 
//
//}; //Vector
//
////ABCABCABC BCABCABCA
////AAAAAAAAA AAAAAAAAA
//
//void find_char(char *str, char c, Vector<int> &vec)
//{
//	char * pch;
//	pch=strchr(str,c);
//	while (pch!=NULL)
//	{
//		vec.insert(pch-str);
//		pch=strchr(pch+1,c);
//	}
//}
//#define MAXCOUNT 500001
//int main(){
//
//#ifndef _OJ_
//	freopen("input_cycle.txt", "r", stdin);
//	//freopen("output_lh.txt", "w", stdout);
//#endif
//
//	int m;
//	char s1[MAXCOUNT], s2[MAXCOUNT], s1trans[MAXCOUNT];
//	while(scanf("%s %s", &s1, &s2) != EOF)
//	{
//		if (strlen(s1) != strlen(s2))
//		{
//			printf("%s\n", "NO");
//			continue;
//		}
//		Vector<int> vec;
//		bool matched = false;
//		find_char(s1, s2[0], vec);
//		for (int i = 0; i < vec.size(); i++)
//		{
//			int split = vec[i];
//			int r1 = -1;
//			if (split == 0)
//			{
//				r1=strcmp(s1,s2);
//			}
//			else
//			{
//				int len = strlen(s1);
//				strncpy(s1trans, s1+split, len-split);
//				strncpy(s1trans+len-split, s1, split);
//				s1trans[len] = '\0';
//				r1=strcmp(s1trans,s2);
//			}
//			if (r1 != 0)
//			{
//				matched = false;
//			}
//			else
//			{
//				matched = true;
//				break;
//			}
//		}
//		if (matched)
//		{
//			printf("%s\n", "YES");
//		}
//		else
//		{
//			printf("%s\n", "NO");
//		}
//		getchar();		
//	}
//
//	//fclose(stdin);
//	//fclose(stdout);
//	return 0;
//}
