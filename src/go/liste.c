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

SList* listInit()
{
	SList* res = malloc(sizeof(SList));
	res->head = NULL;
	res->curr = NULL;
	return res;
}

void* listCurrent(SList* list)
{
	void* res = NULL;
	if(list->curr) res = list->curr->data;
	return res;
}

int listEmpty(SList* list)
{
	return list->head ? 0 : 1;
}

void listAdd(SList* list, void* elem)
{
	if(elem)
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
			while(listNext(list));
			list->curr->next = node;
		}
	}
}

void* listNext(SList* list)
{
	void* res = NULL;
	if(!listEmpty(list))
	{
		if(list->curr->next)
		{
			res = list->curr->next->data;
			list->curr = list->curr->next;
		}
	}
	return res;
}

void* listHead(SList* list)
{
	void* res = NULL;
	if(list->head)
	{
		list->curr = list->head;
		res = list->head->data;
	}
	return res;
}

void* listRemove(SList* list, int index)
{
	void* res = NULL;
	if(list)
	{
		listHead(list);
		if(!listEmpty(list))
		{
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
		}
	}
	return res;
}


void* listRemoveElement(SList* list, void* elem)
{
	void* res = NULL;

	if(!listEmpty(list))
	{
		SListNode* prev = NULL;
		SListNode* curr = NULL;
		listHead(list);

		int found = 0;

		do
		{
			prev = curr;
			curr = list->curr;
			if(listCurrent(list) == elem)
			{
				found = 1;

				if(curr == list->head)
				{
					list->head = list->head->next;
					list->curr = list->head;
				}
				else
				{
					prev->next = curr->next;
					list->curr = prev;
				}

				res = curr->data;
				printf("destruction %x\n", curr);
				free(curr);
			}
		}while(!found && listNext(list));
	}

	printf("FIN destruction \n");

	return res;
}

int listSize(SList* list)
{
	int res = 0;
	if(list)
	{
		listHead(list);
		++res;
		while(listNext(list)) ++res;
	}
	return res;
}

void listDisplay(SList* list)
{
	if(!listEmpty(list))
	{
		listHead(list);
		printf("%X", (unsigned int)(list->curr->data));
		while(listNext(list))
		{
			printf(" -> %X", (unsigned int)(list->curr->data));
		}
		printf("\n");
	}
	else
	{
		printf("%X est vide\n", (unsigned int)(list));
	}
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
		while(list1->curr->next) listNext(list1);
		list1->curr->next = list2->head;
	}
	return list1;
}

SList* listConcatUnique(SList* list1, SList* list2, int(*cmp)(void*, void*))
{
	if(!list1 || listEmpty(list1))
	{
		list1->head = list2->head;
		list1->curr = list2->curr;
	}
	else if(!list2 || listEmpty(list2))
	{
		return list1;
	}
	else
	{
		listHead(list2);
		do
		{
			int found = 0;
			listHead(list1);
			do
			{
				found = cmp(listCurrent(list1), listCurrent(list2));
			}while(!found && listNext(list1));

			if(!found)
			{
				listAdd(list1, listCurrent(list2));
			}
		}while(listNext(list2));
	}
	return list1;
}

void listDelete(SList* list)
{
	if(list)
	{
		while(!listEmpty(list))
		{
			listRemove(list,0);
		}
		free(list);
	}
}
