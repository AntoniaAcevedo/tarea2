#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

enum selec{import = 1, export, add, search, display, cartop, end_program};
enum selec2{name = 1, tiype, brand};
enum car_selec{add_car = 1, delete_car, show_car, buy_car};

typedef struct Almacen Almacen; 

typedef struct Producto Producto;

typedef struct Carrito Carrito;

void Buscar_nom (char * n, Almacen * Global);

void Buscar_tipo (char * Tipo, Almacen * Global); 

void Buscar_marca (char * Marca, Almacen * Global);

void Mostrar_pro (Almacen * Global); 

Producto * create_product(char * Nom, char * Marc, char * Tipo, size_t stock, size_t precio); 

const char *get_csv_field (char * tmp, int k); 

void importar_archivo(char * Nom_Arch, Almacen * gl); 

Carrito * CrearCarrito(char * nCarrito);

void Agregar_a_carr(char *nprod , int cant,char * car, Almacen * gl);

void Mostrar_Lista_Carr(Almacen * gl); 

void VoltearyMostrarCarro(Carrito * car);

Carrito * BuscarCarro(char * nCarrIn ,Almacen * Global);

void Elim_del_carr(char * nCarrIn,Almacen * Global);

void agregar_producto(Almacen * Global, char * Nom, char * Marc, 
                      char * Type, size_t Price, size_t Stock); 

Almacen * create_Almacen(void); 

void exportar_archivo(Almacen * Global, char * arch);

void concretar_compra(char * nom_carr, Almacen * gl);


#endif // FUNCIONES_H_INCLUDED
