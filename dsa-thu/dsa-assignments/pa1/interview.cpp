#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef unsigned int uint;

typedef struct Node 
{
	int data;
	struct Node *prev;
	struct Node *next;
};

typedef struct CircularLinkList 
{
	struct Node *start;
	//struct Node *end;
} CLList;

Node* insertAfter(CLList* list, Node *cur, int m, int data)
{
	if (list->start == NULL)//列表为空
	{
		Node* nd = (Node *)malloc(sizeof(Node));
		nd->data = data;
		nd->prev = nd->next = nd;
		list->start = nd;
		return nd;
	}
	else
	{
		Node* nd = (Node *)malloc(sizeof(Node));
		nd->data = data;
		if (cur->next == cur)//只有一个节点
		{
			cur->next = cur->prev = nd;
			nd->next = nd->prev = cur;
		}
		else
		{
			nd->prev = cur; nd->next = cur->next;
			cur->next->prev = nd; cur->next = nd;
		}
		return nd;
	}
}

void print(CLList *list)
{
	Node * cur = list->start;
	do 
	{
		printf("%d ",cur->data);
		cur = cur->next;
	} while (cur != list->start);
}

void printInverse(CLList *list)
{
	Node * cur = list->start->prev;
	do 
	{
		printf("%d ",cur->data);
		cur = cur->prev;
	} while (cur != list->start);
}

int main(){
	#ifndef _OJ_
		freopen("input_interview.txt", "r", stdin);
		//freopen("output_team.txt", "w", stdout);
	#endif
	
	int n = 0,m = 0;
	scanf("%d %d", &n,&m);
	int *ids = new int[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &ids[i]);
	}




	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
