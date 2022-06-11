#include <stdio.h>
#include <stdlib.h>
#include "listlink.h"

/*局部函数原型*/
static void CopyToNode(Item item, Node *pnode);

/*接口函数*/
/*把链表设置为空*/
void InitializeList(List* plist) 
{
	*plist = NULL;
}

/*如果链表为空，返回ture*/
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

/*创建存储项的节点，并将其添加至plist指向的链表末尾（较慢的实现）*/
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

/*释放由malloc分配的内存*/
/*设置链表指针为NULL*/
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

/*局部函数定义 */
/*把一个项拷贝到节点中*/
static void CopyToNode(Item item, Node* pnode) 
{
	pnode->item = item;
}