#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>
#define TSIZE  45

struct film {
	char title[TSIZE];
	int rating;
};

typedef struct film Item;

typedef struct node {
	Item item;
	struct node* next;
}Node;

typedef Node* List;

/* ����ԭ�� */

/*����:		    ��ʼ��һ������ */
/*ǰ������:		plistָ��һ������ */
/*��������:		�����ʼ��Ϊ�� */
void InitializeList(List* plist);

/*����:	        ȷ�������Ƿ�Ϊ�ն���*/
/*��������      �������Ϊ�ú�������true ���򷵻�false*/
bool ListIsEmpty(const List* plist);

/*������        ȷ�������е����� pListָ��һ���ѳ�ʼ��������*/
/*��������      �ú������������е�����*/
unsigned int ListItemCount(const List* plist);

/*����           �������е�ĩβ�콡��*/
/*ǰ������       item��һ����������������ҷ���ture�����򷵻�false*/
/*��������        ������ԣ��ú���������ĩβ���һ����ҷ���ture���򷵻�false*/
bool AddItem(Item item, List* plist);

/*������          �Ѻ��������������е�ÿ����*/
/*                plistָ��һ���ѳ�ʼ��������*/
/*                pfunc ָ��һ������*/			  
/*��������:       pfuncָ��ĺ��������������ÿһ��һ��*/
void Traverse(const List* plist, void(*pfunc)(Item item));

/*����:           �ͷ��ѷ�����ڴ棨����еĻ��� */
/*                plistָ��һ���ѳ�ʼ�������� */
/*��������        �ͷ���Ϊ�������������ڴ棬��������Ϊ�� */
void EmptyTheList(List* plist);


/*������          ȷ�������Ƿ����� */
/*����������      ����������� �ú�������true ���򷵻�false */
bool ListIsFull(const List* plist);

#endif