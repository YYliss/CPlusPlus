/* queuqe.h --Queue的接口 */
#ifndef QUEUE_H_
#define QUEUE_H_
#include <stdbool.h>

//在这里插入Item类型的定义 例如
typedef int  Item;        //用于use_q.c
//或者typedef struct item{int gumption; int charisn}item

#define MAXQUEUE 10

typedef struct node
{
	Item item;
	struct node* next;
}Node;

typedef struct queue 
{
	Node* front;        /* 指向队列首项的指针 */
	Node* fear;			/* 指向队列尾项的指针 */
	int items;			/* 队列中的项数 */
}Queue;


/**
	操作：		初始化队列
	前置条件：	pq指向 一个队列
	后置条件：	队列被初始化为空
 */
void InitializeQueue(Queue* pq);

/**
 * 操作：		检查队列是否已满
 * 前置条件:	pa指向之前被初始化的队列
 * 后置条件:	如果队列已满则返回ture，否则返回false
 */
bool QueueIsFull(const Queue* pq);

/**
 * 操作：		检查队列是否为空
 * 前置条件：	pq指向之前被初始化的队列
 * 后置条件：	如果队列为空则返回ture，否则返回false
 */
bool QueueIsEmpty(const Queue* pq);

/*
 * 操作:		确定队列中的项数
 * 前置条件:	pq指向之前被初始化的队列
 * 后置条件		返回队列中的项数
 */
int QueueItemCount(const Queue* pq);

/*
 * 操作：		在队列末尾添加项
 * 前置条件：	pa指向之前被初始化的队列 item是要被添加在末尾的
 * 后置条件：	如果队列不为空，item将被插在队列末尾
 */
bool EnQueue(Item item, Queue *pq);

/*
* 操作：		从队列的开头删除项
* 前置条件：	pq指向之前被初始化的队列
* 后置条件：	如果队列不为空，队列首个item将被拷贝到
*				*pitem中并被删除，且函数返回ture
*				如果该 操作使得队列为空，则重置队列为空
*				如果队列在操作前为空，该函数返回false
*/
bool  DeQueue(Item* pitem, Queue* pq);

/*
* 操作:			清空队列
* 前置条件：	pq指向之前被初始化的队列
* 后置条件：	队列被清空
*/
void EmptyTheQueue(Queue* pq);


#endif // !QUEUE_H_
