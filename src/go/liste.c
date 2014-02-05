#include "liste.h"

typedef struct node{
	void* data;
	struct node* next;
} SNode;

typedef struct list{
	struct node* head;
	struct node* curr;
} SList;

SList* listInit()
{
	SList* res = malloc(sizeof(SList));
	res->head = NULL;
	res->curr = NULL;
	return res;
}

int listEmpty(SList* _list)
{
	return _list->head ? 0 : 1;
}

void listAdd(SList* _list, void* _elem)
{
	SNode* elem = malloc(sizeof(SNode));
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

SNode* listNext(SList* _list)
{
	SNode* res = NULL;
	if(_list->curr->next)
	{
		res = _list->curr->next;
		_list->curr = _list->curr->next;
	}
	return res;
}

SNode* listHead(SList* _list)
{
	_list->curr = _list->head;
	return _list->curr;
}

void* listRemove(SList* _list, int _index)
{
	listHead(_list);
	void* res = NULL;
	if(_index = 0)
	{
		SNode* to_delete = _list->head;
		_list->head = _list->head->next;
		res = to_delete->data;
		free(to_delete);
	}

	int i = 0;
	while(listNext(_list) && i != _index-1);

	if( i == _index-1)
	{
		// l'élément existe
		SNode* to_delete = _list->curr->next;
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
