#ifndef GRAPH_H
#define GRAPH_H

#include "Vector.h"
#include "Stack.h"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //����״̬
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //���ڱ�����������������

//ͼGraphģ����
template <typename Tv, typename Te> //�������͡�������
class Graph 
{
private:
	//���ж��㡢�ߵĸ�����Ϣ��λ
	void reset() {
		//���ж����
		for ( int i = 0; i < n; i++ ) { 
			status ( i ) = UNDISCOVERED; dTime ( i ) = fTime ( i ) = -1; //״̬��ʱ���ǩ
			parent ( i ) = -1; priority ( i ) = INT_MAX; //���ڱ������еģ����ڵ㣬���ȼ���
			//���бߵ�
			for ( int j = 0; j < n; j++ )
				if ( exists ( i, j ) ) 
					type ( i, j ) = UNDETERMINED; //����
		}
	}


	//�����������BFS�㷨��������ͨ��
	void BFS ( int v, int& clock )
	{ 
		//assert: 0 <= v < n
		Queue<int> Q; //���븨������
		status ( v ) = DISCOVERED; Q.enqueue ( v ); //��ʼ�����
		while ( !Q.empty() ) { //��Q���֮ǰ������
			int v = Q.dequeue(); dTime ( v ) = ++clock; //ȡ�����׶���v
			for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //ö��v�������ھ�u
				if ( UNDISCOVERED == status ( u ) ) { //��u��δ�����֣���
					status ( u ) = DISCOVERED; Q.enqueue ( u ); //���ָö���
					type ( v, u ) = TREE; parent ( u ) = v; //����������չ֧����
				} else { //��u�ѱ����֣����������ѷ�����ϣ���
					type ( v, u ) = CROSS; //��(v, u)�����ڿ��
				}
				status ( v ) = VISITED; //���ˣ���ǰ����������
		}
	}

	//�����������DFS�㷨��������ͨ��
	void DFS ( int v, int& clock ) 
	{ 
		//assert: 0 <= v < n
		dTime ( v ) = ++clock; status ( v ) = DISCOVERED; //���ֵ�ǰ����v
		for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //ö��v�������ھ�u
			switch ( status ( u ) ) { //������״̬�ֱ���
			case UNDISCOVERED: //u��δ���֣���ζ��֧�������ڴ���չ
				type ( v, u ) = TREE; parent ( u ) = v; DFS ( u, clock ); break;
			case DISCOVERED: //u�ѱ����ֵ���δ������ϣ�Ӧ�������ָ�������
				type ( v, u ) = BACKWARD; break;
			default: //u�ѷ�����ϣ�VISITED������ͼ�������ӳ�Ϯ��ϵ��Ϊǰ��߻���
				type ( v, u ) = ( dTime ( v ) < dTime ( u ) ) ? FORWARD : CROSS; break;
		}
		status ( v ) = VISITED; fTime ( v ) = ++clock; //���ˣ���ǰ����v����������
	}


#define hca(x) (fTime(x)) //���ô˴����õ�fTime[]�䵱hca[]
	//�������͡�������
	void BCC ( int v, int& clock, Stack<int>& S ) { //assert: 0 <= v < n
		hca ( v ) = dTime ( v ) = ++clock; status ( v ) = DISCOVERED; S.push ( v ); //v�����ֲ���ջ
		for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //ö��v�������ھ�u
			switch ( status ( u ) ) { //����u��״̬�ֱ���
			case UNDISCOVERED:
				parent ( u ) = v; type ( v, u ) = TREE; BCC ( u, clock, S ); //�Ӷ���u������
				if ( hca ( u ) < dTime ( v ) ) //�������غ�������u��ͨ������ߣ���ָ��v��������
					hca ( v ) = min ( hca ( v ), hca ( u ) ); //��v������
				else { //������vΪ�ؽڵ㣨u���¼���һ��BCC�������ж����ʱ��������ջS�Ķ�����
					/*DSA*/printf ( "BCC rooted at %c:", vertex ( v ) );
					/*DSA*/Stack<int> temp; do { temp.push ( S.pop() ); print ( vertex ( temp.top() ) ); } while ( v != temp.top() ); while ( !temp.empty() ) S.push ( temp.pop() );
					while ( v != S.pop() ); //���ε�����ǰBCC�еĽڵ㣬��ɸ���ʵ������ת���������ṹ
					S.push ( v ); //���һ�����㣨�ؽڵ㣩������ջ�����ܼ���������
					/*DSA*/printf ( "\n" );
				}
				break;
			case DISCOVERED:
				type ( v, u ) = BACKWARD; //���(v, u)�������ա�ԽСԽ�ߡ���׼��
				if ( u != parent ( v ) ) hca ( v ) = min ( hca ( v ), dTime ( u ) ); //����hca[v]
				break;
			default: //VISITED (digraphs only)
				type ( v, u ) = ( dTime ( v ) < dTime ( u ) ) ? FORWARD : CROSS;
				break;
		}
		status ( v ) = VISITED; //��v�ķ��ʽ���
	}
#undef hca

