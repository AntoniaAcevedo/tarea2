#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#define MAX 100

int main (void)
{
    Almacen * info_almacen = create_Almacen();

    while (1){

       // ¬.¬
        long selec;
        long selec2;
        long selec3;
        long selec4;
        long selec5;
        
        char arch[MAX] = "";
        char nCarrIn[MAX]="";
        int cant;


        system("cls");
        printf("MENU RAWR XDDDDDDDDDDDDDDD\n\n");

        printf(
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
            case 1:
                system("cls");
                puts("Ingrese el nombre del archivo que desea importar");
                scanf("%s", arch);
                getchar();

                printf("Nombre de su archivo: %s\n\n", arch);

                importar_archivo(arch, info_almacen);
                getchar();
                break;
            case 2:
                system("cls");
                puts("Ingrese el nombre del archivo que desea exportar");
                scanf("%s", arch);
                getchar();

                printf("Nombre de su archivo: %s\n\n", arch);

                exportar_archivo(info_almacen, arch);
                getchar();
            break;
            case 3:
                puts("lol");
                getchar();
                break;
            case 4:                
                printf("1. Nombre Producto\n");
                printf("2. Tipo\n");
                printf("3. Marca\n");
                printf("Ingresa parametro de busqueda:  ");
                scanf("%ld",&selec2);
                getchar();
                switch(selec2){
                    case 1:
                    system("cls");
                    printf("Ingrese nombre: ");
                    scanf("%[^\n]", arch);
                    getchar();
                    Buscar_nom (arch, info_almacen);
                    getchar();
                    break;
                    ////
                    case 2:
                    system("cls");
                    printf("Ingrese tipo: ");
                    scanf("%s", arch);
                    getchar();
                    Buscar_tipo (arch,info_almacen);
                    getchar();
                    break;
                    ////
                    case 3:
                    system("cls");
                    printf("Ingrese marca: ");
                    scanf("%s", arch);
                    getchar();
                    Buscar_marca (arch, info_almacen);
                    getchar();
                    break;
                }
                break;
            case 5:
                system("cls");
                printf("Imprimiendo todos los productos\n\n");
                Mostrar_pro (info_almacen);
                getchar();
                break;
                //OPERACIONES CARRITO//
            case 6: 

                printf("1. Agregar a Carrito\n");
                printf("2. Eliminar del Carrito\n");
                printf("3. Muestrar Carritos\n");
                printf("4. Concretar Compra");
                printf("Indique Operacion:");

                scanf("%ld",&selec3);
                getchar();

                switch (selec3)
                {
                case 1:
                    system("cls");
                    printf("Ingrese el producto, la cantidad y el nombre del Carrito:\n");
                    printf("Ingrese nombre: ");
                    scanf("%[^\n]", arch);
                    getchar();
                    scanf("%d",cant);
                    getchar();
                    scanf("%[^\n]",nCarrIn);
                    getchar();
                    Agregar_a_carr(arch,cant,nCarrIn,info_almacen);
                    getchar();
                    Mostrar_Lista_Carr(info_almacen);
                    break;
                    /////
                case 2:
                    system("cls");
                    printf("Ingrese Nombre Del Carrito :");
                    scanf("%s", nCarrIn);
                    getchar();
                    Carrito * carr;
                    //carr=BuscarCarrito(nCarrIn,info_almacen);
                    //Elim_del_carr(carr);
                    


                    break;
                    /////
                case 3:
                    system("cls");
                    printf("Carros De Compra:");
                    Mostrar_Lista_Carr(info_almacen);
                    //consultar si agregar opcion de eliminar un carrito de la lista//

                    break;
                    /////
                    
                case 4:
                    system("cls");
                    printf("Ingrese Nombre Del Carrito A comprar :");
                    scanf("%s\n\n", nCarrIn);
                    getchar();
                    //mostrarCarrito(nCarrIn);//
                    printf("Desea Concretar Su compra :");
                    printf("1. SI");
                    printf("2. NO");

                    scanf("%ld", &selec4);
                    switch (selec4)
                    {
                    case 1:
                        //Concretar_Compra(nCarrIn,info_almacen);//
                        break;
                        //////
                    case 2:
                        printf("Desea Eliminar Su carro :");
                        printf("1. SI");
                        printf("2. NO");

                        scanf("%ld", &selec5);
                        switch (selec5)
                        {
                        case 1:
                            //Elim_Carrito(nCarrIn,info_almacen);//
                            break;
                            /////
                        case 2:
                            break;
                            /////
                        }
                        break;
                    }


                    break;
                }

            case 7:
                puts("Saliendo del programa...");
                getchar();
                return 0;
            break;

            default:
                printf("Valor ingresado no valido!\n");
                getchar();


        }
    }
}