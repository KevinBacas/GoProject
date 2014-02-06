#ifndef __FILE_H__
#define __FILE_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct node SNode;

typedef struct list SList;

void* getListNodeData(SNode* _node);

SList* listInit();

void* listCurrent(SList* list);

int listEmpty(SList* list);

void listAdd(SList* list, void* elem);

SNode* listNext(SList* list);

SNode* listHead(SList* list);

void* listRemove(SList* list, int index);

void listDisplay(SList* list);

int listFind(SList* list, void* elem);

SList* listConcat(SList* list1, SList* list2);

int listMeme(SList* list, void* elem);

SList* listConcatUnique(SList* list1, SList* list2);

void listDelete(SList* list);

#endif // __FILE_H__