	bool TSort ( int, int&, Stack<Tv>* ); //����ͨ�򣩻���DFS�����������㷨
	template <typename PU> void PFS ( int, PU ); //����ͨ�����ȼ��������

public:
	// ����
	int n; //��������
	virtual int insert ( Tv const& ) = 0; //���붥�㣬���ر��
	virtual Tv remove ( int ) = 0; //ɾ�����㼰������ߣ����ظö�����Ϣ
	virtual Tv& vertex ( int ) = 0; //����v�����ݣ��ö����ȷ���ڣ�
	virtual int inDegree ( int ) = 0; //����v����ȣ��ö����ȷ���ڣ�
	virtual int outDegree ( int ) = 0; //����v�ĳ��ȣ��ö����ȷ���ڣ�
	virtual int firstNbr ( int ) = 0; //����v���׸��ڽӶ���
	virtual int nextNbr ( int, int ) = 0; //����v�ģ�����ڶ���j�ģ���һ�ڽӶ���
	virtual VStatus& status ( int ) = 0; //����v��״̬
	virtual int& dTime ( int ) = 0; //����v��ʱ���ǩdTime
	virtual int& fTime ( int ) = 0; //����v��ʱ���ǩfTime
	virtual int& parent ( int ) = 0; //����v�ڱ������еĸ���
	virtual int& priority ( int ) = 0; //����v�ڱ������е����ȼ���

	// �ߣ�����Լ��������߾�ͳһת��Ϊ�������һ������ߣ��Ӷ�������ͼ��������ͼ������
	int e; //������
	virtual bool exists ( int, int ) = 0; //��(v, u)�Ƿ����
	virtual void insert ( Te const&, int, int, int ) = 0; //�ڶ���v��u֮�����Ȩ��Ϊw�ı�e
	virtual Te remove ( int, int ) = 0; //ɾ������v��u֮��ı�e�����ظñ���Ϣ
	virtual EType & type ( int, int ) = 0; //��(v, u)������
	virtual Te& edge ( int, int ) = 0; //��(v, u)�����ݣ��ñߵ�ȷ���ڣ�
	virtual int& weight ( int, int ) = 0; //��(v, u)��Ȩ��

	// �㷨
	//�����������BFS�㷨��ȫͼ��
	void bfs ( int s ) 
	{ 
		//assert: 0 <= s < n
		reset(); int clock = 0; int v = s; //��ʼ��
		do //��һ������ж���
		if ( UNDISCOVERED == status ( v ) ) //һ��������δ���ֵĶ���
			BFS ( v, clock ); //���Ӹö����������һ��BFS
		while ( s != ( v = ( ++v % n ) ) ); //����ż�飬�ʲ�©����
	}

	//�����������DFS�㷨��ȫͼ��
	void dfs ( int s ) 
	{ 
		//assert: 0 <= s < n
		reset(); int clock = 0; int v = s; //��ʼ��
		do //��һ������ж���
		if ( UNDISCOVERED == status ( v ) ) //һ��������δ���ֵĶ���
			DFS ( v, clock ); //���Ӹö����������һ��DFS
		while ( s != ( v = ( ++v % n ) ) ); //����ż�飬�ʲ�©����
	}
	
	void bcc ( int s ) { //����DFS��BCC�ֽ��㷨
		reset(); int clock = 0; int v = s; Stack<int> S; //ջS���Լ�¼�ѷ��ʵĶ���
		do
		if ( UNDISCOVERED == status ( v ) ) { //һ������δ���ֵĶ��㣨����ͨ������
			BCC ( v, clock, S ); //���Ӹö����������һ��BCC
			S.pop(); //�������غ󣬵���ջ�����һ�����㡪����ǰ��ͨ������
		}
		while ( s != ( v = ( ++v % n ) ) );
	}

	
	Stack<Tv>* tSort ( int ); //����DFS�����������㷨
	void prim ( int ); //��С֧����Prim�㷨
	void dijkstra ( int ); //���·��Dijkstra�㷨
	template <typename PU> void pfs ( int, PU ); //���ȼ��������
};


#endif