
#include <stdio.h>
#include<stdlib.h>

typedef struct list_elem{
	struct list_elem* next;
	struct list_elem* prev;
}ListElem;

typedef struct list_head{
	ListElem* head;
	ListElem* tail;
	int lenght;
}ListHead;

ListHead* List_init();//initialize the list
ListElem* pop(ListHead* list);//take the first elem in the list
ListElem* detach(ListHead* list, ListElem* elem);
int pushFront(ListHead* list, ListElem* elem);//insert a new elem at the head of the list
int pushBack(ListHead* list, ListElem* elem); //insert a new elem at the end of the list
int isEmpty(ListHead* list);