#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

typedef struct Stack{
    Nodo * top;
}Stack;

typedef struct nodo Nodo;

struct nodo{
    void * data;
    Nodo * next;
};

Nodo * create_node(void * data){
    Nodo * new_node = (Nodo *) malloc (sizeof(Nodo));
    //Comprobar reserva

    new_node->next = NULL;
    new_node->data = data;

    return new_node;
}

Stack * create_stack(void){
    Stack * new_s = (Stack *) malloc (sizeof(Stack));
    // Comprobar reserva

    new_s->top = NULL;
    return new_s;
}

void* Top(Stack* P){
    if (P->top == NULL) return NULL;
    else 
        return P->top->data;
}

void Pop(Stack* P){
    if (P->top == NULL) return;

    Nodo * aux_node = P->top;
    P->top = P->top->next;

    free(aux_node);
}

void Push(Stack* P, void * data){
    Nodo * new_node = create_node(data);
    new_node->next = P->top;
    P->top = new_node;
}
