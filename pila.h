#ifndef Pila_h
#define Pila_h

typedef struct nodo Nodo;

typedef struct Stack Stack;

Nodo * create_node(void * data);

Stack * create_stack(void);

void* Top(Stack* P);

void Pop(Stack* P);

void Push(Stack* P, void * data);

#endif /* Pila_h*/