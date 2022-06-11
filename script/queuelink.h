/* queuqe.h --Queue�Ľӿ� */
#ifndef QUEUE_H_
#define QUEUE_H_
#include <stdbool.h>

//���������Item���͵Ķ��� ����
typedef int  Item;        //����use_q.c
//����typedef struct item{int gumption; int charisn}item

#define MAXQUEUE 10

typedef struct node
{
	Item item;
	struct node* next;
}Node;

typedef struct queue 
{
	Node* front;        /* ָ����������ָ�� */
	Node* fear;			/* ָ�����β���ָ�� */
	int items;			/* �����е����� */
}Queue;


/**
	������		��ʼ������
	ǰ��������	pqָ�� һ������
	����������	���б���ʼ��Ϊ��
 */
void InitializeQueue(Queue* pq);

/**
 * ������		�������Ƿ�����
 * ǰ������:	paָ��֮ǰ����ʼ���Ķ���
 * ��������:	������������򷵻�ture�����򷵻�false
 */
bool QueueIsFull(const Queue* pq);

/**
 * ������		�������Ƿ�Ϊ��
 * ǰ��������	pqָ��֮ǰ����ʼ���Ķ���
 * ����������	�������Ϊ���򷵻�ture�����򷵻�false
 */
bool QueueIsEmpty(const Queue* pq);

/*
 * ����:		ȷ�������е�����
 * ǰ������:	pqָ��֮ǰ����ʼ���Ķ���
 * ��������		���ض����е�����
 */
int QueueItemCount(const Queue* pq);

/*
 * ������		�ڶ���ĩβ�����
 * ǰ��������	paָ��֮ǰ����ʼ���Ķ��� item��Ҫ�������ĩβ��
 * ����������	������в�Ϊ�գ�item�������ڶ���ĩβ
 */
bool EnQueue(Item item, Queue *pq);

/*
* ������		�Ӷ��еĿ�ͷɾ����
* ǰ��������	pqָ��֮ǰ����ʼ���Ķ���
* ����������	������в�Ϊ�գ������׸�item����������
*				*pitem�в���ɾ�����Һ�������ture
*				����� ����ʹ�ö���Ϊ�գ������ö���Ϊ��
*				��������ڲ���ǰΪ�գ��ú�������false
*/
bool  DeQueue(Item* pitem, Queue* pq);

/*
* ����:			��ն���
* ǰ��������	pqָ��֮ǰ����ʼ���Ķ���
* ����������	���б����
*/
void EmptyTheQueue(Queue* pq);


#endif // !QUEUE_H_
