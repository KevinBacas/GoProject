#ifndef __FILE_H__
#define __FILE_H__

#include <stdlib.h>
#include <stdio.h>

//TODO : documentation
typedef struct node SListNode;

typedef struct list SList;

SList* listInit();

void* listCurrent(SList* list);

int listEmpty(SList* list);

void listAdd(SList* list, void* elem);

void* listNext(SList* list);

void* listHead(SList* list);

void* listRemove(SList* list, int index);

void* listRemoveElement(SList* list, void* elem);

void* listGetElement(SList* list, int index);

int listSize(SList* list);

void listDisplay(SList* list);

int listFind(SList* list, void* elem);

int listSearch(SList* list, void* elem, int(*cmp)(void*, void*));

SList* listConcat(SList* list1, SList* list2);

SList* listConcatUnique(SList* list1, SList* list2, int(*cmp)(void*, void*));

void listDelete(SList* list);

#endif // __FILE_H__
