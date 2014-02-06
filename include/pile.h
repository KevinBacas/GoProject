#ifndef __PILE_H__
#define __PILE_H__

typedef struct StackNode SStackNode;
typedef struct Stack SStack;

void* getStackNodeData(SStackNode* _node);

SStack* initStack();

void pushStack(SStack* _stack, void* _elem);

void* popStack(SStack* _stack);

#endif // __PILE_H__
