#define MAX 50
#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "hashmap.h"
#include "list.h"

typedef struct Almacen{
    HashMap * Productos;
    HashMap * Marcas;
    HashMap * Tipos;
    List * Carritos;
    size_t tot_prod, tot_marc, tot_tipos, tot_car; //opcional.
}Almacen; 

typedef struct Producto{
    char Nom_prod [MAX];
    char Marca [MAX];
    char Tipo [MAX];
    size_t precio, stock;
}Producto;

typedef struct Carrito{
    char Nom_car [MAX];
    size_t tot_car;
    Pila * Productos; //aun no esta definida.
}Carrito;

//mostrarProductosTipo
void Buscar_tipo (char * Tipo, HashMap * Tipos){
    Pair * aux = searchMap(Tipos, Tipo);
    if (aux == NULL){
        printf("NO hay jaja (llego tarde señor)");
        return;
    }
    List * aux2 = (List *) aux -> value;
    Producto * aux3;
    aux3= (Producto *)firstList (aux2);
    if (aux3 == NULL){
        printf("NO queda");
        return; 
    }
    while ( aux3 != NULL){
        printf("SI hay jaja ");//imprime info producto
        aux3 = (Producto *) nextList(aux2);
    }
    return; //si no fuciona me pego un tiro porque no sabria hacer el resto.
}
