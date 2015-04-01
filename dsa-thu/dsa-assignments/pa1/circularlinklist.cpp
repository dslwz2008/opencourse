//////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>

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

int main()
{
	CLList* list = (CLList*)malloc(sizeof(CLList));
	list->start = NULL;
	int m = 3;
	Node *current=NULL;
	for ()
	{
		current = insertAfter(list, current, m, data);
	}
	printInverse();
        ///* start always points to the first node of the linked list.
        //   temp is used to point to the last node of the linked list.*/
        //node *start,*temp;
        //start = (node *)malloc(sizeof(node)); 
        //temp = start;
        //temp -> next = start;
        ///* Here in this code, we take the first node as a dummy node.
        //   The first node does not contain data, but it used because to avoid handling special cases
        //   in insert and delete functions.
        // */
        //printf("1. Insert\n");
        //printf("2. Delete\n");
        //printf("3. Print\n");
        //printf("4. Find\n");
        //while(1)
        //{
        //        int query;
        //        scanf("%d",&query);
        //        if(query==1)
        //        {
        //                int data;
        //                scanf("%d",&data);
        //                insert(start,data);
        //        }
        //        else if(query==2)
        //        {
        //                int data;
        //                scanf("%d",&data);
        //                delete(start,data);
        //        }
        //        else if(query==3)
        //        {
        //                printf("The list is ");
        //                print(start,start->next);
        //                printf("\n");
        //        }
        //        else if(query==4)
        //        {
        //                int data;
        //                scanf("%d",&data);
        //                int status = find(start,data);
        //                if(status)
        //                {
        //                        printf("Element Found\n");
        //                }
        //                else
        //                {
        //                        printf("Element Not Found\n");

        //                }
        //        }
        //}


}