#include "liste.h"
#include "position.h"
#include "ensemblePosition.h"

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

void* listCurrent(SList* list)
{
	return list->curr;
}

int listEmpty(SList* list)
{
	return list->head ? 0 : 1;
}

void listAdd(SList* list, void* elem)
{
	SListNode* node = malloc(sizeof(SListNode));
	node->data = elem;
	node->next = NULL;

	if(listEmpty(list))
	{
		list->head = node;
		list->curr = node;
	}
	else
	{
		while(list->curr->next != NULL)
		{
			listNext(list);
		}
		list->curr->next = node;
	}
	printf("added %X\n", (unsigned int)elem);
}

SListNode* listNext(SList* list)
{
	SListNode* res = NULL;
	if(!listEmpty(list))
	{
		if(list->curr->next)
		{
			res = list->curr->next;
			list->curr = list->curr->next;
		}
	}
	return res;
}

SListNode* listHead(SList* list)
{
	list->curr = list->head;
	return list->curr;
}

void* listRemove(SList* list, int index)
{
	listHead(list);
	void* res = NULL;
	if(index == 0)
	{
		SListNode* to_delete = list->head;
		list->head = list->head->next;
		res = to_delete->data;
		free(to_delete);
	}

	int i = 1;
	while(listNext(list) && i != index-1) ++i;

	if( i == index-1)
	{
		// l'element existe
		SListNode* to_delete = list->curr->next;
		list->curr->next = list->curr->next->next;
		res = to_delete->data;
		free(to_delete);
	}
	return res;
}


void* listRemoveElement(SList* list, void* elem)
{
	listHead(list);
	void* res = NULL;

	SListNode* curr = NULL;
	SListNode* prev = NULL;
	if(!listEmpty(list))
	{
		while(listCurrent(list) != elem){
			prev = curr;
			curr = listCurrent(list);
			if(!listNext(list))
			{
				return res;
			}
		}

		if(curr == list->head)
		{
			list->head = curr->next;
		}
		else
		{
			prev->next = curr->next;
		}

		res = curr->data;
		free(curr);
	}

	return res;
}

void listDisplay(SList* list)
{
	listHead(list);
	printf("%X", (unsigned int)(list->curr->data));
	while(listNext(list))
	{
		printf(" -> %X", (unsigned int)(list->curr->data));
	}
	printf("\n");
}

int listFind(SList* list, void* elem)
{
	listHead(list);
	while(listCurrent(list) != elem)
	{
		if(!listNext(list))
		{
			return 0;
		}
	}
	return 1;
}

SList* listConcat(SList* list1, SList* list2)
{
	if(listEmpty(list1))
	{
		list1->head = list2->head;
		list1->curr = list2->curr;
	}
	else
	{
		while(list1->curr->next == NULL) listNext(list1);
		list1->curr->next = list2->head;
	}
	return list1;
}

SEnsemblePosition* listConcatUnique(SEnsemblePosition* list1, SEnsemblePosition* list2)
{
	while(listNext(list2) != NULL)
	{
		if(listMeme(list1 , listCurrent(list2)))
		{
			free(listRemove(list2, 1));
		}
		else
		{
			listAdd(list1,listCurrent(list2));
			free(listRemove(list2, 1));
			listConcatUnique(list1,list2);
		}

	}
	free(list2);
	return list1;
}

int listMeme(SEnsemblePosition* list, void* elem)
{
	listHead(list);
	while( positionsEgale((SPosition*)listCurrent(list),(SPosition*)elem)==1
			&& listCurrent(list) != NULL) listNext(list);
	if(listCurrent(list)==NULL) return 0;
	else return 1;
	return -1;
}

void listDelete(SList* list)
{
	while(list->curr != NULL)
	{
		listRemove(list,1);
	}
	free(list);
}
