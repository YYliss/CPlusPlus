#include <stdio.h>
#include <stdlib.h>
#include "listlink.h"

/*�ֲ�����ԭ��*/
static void CopyToNode(Item item, Node *pnode);

/*�ӿں���*/
/*����������Ϊ��*/
void InitializeList(List* plist) 
{
	*plist = NULL;
}

/*�������Ϊ�գ�����ture*/
bool ListIsEmpty(const List* plist) 
{
	if (*plist == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ListIsFull(const List* plist) 
{
	Node* pt;
	bool full;
	pt = (Node*)malloc(sizeof(Node));
	if (pt == NULL)
	{
		full = false;
	}
	else
	{
		full = true;
	}
	return full;
}

unsigned int ListItemCount(const List* plist) 
{
	unsigned int count = 0;
	Node* pnode = *plist;
	while (pnode != NULL)
	{
		++count;
		pnode = pnode->next;
	}
	return count;
}

/*�����洢��Ľڵ㣬�����������plistָ�������ĩβ��������ʵ�֣�*/
bool AddItem(Item item, List* plist) 
{
	Node* pnew;
	Node* scan = *plist;
	pnew = (Node*)malloc(sizeof(Node));
	if (pnew == NULL)
	{
		return false;
	}
	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (scan = NULL)
	{
		*plist = pnew;
	}
	else
	{
		while (scan->next != NULL)
		{
			scan = scan->next;
		}
		scan->next = pnew;
	}
	return true;
}

void Traverse(const List* plist, void(*pfunc)(Item item)) 
{
	Node* pnode = *plist;
	while (pnode != NULL)
	{
		(*pfunc)(pnode->item);
		pnode = pnode->next;
	}
}

/*�ͷ���malloc������ڴ�*/
/*��������ָ��ΪNULL*/
void EmptyTheList(List* plist) 
{
	Node* pasve;
	while (*plist != NULL)
	{
		pasve = (*plist)->next;
		free(*plist);
		plist = pasve;
	}
}

/*�ֲ��������� */
/*��һ��������ڵ���*/
static void CopyToNode(Item item, Node* pnode) 
{
	pnode->item = item;
}