#ifndef _HEAP_H
#define _HEAP_H

#pragma once

class Heap
{
public:
	Heap(int size = 0):_size(size)
	{
		elements = new int[_size];
	};
	Heap(int *elems, int size):_size(size)
	{
		elements = new int[_size];
		makeHeap(elems,_size);
	}
	~Heap()
	{
		delete []elements;
	};

	bool empty() const
	{ return _size ==0;}

	int size() const
	{ return _size; }

	int& top() const
	{
		return elements[0];
	}

	int& delintop()
	{
		int e = top();
		elements[0] = elements[--_size];
		keepHeapDown(0);
		return e;
	}

	void insert(const int &e)
	{
		elements[_size++] = e;
		keepHeapUp(_size-1);
	}

private:
	int _size;
	int *elements;
	void makeHeap(int *elems, int n);
	void keepHeapDown(int index);
	void keepHeapUp(int index);
};

template <typename int>
void Heap<int>::keepHeapDown(int index)
{
	int temp = elements[index];
	int j=index;
	while(2*j+1<=_size-1)
	{
		if(2*j+2<=_size-1)
		{
			if(elements[2*j+2]<elements[2*j+1])
				j = 2*j+2;
			else
				j = 2*j+1;
		}
		else
		{
			j = 2*j+1;
		}
		if(elements[j]<elements[index])
		{
			elements[index] = elements[j];
			index = j;
		}
		else
		{
			j = index;
			break;
		}
	}
	elements[j] = temp;
}
template <typename int>
void Heap<int>::keepHeapUp(int index)
{
	int temp = elements[index];
	int j=index;
	while(j>0 && (j-1)/2>=0)
	{
		if(elements[index]<elements[(j-1)/2])
		{
			elements[index] = elements[(j-1)/2];
			index = j = (j-1)/2;
		}
		else
			break;
	}
	elements[j] = temp;
}

template <typename int>
void Heap<int>::makeHeap(int *elems, int n)
{
	for(int i=0; i<n; ++i)
		elements[i] = elems[i];
	//int mid = n/2 - 1;
	for(int i=n/2 -1;i>=0;--i)
	{
		keepHeapDown(i);
		/*int temp = elements[i];
		int j=i;
		while(2*j+1<n-1)
		{
			if(2*j+2<n-1)
			{
				if(elements[2*j+2]<elements[2*j+1])
					j = 2*j+2;
				else
					j = 2*j+1;
			}
			else
			{
				j = 2*j+1;
			}
			if(elements[j]<temp)
			{
				elements[i] = elements[j];
				i = j;
			}
		}
		elements[j] = temp;*/
	}
}

#endif