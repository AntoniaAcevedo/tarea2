#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#define MAX 10

int main (void)
{
    while (1){

       // ¬.¬
        long selec;
        long selec2;
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
                puts("Ingrese el nombre del archivo que desea importar");
                getchar();
            break;
            case 2:
                puts("lol");
                getchar();
            break;
            case 3:
                puts("lol");
                getchar();
            break;
            case 4:
                puts("lol");
                getchar();
            break;
            case 5:
                puts("lol");
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