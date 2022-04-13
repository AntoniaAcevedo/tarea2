#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "hashmap.h"
#include "list.h"
#include "pila.h"
#define MAX 50

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
    Stack * Productos; //aun no esta definida.
}Carrito;

//mostrarProductosTipo
void Buscar_tipo (char * Tipo, HashMap * Tipos){
    Pair * aux = searchMap(Tipos, Tipo);
    List * aux2;
    Producto * aux3;

    if (aux == NULL){
        printf("NO hay jaja (llego tarde señor)");
        return;
    }

    aux2 = (List *) aux -> value;
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

void agregar_producto(Almacen * Global, char * Nom, char * Marc, 
                      char * Type, size_t Price, size_t Stock){
    Pair * aux;
    Producto * aux_prod;
    List * aux_list;

    aux = searchMap(Global->Productos, Nom);
    if (aux == NULL)
    {
        aux_prod = create_product(Nom, Marc, Type, Price, Stock); 
        insertMap(Global->Productos, Nom, aux_prod);
    }
    else
    {
        aux_prod = (Producto *) aux->value;
        aux_prod->stock += Stock;
    }

    //
    aux = searchMap(Global->Marcas, Marc);
    if (aux == NULL)
    {   
        aux_list = createList();
        pushBack(aux_list, aux_prod);
        insertMap(Global->Marcas, Marc, aux_list);
    }
    else
    {
        aux_list = (List *) aux->value;
        pushBack(aux_list, aux_prod);
    }

    //
    aux = searchMap(Global->Tipos, Type);
    if (aux == NULL)
    {
        aux_list = createList();
        pushBack(aux_list, aux_prod);
        insertMap(Global->Tipos, Type, aux_prod);
    }
    else
    {
        aux_list = (List *) aux->value;
        pushBack(aux_list, aux_prod);
    }

    // Finalizado.
    return;
}

Producto * create_product(char * Nom, char * Marc, char * Tipo, size_t costo, size_t stock){
    Producto * new_prod = (Producto *) malloc (sizeof(Producto));
    // Comprobar reserva

    strcpy(new_prod->Nom_prod, Nom);
    strcpy(new_prod->Marca, Marc);
    strcpy(new_prod->Tipo, Tipo);
    new_prod->precio = costo;
    new_prod->stock = stock;

    return new_prod;
}

void importar_archivo(){
    // IDEA, pasar de argumento funcion que transforme la informacion al formato reuqerido.
    // Importar deberia funcionar para cualquier tarea xd

    // Importar solo se encarga de la lectura de las cadenas, 
    // la llamada a la funcion que guarda la informacion


    // Donde se guardara la informacion?
    // Se podra hacer que la misma funcion guarde la infromacion?
    // quiza pasarle dos funciones??
    //ekis. matenme 
}

void Agregar_a_carr(Carrito  * car, Producto * prod){
    //Comporbar existencia del carrito, comprobar repeticion en lista
    // para no volver a agregar un mismo item al carrito. 

    // Si no se encunentra se agrega, si se encuentra se suma al stock.
}