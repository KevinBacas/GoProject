#include <stdlib.h>
#include <stdio.h>

#define DECL_NODE(type)\
	typedef struct node_##type{\
		type* data;\
		struct node_##type* next;\
	} node_##type;
	
#define DECL_IT(type)\
	typedef struct list_##type{\
		struct node_##type* head;\
		struct node_##type* curr;\
	} list_##type;

#define DECL_INIT_LIST(type)\
	void listInit(list_##type* _list)\
	{\
		_list->head = NULL;\
		_list->curr = NULL;\
	}

#define DECL_EMPTY(type)\
	int listEmpty(list_##type* _list)\
	{\
		return _list->head ? 0 : 1;\
	}

#define DECL_ADD_ELEM(type)\
	void listAdd(list_##type* _list, type* _elem)\
	{\
		node_##type* elem = malloc(sizeof(node_##type));\
		elem->data = _elem;\
		elem->next = NULL;\
\
		if(listEmpty(_list))\
		{\
			_list->head = elem;\
			_list->curr = elem;\
		}\
		else\
		{\
			while(_list->curr->next != NULL)\
			{\
				listNext(_list);\
			}\
			_list->curr->next = elem;\
		}\
		printf("added %X\n", (unsigned int)_elem);\
	}

#define DECL_NEXT_ELEM(type)\
	node_##type* listNext(list_##type* _list)\
	{\
		node_##type* res = NULL;\
		if(_list->curr->next)\
		{\
			res = _list->curr->next;\
			_list->curr = _list->curr->next;\
		}\
		return res;\
	}

#define DECL_LIST_HEAD(type)\
	node_##type* listHead(list_##type* _list)\
	{\
		_list->curr = _list->head;\
		return _list->curr;\
	}

#define DECL_LIST_DISPLAY(type)\
	void listDisplay(list_##type* _list)\
	{\
		listHead(_list);\
		printf("%X", (unsigned int)(_list->curr->data));\
		while(listNext(_list))\
		{\
			printf(" -> %X", (unsigned int)(_list->curr->data));\
		}\
		printf("\n");\
	}

#define DECL_LIST(type)\
	DECL_NODE(type)\
	DECL_IT(type)\
	DECL_INIT_LIST(type)\
	DECL_EMPTY(type)\
	DECL_NEXT_ELEM(type)\
	DECL_ADD_ELEM(type)\
	DECL_LIST_HEAD(type)\
	DECL_LIST_DISPLAY(type)

DECL_LIST(int)
