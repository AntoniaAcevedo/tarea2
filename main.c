#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#define MAX 100

int main (void)
{
    Almacen * info_almacen = create_Almacen();

    while (1){

       // ¬.¬
        long selec, selec2;
        
        char arch[MAX], nom[MAX], marc[MAX], type[MAX];
        char nCarrIn[MAX]="";
        int cant;
        size_t size, stock; 
        Carrito * aux_car;

        system("cls");
        printf(
            "++ Almacen ++\n\n"

            "1. Importar productos\n"
            "2. Exportar productos\n"
            "3. Agregar productos\n"
            "4. Buscar producto por criterio\n"
            "5. Mostrar todos los productos\n"
            "6. Operaciones de carrito\n"
            "7. Salir del programa\n"

            "\nIngrese lo que desea hacer:\n"
        );

        scanf("%ld", &selec);
        getchar();

        switch (selec)
        {
            case import:
                system("cls");
                puts("Ingrese el nombre del archivo que desea importar");
                scanf("%s", arch);
                getchar();

                printf("Nombre de su archivo: %s\n\n", arch);

                importar_archivo(arch, info_almacen);
                getchar();
                break;

            case export:
                system("cls");
                puts("Ingrese el nombre del archivo que desea exportar");
                scanf("%s", arch);
                getchar();

                printf("Nombre de su archivo: %s\n\n", arch);

                exportar_archivo(info_almacen, arch);
                getchar();
                break;

            case add:
                system("cls");

                printf("Ingrese el nombre, marca y tipo del producto que \n"
                        "desea agregar, separados por un salto de linea (enter):\n");
                scanf("%[^\n] %[^\n] %[^\n]", nom, marc, type);
                getchar();

                printf("Ingrese la cantidad de producto que desea agregar y su\n"
                        "precio, separados por un salto de linea:\n");
                scanf("%u", &stock);
                getchar();
                scanf("%u", &size);
                getchar();

                agregar_producto(info_almacen, nom, marc, type, size, stock);
                printf("Producto agregado exitosamente!\n");

                getchar();
                break;

            case search:   
                system("cls");             
                printf( "1. Nombre Producto\n"
                        "2. Tipo\n"
                        "3. Marca\n\n"

                        "Ingresa parametro de busqueda:  ");
                

                scanf("%ld",&selec2);
                getchar();

                switch(selec2){
                    case name:
                        system("cls");
                        printf("Ingrese nombre: ");
                        scanf("%[^\n]", arch);
                        getchar();

                        Buscar_nom (arch, info_almacen);
                        getchar();
                        break;
                    
                    case tiype:
                        system("cls");
                        printf("Ingrese tipo: ");
                        scanf("%[^\n]", arch);
                        getchar();

                        Buscar_tipo (arch,info_almacen);
                        getchar();
                        break;
                    
                    case brand:
                        system("cls");
                        printf("Ingrese marca: ");
                        scanf("%[^\n]", arch);
                        getchar();

                        Buscar_marca (arch, info_almacen);
                        getchar();
                        break;
                    
                    default:
                        printf("\nOpcion no valida!");
                        getchar();
                        break;
                }
                break;

            case display:
                system("cls");
                printf("Imprimiendo todos los productos\n\n");
                
                Mostrar_pro (info_almacen);
                getchar();
                break;

            case cartop: 
                system("cls");
                printf( "1. Agregar a Carrito\n"
                        "2. Eliminar del Carrito\n"
                        "3. Muestrar Carritos\n"
                        "4. Concretar Compra\n\n"
                        
                        "Indique Operacion:    ");
                
                scanf("%ld",&selec2);
                getchar();
                
                switch (selec2)
                {
                case add_car:
                    system("cls");
                    printf("Ingrese el producto, la cantidad y el nombre del Carrito\n");

                    printf("\nIngrese nombre del producto:    \n");
                    scanf("%[^\n]", arch);
                    getchar();

                    printf("\nIngrese la cantidad de producto:    \n");
                    scanf("%u",&cant);
                    getchar();

                    printf("\nIngrese nombre de su carrito:     \n");
                    scanf("%[^\n]",nCarrIn);
                    getchar();

                    Agregar_a_carr(arch,cant,nCarrIn,info_almacen);
                    getchar();
                    break;
                    
                case delete_car:
                    system("cls");
                    printf("Ingrese Nombre Del Carrito :");
                    scanf("%[^\n]", nCarrIn);
                    getchar();

                    Elim_del_carr(nCarrIn ,info_almacen);

                    getchar();
                    break;
                    
                case show_car:
                    system("cls");
                    printf("Carros De Compra:\n\n");
                    Mostrar_Lista_Carr(info_almacen);
                    getchar();
                    //consultar si agregar opcion de eliminar un carrito de la lista//
                    break;
                
                case buy_car:
                    system("cls");
                    printf("Ingrese Nombre Del Carrito A comprar :");
                    scanf("%[^\n]", nCarrIn);
                    getchar();

                    concretar_compra(nCarrIn, info_almacen);
                    getchar();
                    break;
                }
                break;

            case end_program:
                puts("Saliendo del programa...");
                getchar();
                return 0;
                break;

            default:
                printf("Valor ingresado no valido!\n");
                getchar();
                break;
        }
    }
}