#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"
#include "hashmap.h"
#include "list.h"
#include "pila.h"
#define MAX 300
#define CAP_PROD 300
#define CAP_MT 100

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

void Buscar_nom (char * n, Almacen * Global){
    Pair * aux= searchMap(Global ->Productos,n);
    Producto * aux2= (Producto*) return_value(aux);
    if (aux == NULL){
    printf("No existe este tipo de producto");
    return;
    }
    else{
        printf("----Productos del tipo %s----\n", n);
        printf("-----------------------------------------------------------------\n");
        printf("-->%-61s Marca: %s|\n", aux2 -> Nom_prod, aux2 -> Marca);//imprime info producto
        printf("Tipo: %-26s Stock:%4ld | Precio:%9ld |\n",aux2 -> Tipo, aux2 -> stock, aux2 -> precio);
        printf("                                                                |\n");
        printf("-----------------------------------------------------------------\n");
    }
}
//mostrarProductosMarca
void Buscar_marca (char * m, Almacen * Global){

    Pair * aux_pair;
    List * rec_list;
    Producto * prod;


    aux_pair = searchMap(Global->Marcas, m);

    if (aux_pair == NULL){
        printf("No existe este tipo de producto");
        return;
    }

    rec_list = (List *) return_value(aux_pair);
    prod= (Producto *)firstList (rec_list);

    if (prod == NULL){
        printf("NO queda");
        return; 
    }

    printf("----Productos de la marca %s----\n", m);

    printf("-----------------------------------------------------------------\n");

    while (prod != NULL){
        printf("-->%-61s|\n",  prod->Nom_prod);//imprime info producto
        printf("Tipo: %-26s Stock:%4ld | Precio:%9ld |\n",prod->Tipo, prod->stock, prod->precio);
        printf("                                                                |\n");
        prod = (Producto *) nextList(rec_list);
    }
    printf("-----------------------------------------------------------------\n");
    return; 
}
void Mostrar_pro (Almacen * Global){
    HashMap* aux= Global -> Productos;
    int cont= 0;
    if ( Global -> Productos == NULL){
        printf("NO hay productos");
        return;
    }
    else{
        Pair* aux3= firstMap(aux);
        printf("----Productos----\n");
        printf("-----------------------------------------------------------------\n");
        while ( aux3 != NULL){
            cont ++;
            Producto* aux2= (Producto*)return_value(aux3);
            printf("-->%-61s|\n", aux2->Nom_prod);//imprime info producto
            printf("Tipo: %-26s Stock:%4ld | Precio:%9ld  |\n",aux2->Tipo, aux2->stock, aux2->precio);
            printf("                                                                |\n");
            aux3= nextMap(aux);
        }
        printf("Son en total %d productos",cont);
    }

}
//mostrarProductosTipo
void Buscar_tipo (char * t, Almacen * Global){

    Pair * aux;
    List * aux2;
    Producto * aux3;


    aux = searchMap(Global->Tipos, t);

    if (aux == NULL){
        printf("No existe este tipo de producto");
        return;
    }

    aux2 = (List *) return_value(aux);
    aux3= (Producto *)firstList (aux2);

    if (aux3 == NULL){
        printf("NO queda");
        return; 
    }

    printf("----Productos del tipo %s----\n", t);
    printf("-----------------------------------------------------------------\n");

    while (aux3 != NULL){
        printf("-->%-61s|\n",  aux3->Nom_prod);//imprime info producto
        printf("Marca: %-26s Stock:%4ld | Precio:%9ld |\n",aux3->Marca, aux3->stock, aux3->precio);
        printf("                                                                |\n");
        aux3 = (Producto *) nextList(aux2);
    }
    printf("-----------------------------------------------------------------\n");
    return; 
}

