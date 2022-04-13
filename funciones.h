#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "list.h"
#include "hashmap.h"

typedef struct Almacen Almacen; 

typedef struct Producto Producto;

typedef struct Carrito Carrito;

void Buscar_tipo (char * Tipo, HashMap * Global);

Producto * create_product(char * Nom, char * Marc, char * Tipo, size_t stock, size_t precio);


#endif // FUNCIONES_H_INCLUDED
