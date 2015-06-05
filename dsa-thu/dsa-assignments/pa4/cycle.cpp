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
//typedef int Rank; //��
//#define DEFAULT_CAPACITY  100 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����
//
////����ģ����
//template <typename T> class Vector { 
//protected:
//	Rank _size; int _capacity;  T* _elem; //��ģ��������������
//
//	//������������A[lo, hi)
//	void copyFrom ( T const* A, Rank lo, Rank hi )
//	{
//		_elem = new T[_capacity = 2 * ( hi - lo ) ]; _size = 0; //����ռ䣬��ģ����
//		while ( lo < hi ) //A[lo, hi)�ڵ�Ԫ����һ
//			_elem[_size++] = A[lo++]; //������_elem[0, hi - lo)
//	}
//
//	//�ռ䲻��ʱ����
//	void expand()
//	{
//		if ( _size < _capacity ) return; //��δ��Աʱ����������
//		if ( _capacity < DEFAULT_CAPACITY ) _capacity = DEFAULT_CAPACITY; //��������С����
//		T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //�����ӱ�
//		for ( int i = 0; i < _size; i++ )
//			_elem[i] = oldElem[i]; //����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='��
//		delete [] oldElem; //�ͷ�ԭ�ռ�
//	}
//
//public:
//	// ���캯��
//	//����Ϊc����ģΪs������Ԫ�س�ʼΪv
//	Vector ( int c = DEFAULT_CAPACITY, int s = 0 )
//	{ _elem = new T[_capacity = c]; _size = s; } //s<=c
//
//	//�������帴��
//	Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } 
//
//	//����
//	Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } 
//
//	//�������帴��
//	Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); }
//
//	//����
//	Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } 
//
//	// ��������
//	~Vector() { delete [] _elem; } //�ͷ��ڲ��ռ�
//
//	// ֻ�����ʽӿ�
//	Rank size() const { return _size; } //��ģ
//
//	bool empty() const { return !_size; } //�п�
//
//
//	// ��д���ʽӿ�
//	T& operator[] ( Rank r ) const//�����±������������������������ʽ���ø�Ԫ��
//	{
//		return _elem[r];
//	}
//
//	//���ظ�ֵ���������Ա�ֱ�ӿ�¡����
//	Vector<T> & operator= ( Vector<T> const& V)
//	{
//		if ( _elem ) delete [] _elem; //�ͷ�ԭ������
//		copyFrom ( V._elem, 0, V.size() ); //���帴��
//		return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
//	}
//
//	//����Ԫ��
//	Rank insert ( Rank r, T const& e )
//	{
//		//assert: 0 <= r <= size
//		expand(); //���б�Ҫ������
//		for ( int i = _size; i > r; i-- )
//			_elem[i] = _elem[i-1]; //�Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ
//		_elem[r] = e; _size++; //������Ԫ�ز���������
//		return r; //������
//	}
//
//	//Ĭ����ΪĩԪ�ز���
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
