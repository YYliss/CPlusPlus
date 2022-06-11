#include "queuelink.h"
#include <stdio.h>

static void CopyToNode(Item item, Node* pnode);
static void CopyToItem(Node* pq, Item pi);

void InitializeQueue(Queue* pq) 
{
	pq->front = pq->fear = NULL;
	pq->items = 0;
}

bool QueueIsFull(const Queue* pq)
{
	return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(const Queue* pq) 
{
	return pq->items == 0;
}

int QueueItemCount(const Queue* pq) 
{
	return pq->items;
}

bool EnQueue(Item item, Queue* pq) 
{
	Node* pnew;
	if (QueueIsFull(pq))
	{
		return false;
	}

	pnew = (Node*)malloc(sizeof(Node));
	if (pnew == NULL)
	{
		fprintf("Unable to allocate memory!",stderr);
		exit(1);
		return false;
	}

	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (QueueIsEmpty(pq))
	{
		pq->front = pnew;
	}
	else
	{
		pq->fear->next = pnew;
	}
	pq->fear = pnew;
	pq->items++;
	return true;
}

bool DeQueue(Item* pitem, Queue* pq) 
{
	Node* pt;
	if (QueueIsEmpty(pq))
	{
		return false;
	}
	CopyToItem(pq->front, pitem);
	pt = pq->front;
	pq->front = pq->front->next;
	free(pt);
	pq->items--;
	if (pq->items == 0)
	{
		pq->fear = NULL;
	}
	return true;
}

void EmptyTheQueue(Queue* pq) 
{
	Item dummy;
	while (!QueueIsEmpty(pq))
	{
		DeQueue(&dummy, pq);
	}
}

static void CopyToNode(Item item, Node* pnode) 
{
	pnode->item = item;
}

static void CopyToItem(Node* pn, Item * pi) 
{
	*pi = pn->item;
}