void agregar_producto(Almacen * Global, char * Nom, char * Marc, 
                      char * Type, size_t Price, size_t Stock){
    Pair * aux, * aux2, * aux3;
    Producto * aux_prod;
    List * aux_list_mar;
    List * aux_list_tip;
    
    aux = (Pair  *) searchMap(Global->Productos, Nom);
    if (aux == NULL)
    {
        aux_prod = create_product(Nom, Marc, Type, Price, Stock); 
        insertMap(Global->Productos, aux_prod->Nom_prod , aux_prod);
    }
    else
    {
        aux_prod = (Producto *) return_value(aux);
        aux_prod->stock += Stock;
    }

    aux2 = (Pair *) searchMap(Global->Marcas, Marc);
    if (aux2 == NULL)
    {   
        aux_list_mar = createList();
        pushBack(aux_list_mar, aux_prod);
        insertMap(Global->Marcas, aux_prod->Marca, aux_list_mar);
    }
    else
    {
        aux_list_mar = (List *) return_value(aux2);
        pushBack(aux_list_mar, aux_prod);
    }

    aux3 = (Pair *) searchMap(Global->Tipos, Type);
    if (aux3 == NULL)
    {
        aux_list_tip = createList();
        pushBack(aux_list_tip, aux_prod);
        insertMap(Global->Tipos, aux_prod->Tipo, aux_list_tip);
    }
    else
    {
        aux_list_tip = (List *) return_value(aux3);
        pushBack(aux_list_tip, aux_prod);
    }
}
Carrito * crearCarrito(char * nCarrito){
    Carrito * aux=(Carrito *)malloc(sizeof(Carrito));
    if(aux == NULL){exit(1);}
    aux->tot_car=0;
    strcpy(aux->Nom_car,nCarrito);
    aux->Productos=create_stack();
    return aux;
}
void Agregar_a_carr(char * nprod , int cant,char * car ,Almacen * gl){// No fun
    Carrito * aux=(Carrito * )firstList(gl->Carritos);
    Pair * aux2=searchMap(gl->Productos,nprod);
    if(aux2 == NULL){
        printf("No Se Encontro tu Producto");
        return;
    }
    Producto * aux3=(Producto *) return_value(aux2);
    if(aux == NULL){
        aux=CrearCarrito();
        Push(aux->Productos,aux3);
        aux->tot_car++;
        pushFront(gl->Carritos,aux);

    }
    else{
        while (aux != NULL)
        {
            if(strcmp(car,aux->Nom_car)==0){
                Push(aux->Productos,aux3);
                aux->tot_car++;
                return;
            }
            aux=(Carrito *)nextList(gl->Carritos);
        }
        if( aux == NULL){
            aux=CrearCarrito();
            Push(aux->Productos,aux3);
            aux->tot_car++;
            pushFront(gl->Carritos,aux);
        }
    }     
}
void Mostrar_Lista_Carr(Almacen * gl){
    int totCarros=0;
    Carrito * aux=(Carrito * )firstList(gl->Carritos);
    if(aux == NULL){
        printf("No Hay carros existentes.");
    }
    else{
        while (aux != NULL)
        {
            totCarros++;
            printf("\"%s\"\n",aux->Nom_car);
            printf("Total De Productos = %zd",aux->tot_car);
            aux=nextList(gl->Carritos);
        }
        printf("El total de carros existentes = %d",totCarros);
    }
} 
/*/funciones Carrito //
Carrito * BuscarCarro(char nCarrIn,Almacen * Global ){

}


void Elim_del_carr(Carrito * car){
    if(car->tot_car==0){
        printf("Tu Carro se encuentra Vacio");
    }
    else{
        Pop(car->Productos);
        car->tot_car--;
    }
        
}



void Concretar_Compra(char nCarrIn){// No fun

} 

void Elim_Carrito(char nCarrIn , Almacen * Global){
    if(Global->Carritos == NULL){
        printf("No Hay carros existentes.");
    }
    else {
        int totCarros=0;
        Carrito * aux=(Carrito * )BuscarCarrito(nCarrIn,Global->Carritos);
        while (aux != NULL)
        {
            totCarros++;
            printf("\"%c\"\n");
            printf("Total De Productos = %zd",aux->tot_car);
            aux=nextList(Global->Carritos);
        }
        printf("El total de carros existentes = %d",totCarros);
    }
}

//void ActualizarStock(char nCarrIn,Almacen * Global){// No fun


///*/

const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (150*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {

        i = i-1;
       while(tmp[i]!=  '\0')
        {
            ret[i-ini_i] =  tmp[i];
            i++;
        }
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
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

void importar_archivo(char * Nom_Arch, Almacen * gl){
    FILE * entrada;
    char str[MAX];
    char a_nom[MAX], a_Mar[MAX], 
         a_tip[MAX], a_price[MAX], a_stock[MAX];


    entrada = fopen(Nom_Arch, "rt");
    if(entrada == NULL)
    {
        perror("No se pudo abrir el archivo de lectura");
        exit(1);
    }

    while(fscanf(entrada,"%[^\n]", str) != EOF)
    {
        for (int i = 0; i<5 ; i++){
            const char * aux = get_csv_field(str, i);

            switch (i)
            {
            case 0:
                strcpy(a_nom, aux);
                break;
            case 1:
                strcpy(a_Mar, aux);
                break;
            case 2:
                strcpy(a_tip, aux);
                break;
            case 3:
                strcpy(a_stock, aux);
                break;
            case 4:
                strcpy(a_price, aux);
                break;
            default:
                printf("Se produjo un error\n");
                exit(1);
                break;
            }
        }

        agregar_producto(gl, a_nom, a_Mar, a_tip, (size_t) atol(a_price), (size_t) atol(a_stock));
        getc(entrada);
    }

    fclose(entrada);
    return;
}

Almacen * create_Almacen(void){
    Almacen * new_alm = (Almacen *) malloc(sizeof(Almacen));
    // Comprobar reserva

    new_alm->Carritos = createList();
    new_alm->Marcas = createMap(CAP_MT);
    new_alm->Productos = createMap(CAP_PROD);
    new_alm->Tipos = createMap(CAP_MT);

    new_alm->tot_car = 0;
    new_alm->tot_marc = 0;
    new_alm->tot_prod = 0;
    new_alm->tot_tipos = 0;

    return new_alm;
}


// Se recorre hashmapde marcas por ser de menor tamanyo que  el de productos.
void exportar_archivo(Almacen * Global, char * arch){
    FILE * salida;
    Pair  * rec_marc;
    List * lista;
    Producto * rec_list;

    salida = fopen(arch, "wt");
    if(salida == NULL)
    {
        perror("No se pudo abrir el archivo de salida");
        exit(1);
    }

    rec_marc = firstMap(Global->Marcas);
    while(rec_marc != NULL)
    {
        lista  = return_value(rec_marc);
        rec_list = (Producto *) firstList(lista);

        while (rec_list != NULL)
        {
            fprintf(salida, "%s,%s,%s,%ld,%ld\n", rec_list->Nom_prod, rec_list->Marca, 
                        rec_list->Tipo, rec_list->stock, rec_list->precio);
            rec_list = (Producto *) nextList(lista);
        } 
        rec_marc = nextMap(Global->Marcas);      
    }

    fclose(salida);

    return;
}
