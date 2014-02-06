#include "liste.h"

typedef struct node{
	void* data;
	struct node* next;
} SListNode;

typedef struct list{
	struct node* head;
	struct node* curr;
} SList;

void* getListNodeData(SListNode* _node)
{
	return _node->data;
}

SList* listInit()
{
	SList* res = malloc(sizeof(SList));
	res->head = NULL;
	res->curr = NULL;
	return res;
}

void* listCurrent(SList* _list)
{
	return _list->curr;
}

int listEmpty(SList* _list)
{
	return _list->head ? 0 : 1;
}

void listAdd(SList* _list, void* _elem)
{
	SListNode* elem = malloc(sizeof(SListNode));
	elem->data = _elem;
	elem->next = NULL;

	if(listEmpty(_list))
	{
		_list->head = elem;
		_list->curr = elem;
	}
	else
	{
		while(_list->curr->next != NULL)
		{
			listNext(_list);
		}
		_list->curr->next = elem;
	}
	printf("added %X\n", (unsigned int)_elem);
}

SListNode* listNext(SList* _list)
{
	SListNode* res = NULL;
	if(_list->curr->next)
	{
		res = _list->curr->next;
		_list->curr = _list->curr->next;
	}
	return res;
}

SListNode* listHead(SList* _list)
{
	_list->curr = _list->head;
	return _list->curr;
}

void* listRemove(SList* _list, int _index)
{
	listHead(_list);
	void* res = NULL;
	if(_index == 0)
	{
		SListNode* to_delete = _list->head;
		_list->head = _list->head->next;
		res = to_delete->data;
		free(to_delete);
	}

	int i = 0;
	while(listNext(_list) && i != _index-1);

	if( i == _index-1)
	{
		// l'element existe
		SListNode* to_delete = _list->curr->next;
		_list->curr->next = _list->curr->next->next;
		res = to_delete->data;
		free(to_delete);
	}
	return res;
}

void listDisplay(SList* _list)
{
	listHead(_list);
	printf("%X", (unsigned int)(_list->curr->data));
	while(listNext(_list))
	{
		printf(" -> %X", (unsigned int)(_list->curr->data));
	}
	printf("\n");
}

SList* listConcat(SList* _list1, SList* _list2)
{
	if(listEmpty(_list1))
	{
		_list1->head = _list2->head;
		_list1->curr = _list2->curr;
	}
	else
	{
		while(_list1->curr->next == NULL) listNext(_list1);
		_list1->curr->next = _list2->head;
	}
	return _list1;
}

void listDelete(SList* _list)
{
	while(_list->curr != NULL)
	{
		listRemove(_list,1);
	}
	free(_list);
}
