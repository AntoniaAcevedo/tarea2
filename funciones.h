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

Carrito * CrearCarrito(char * nCarrito,int cant);

void Agregar_a_carr(char *nprod , int cant,char * car, Almacen * gl);

void Mostrar_Lista_Carr(Almacen * gl); // MED Funcional
/*/funciones Carrito //
 // No fun 

//Carrito * BuscarCarrito(char * nCarrIn, Almacen * gl);//No

//void Elim_del_carr(Carrito * car); // MED Funcional



void Concretar_Compra(); // No fun

void Elim_Carrito(char nCarrIn , Almacen * gl);// No fun

void ActualizarStock(char * nCarrIn,Almacen * gl);// No fun
/////*/

void agregar_producto(Almacen * Global, char * Nom, char * Marc, 
                      char * Type, size_t Price, size_t Stock); // FUNCIONAL

Almacen * create_Almacen(void); // FUNCIONAL

void exportar_archivo(Almacen * Global, char * arch);


#endif // FUNCIONES_H_INCLUDED
