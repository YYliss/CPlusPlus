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

/* 函数原型 */

/*操作:		    初始化一个链表 */
/*前提条件:		plist指向一个链表 */
/*后置条件:		链表初始化为空 */
void InitializeList(List* plist);

/*操作:	        确定链表是否为空定义*/
/*后置条件      如果链表为该函数返回true 否则返回false*/
bool ListIsEmpty(const List* plist);

/*操作：        确定链表中的项数 pList指向一个已初始化的链表*/
/*后置条件      该函数返回链表中的项数*/
unsigned int ListItemCount(const List* plist);

/*操作           在链表中的末尾天健项*/
/*前置条件       item是一个待添加至链表的项，且返回ture；否则返回false*/
/*后置条件        如果可以，该函数在链表末尾添加一个项，且返回ture否则返回false*/
bool AddItem(Item item, List* plist);

/*操作：          把函数作用于链表中的每个项*/
/*                plist指向一个已初始化的链表*/
/*                pfunc 指向一个函数*/			  
/*后置条件:       pfunc指向的函数作用于链表的每一项一次*/
void Traverse(const List* plist, void(*pfunc)(Item item));

/*操作:           释放已分配的内存（如果有的话） */
/*                plist指向一个已初始化的链表 */
/*后置条件        释放了为链表分配的所有内存，链表设置为空 */
void EmptyTheList(List* plist);


/*操作：          确定链表是否已满 */
/*后置条件：      如果链表已满 该函数返回true 否则返回false */
bool ListIsFull(const List* plist);

#endif