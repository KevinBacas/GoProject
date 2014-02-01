#include <stdlib.h>

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
	void init_list(list_##type* _list)\
	{\
		_list->head = NULL;\
		_list->curr = NULL;\
	}

#define DECL_EMPTY(type)\
	int list_empty(list_##type _list)\
	{\
		return _list.head ? 0 : 1;\
	}

#define DECL_ADD_ELEM(type)\
	void list_add(list_##type _list, type* _elem)\
	{\
		node_##type* elem = malloc(sizeof(node_##type));\
		elem->data = _elem;\
		elem->next = NULL;\
\
		if(list_empty(_list))\
		{\
			_list.head = elem;\
			_list.curr = elem;\
		}\
		else\
		{\
			while(_list.curr != NULL)\
			{\
				list_next(_list);\
			}\
			_list.curr->next = elem;\
		}\
	}

#define DECL_NEXT_ELEM(type)\
	node_##type* list_next(list_##type _list)\
	{\
		node_##type* res = NULL;\
		if(_list.curr->next)\
		{\
			_list.curr = _list.curr->next;\
			res = _list.curr->next;\
		}\
		return res;\
	}

#define DECL_LIST_HEAD(type)\
	node_##type* list_head(list_##type* _list)\
	{\
		_list->curr = _list->head;\
		return _list->curr;\
	}

#define DECL_LIST(type)\
	DECL_NODE(type)\
	DECL_IT(type)\
	DECL_INIT_LIST(type)\
	DECL_EMPTY(type)\
	DECL_NEXT_ELEM(type)\
	DECL_ADD_ELEM(type)\
	DECL_LIST_HEAD(type)
