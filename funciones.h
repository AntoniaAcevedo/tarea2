#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "list.h"
#include "hashmap.h"

typedef struct Almacen Almacen; 

typedef struct Producto Producto;

typedef struct Carrito Carrito;

<<<<<<< HEAD
void Buscar_tipo (char * Tipo, Almacen * Global); 

void Buscar_marca (char * Marca, Almacen * Global);

void Mostrar_pro (Almacen * Global);

Producto * create_product(char * Nom, char * Marc, char * Tipo, size_t stock, size_t precio); //FUNCIONAL

const char *get_csv_field (char * tmp, int k); // FUNCIONAL

void importar_archivo(char * Nom_Arch, Almacen * gl); // FUNCIONAL

void Agregar_a_carr(Carrito  * car, Producto * prod); // No se ha hecho lol

void agregar_producto(Almacen * Global, char * Nom, char * Marc, 
                      char * Type, size_t Price, size_t Stock); // FUNCIONAL

Almacen * create_Almacen(void); // FUNCIONAL

void exportar_archivo(Almacen * Global, char * arch);


#endif // FUNCIONES_H_INCLUDED
