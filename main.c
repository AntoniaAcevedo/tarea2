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
        char arch[MAX] = "";

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
                    scanf("%s", arch);
                    getchar();
                    //Buscar_nom (arch,info_almacen);
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
                    scanf("%s", arch);
                    getchar();
                    Buscar_marca (arch, info_almacen);
                    getchar();
                    break;
                }
                break;
            case 5:
                puts("Ingrese el producto que desea buscar");
                scanf("%100[^\n]", arch);
                getchar();

                puts("Producto a buscar es:");
                printf("%s\n\n", arch);

                Buscar_tipo(arch, info_almacen);
                getchar();

                break;
            case 6:
                puts("lol");
                getchar();
                break;
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