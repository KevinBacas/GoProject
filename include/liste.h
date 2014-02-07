#ifndef __FILE_H__
#define __FILE_H__

#include <stdlib.h>
#include <stdio.h>

//TODO : documentation
typedef struct node SListNode;

typedef struct list SList;

void* getListNodeData(SListNode* _node);

SList* listInit();

void* listCurrent(SList* list);

int listEmpty(SList* list);

void listAdd(SList* list, void* elem);

SListNode* listNext(SList* list);

SListNode* listHead(SList* list);

void* listRemove(SList* list, int index);

void* listRemoveElement(SList* list, void* elem);

void listDisplay(SList* list);

int listFind(SList* list, void* elem);

SList* listConcat(SList* list1, SList* list2);

int listMeme(SList* list, void* elem);

SList* listConcatUnique(SList* list1, SList* list2);

void listDelete(SList* list);

#endif // __FILE_H__
