#include "pile.h"

#include <stdlib.h>

typedef struct StackNode {
	void* data;
	struct StackNode* prev;
	struct StackNode* next;
} SStackNode;

typedef struct Stack{
	int curr_index;
	SStackNode* head;
} SStack;

SStack* initStack()
{
	SStack* res = malloc(sizeof(SStack));
	res->head = NULL;
	return res;
}

void pushStack(SStack* _stack, void* _elem)
{
	SStackNode* node = malloc(sizeof(SStackNode));
	node->data = _elem;

	_stack->head = node;
}

void* popStack(SStack* _stack)
{
	void* res = _stack->head->data;
	SStackNode* to_delete = _stack->head;
	_stack->head = _stack->head->prev;
	free(to_delete);
	return res;
}
