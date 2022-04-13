#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#define MAX 10

int main (void)
{
       // ¬.¬
    long selec;
    long selec2;


    printf("MENU RAWR XDDDDDDDDDDDDDDD/n/n");

    printf(
        "1. Importar productos/n"
        "2. Exportar productos/n"
        "3. Agregar productos/n"
        "4. Buscar producto por criterio/n"
        "5. Mostrar todos los productos/n"
        "6. Operaciones de carrito/n"
        "7. Salir del programa/n"

        "/nIngrese lo que desea hacer:/n"
    );

    scanf("%ld", &selec);
    
    while (1){
        switch (selec)
        {
            case 1:
            break;
            case 2:
            break;
            case 3:
            break;
            case 4:
            break;
            case 5:
            break;
            case 6:
            break;
            case 7:
                puts("Saliendo del programa...");
                getchar();
            break;

            default:
                printf("Valor ingresado no valido!/n");
                getchar();

        }
    }


    return  0;
}