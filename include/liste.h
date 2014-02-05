#ifndef __FILE_H__
#define __FILE_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct node SNode;

typedef struct list SList;

SList* listInit();

int listEmpty(SList* _list);

void listAdd(SList* _list, void* _elem);

SNode* listNext(SList* _list);

SNode* listHead(SList* _list);

void* listRemove(SList* _list, int _index);

void listDisplay(SList* _list);

#endif // __FILE_H__
