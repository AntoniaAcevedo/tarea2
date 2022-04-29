#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "list.h"
#include "hashmap.h"

typedef struct Almacen Almacen; 

typedef struct Producto Producto;

typedef struct Carrito Carrito;

void Buscar_nom (char * n, Almacen * Global);// FUNCIONAL

void Buscar_tipo (char * Tipo, Almacen * Global); // FUNCIONAL

void Buscar_marca (char * Marca, Almacen * Global);// FUNCIONAL

void Mostrar_pro (Almacen * Global); // FUNCIONAL

Producto * create_product(char * Nom, char * Marc, char * Tipo, size_t stock, size_t precio); //FUNCIONAL

const char *get_csv_field (char * tmp, int k); // FUNCIONAL

void importar_archivo(char * Nom_Arch, Almacen * gl); // FUNCIONAL
//funciones Carrito //
//void Agregar_a_carr(Carrito  * car, Producto * prod, Almacen * gl); // No fun 

//Carrito * BuscarCarrito(char * nCarrIn, Almacen * gl);//No

//void Elim_del_carr(Carrito * car); // MED Funcional

//void Mostrar_Lista_Carr(Almacen * gl); // MED Funcional

//void Concretar_Compra(); // No fun

//void Elim_Carrito(char * nCarrIn,info_almacen);// No fun

//void ActualizarStock(char * nCarrIn,info_almacen);// No fun
//////

void agregar_producto(Almacen * Global, char * Nom, char * Marc, 
                      char * Type, size_t Price, size_t Stock); // FUNCIONAL

Almacen * create_Almacen(void); // FUNCIONAL

void exportar_archivo(Almacen * Global, char * arch);


#endif // FUNCIONES_H_INCLUDED
