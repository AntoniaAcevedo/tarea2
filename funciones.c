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
    size_t tot_car; //opcional.
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


// Busca productos por el nombre en un mapa de productos.
void Buscar_nom (char * n, Almacen * Global){
    Pair * aux_pair= searchMap(Global ->Productos,n);
    Producto * prod= (Producto*) return_value(aux_pair);

    if (aux_pair == NULL){
        printf("\nNo existe este tipo de producto");
        return;
    }
    else{
        printf("\n----Producto encontrado!----\n");
        printf("-----------------------------------------------------------------\n");
        printf("-->%-43s Marca: %9s |\n", prod -> Nom_prod, prod -> Marca);
        printf("Tipo: %-27s Stock:%4ld | Precio:%9ld |\n",prod -> Tipo, prod -> stock, prod -> precio);
        printf("                                                                |\n");
        printf("-----------------------------------------------------------------\n");
    }
}

//Mostrar Productos por Marca
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
        printf("Tipo: %-27s Stock:%4ld | Precio:%9ld |\n",prod->Tipo, prod->stock, prod->precio);
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

//Mostrar Productos por Tipo
void Buscar_tipo (char * t, Almacen * Global){

    Pair * aux_pair;
    List * rec_list;
    Producto * prod;


    aux_pair = searchMap(Global->Tipos, t);

    if (aux_pair == NULL){
        printf("\nNo existe este tipo de producto");
        return;
    }

    rec_list = (List *) return_value(aux_pair);
    prod= (Producto *) firstList(rec_list);

    if (prod == NULL){
        printf("\nNO queda");
        return; 
    }

    printf("\n----Productos del tipo %s----\n", t);
    printf("-----------------------------------------------------------------\n");

    while (prod != NULL){
        printf("-->%-61s|\n",  prod->Nom_prod);//imprime info producto
        printf("Marca: %-26s Stock:%4ld | Precio:%9ld |\n", prod->Marca, prod->stock, prod->precio);
        printf("                                                                |\n");
        prod = (Producto *) nextList(rec_list);
    }
    printf("-----------------------------------------------------------------\n");
    return; 
}

// Agrega un producto
// Si el producto es nuevo se crean los datos y se guardan en las estructuras correspondientes.
// Si el producto si existe se ignora la informacion y se agrega el stock.
void agregar_producto(Almacen * Global, char * Nom, char * Marc, 
                      char * Type, size_t Price, size_t Stock){
    Pair * prod_pair, * marc_pair, * tipo_pair;
    Producto * aux_prod;
    List * marc_list;
    List * tipo_list;
    
    prod_pair = (Pair  *) searchMap(Global->Productos, Nom);
    if (prod_pair == NULL)
    {
        aux_prod = create_product(Nom, Marc, Type, Price, Stock); 
        insertMap(Global->Productos, aux_prod->Nom_prod , aux_prod);
    }
    else
    {
        aux_prod = (Producto *) return_value(prod_pair);
        aux_prod->stock += Stock;
        return;
    }

    marc_pair = (Pair *) searchMap(Global->Marcas, Marc);
    if (marc_pair == NULL)
    {   
        marc_list = createList();
        pushBack(marc_list, aux_prod);
        insertMap(Global->Marcas, aux_prod->Marca, marc_list);
    }
    else
    {
        marc_list = (List *) return_value(marc_pair);
        pushBack(marc_list, aux_prod);
    }

    tipo_pair = (Pair *) searchMap(Global->Tipos, Type);
    if (tipo_pair == NULL)
    {
        tipo_list = createList();
        pushBack(tipo_list, aux_prod);
        insertMap(Global->Tipos, aux_prod->Tipo, tipo_list);
    }
    else
    {
        tipo_list = (List *) return_value(tipo_pair);
        pushBack(tipo_list, aux_prod);
    }
}

// Crea carrito de compra con nombre ingresado
Carrito * CrearCarrito(char * nCarrito){
    Carrito * aux=(Carrito *)malloc(sizeof(Carrito));
    if(aux == NULL) return 0;

    aux->tot_car=0;
    strcpy(aux->Nom_car,nCarrito);
    aux->Productos=create_stack();

    return aux;
}

// Agrega un producto al carrito indicado n veces, en caso de existir el producto y el carrito
void Agregar_a_carr(char * nprod , int cantAgre,char * car ,Almacen * gl){
    
    Producto * prod;//aux3
    Pair * aux_pair;//aux2
    Carrito * aux_car;//aux
    
    aux_pair = searchMap(gl->Productos,nprod);
    

    if(aux_pair == NULL){
        printf("\nNo existe El producto que deseas agregar = %s",nprod);
        return;
    }

    prod = (Producto *) return_value(aux_pair);
    aux_car = (Carrito * ) firstList(gl->Carritos);

    while (aux_car != NULL)
    {
        if(strcmp(car,aux_car->Nom_car) == 0){

            for (int i = 0 ; i<cantAgre ; i++)
            {
                Push(aux_car->Productos,prod);
                aux_car->tot_car ++;
            }
            printf("Producto agregado con exito ");
            return;
        }
        aux_car = (Carrito *) nextList(gl->Carritos);
    }
    if(aux_car == NULL){
        aux_car = CrearCarrito(car);
        for (int i = 0; i<cantAgre ; i++)
        {
            Push(aux_car->Productos,prod);
            aux_car->tot_car++;    
        }
        
        pushFront(gl->Carritos, aux_car);
        printf("\nSe ha creado un carrito nuevo!\n");
        printf("Producto agregado con exito\n");
    }
    return;     
}

// Muestra los nombres de los carritos junto a la cantidad de productos
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
            printf("Total De Productos = %u\n", (unsigned int) aux->tot_car);
            aux=nextList(gl->Carritos);
            printf("\n");
        }
        printf("------------------------------------------\n");
        printf("El total de carros existentes = %d",totCarros);
    }
} 

// Elimina ultimo producto ingresado en el carrito
void Elim_del_carr(char * nCar, Almacen * gl){
    Producto * prod;
    Carrito * car;
    char cmpr_prod[MAX];

    car = BuscarCarro(nCar,gl);

    

    if(car == NULL){
        printf("\nNo Se a encontado tu carro: %s",nCar);
        return;
    }
    if(car->tot_car==0){
        printf("\nTu Carro se encuentra Vacio");
    }
    else{
        
        prod = (Producto *) Top(car->Productos);
        strcpy(cmpr_prod, prod->Nom_prod);

        printf("centinela");
        while (strcmp(cmpr_prod, prod->Nom_prod) == 0)
        {
            Pop(car->Productos);
            car->tot_car--;
            prod = (Producto *) Top(car->Productos);
        }
        printf("\nEl ultimo producto ingresado fue eliminado con exito!");
    }
    return;
}

// Elimina un carrito de la  lista de carritos
void eliminar_carrito(Almacen * gl, Carrito * carr){
    Carrito * aux_car;

    aux_car = (Carrito *) firstList(gl->Carritos);
    while(aux_car !=  NULL)
    {
        if(aux_car == carr)
        {
            popCurrent(gl->Carritos);
            free(carr);
            return;
        }
        aux_car = (Carrito *) nextList(gl->Carritos);
    }

    return;
}

// concreta la compra del carrito leido
void concretar_compra(char * nom_carr, Almacen * gl){
    Producto * prod, * anterior;
    char cmpr_nom[MAX];
    Carrito * carr;
    size_t temp = 0;

    carr = BuscarCarro(nom_carr, gl);
    if (carr == NULL)
    {
        printf("\nSu carro no existe!");
        return;
    }

    printf("Su carrito es:\n");
    VoltearyMostrarCarro(carr);
    printf("Comprobando productos....\n");

    prod = (Producto *) Top (carr->Productos);
    anterior = prod;
    strcpy(cmpr_nom, prod->Nom_prod);

    while (prod != NULL){
        if (strcmp(cmpr_nom, prod->Nom_prod) == 0)
        {
            Pop(carr->Productos);
            prod = Top(carr->Productos);

            temp++;
            continue;
        }

        if (temp > anterior->stock)
        {
            printf("\nNo hay suficientes productos para concretar su compra!\n");
            printf("Se eliminara el carrito...\n");
            eliminar_carrito(gl, carr);
            return;
        }

        anterior->stock = anterior->stock - temp;
        temp = 0;
        strcpy(cmpr_nom, prod->Nom_prod);
        anterior = prod;
        Pop(carr->Productos);
        prod = Top(carr->Productos);
    }

    if (temp > anterior->stock)
    {
        printf("\nNo hay suficientes productos para concretar su compra!\n");
        printf("Se eliminara el carrito...\n");
        eliminar_carrito(gl, carr);
        return;
    }

    printf( "No se han detectado problemas,\n"
            "compra concretada y carrito eliminado!\n");
    
    eliminar_carrito(gl, carr);
    
    return;
}

// muestra los productos por orden dentro de una lista de carritos
void mostrarCarro(Stack * Carr){
    
    Producto * prod;
    
    printf("\n----Productos de Tu Carro ----\n");
    printf("-----------------------------------------------------------------\n");
    
    size_t precioTotal = 0;

    while(((Producto *) Top(Carr)) != NULL){

        prod = (Producto *) Top(Carr);
        precioTotal = precioTotal + prod->precio;

        printf("-->%-31s| Marca: %-20s |\n", prod->Nom_prod, prod->Marca);
        printf("Tipo:%-26s   | Precio:%20ld |\n", prod->Tipo, prod->precio);
        printf("                                                                 |\n");
        Pop(Carr);
    }

    printf("\n El precio total es : %u\n", (unsigned int) precioTotal);
    printf("-----------------------------------------------------------------\n");
    return; 
}

// entrega una copia invertida del stack, restaurando la version original
Stack * Voltear_Restaurar(Stack * orig){
    Stack * copy = create_stack();
    Stack * rev = create_stack();
    
    void * data = Top(orig);

    // Voltea la pila
    while(data != NULL){
        Push(copy, data);
        Push(rev, data);
        Pop(orig);
        data = Top(orig);
    }


    data = Top(copy);
    //Restaura pila  original
    while(data != NULL){
        Push(orig, data);
        Pop(copy);
        data = Top(copy);
    }

    free(copy);
    return rev;
}

// Voltea y muestra la informacion de un carrito
void VoltearyMostrarCarro(Carrito * car){
    Stack * aux_stack = create_stack();
    size_t copia_tot = car->tot_car;

    aux_stack = Voltear_Restaurar(car->Productos);
    mostrarCarro(aux_stack);
    return;
}

// Busca un carrito en la lista de carritos
Carrito * BuscarCarro(char * nCarrIn,Almacen * Global ){
    Carrito * aux= (Carrito *) firstList(Global->Carritos);

    while(aux != NULL){
        if(strcmp(nCarrIn,aux->Nom_car)==0){
            printf("%s",aux->Nom_car);
            return aux;
            break;
        }
        aux= (Carrito *) nextList(Global->Carritos);
    }
    return NULL;
}

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

// Crea producto e inicia variables correspondientes
Producto * create_product(char * Nom, char * Marc, char * Tipo, size_t costo, size_t stock){
    Producto * new_prod = (Producto *) malloc (sizeof(Producto));
    if (new_prod == NULL)
    {
        perror("No se pudo realizar reserva para  producto\n");
        exit(1);
    }

    strcpy(new_prod->Nom_prod, Nom);
    strcpy(new_prod->Marca, Marc);
    strcpy(new_prod->Tipo, Tipo);
    new_prod->precio = costo;
    new_prod->stock = stock;

    return new_prod;
}

// Importar archivo con formato
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

// Guarda memoria e inicializa un datodel tipo Almacen, retornandolo.
Almacen * create_Almacen(void){
    Almacen * new_alm = (Almacen *) malloc(sizeof(Almacen));
    if(new_alm ==  NULL)
    {
        perror("No se pudo guardar memoria para el almacen\n");
        exit(1);
    }

    new_alm->Carritos = createList();
    new_alm->Marcas = createMap(CAP_MT);
    new_alm->Productos = createMap(CAP_PROD);
    new_alm->Tipos = createMap(CAP_MT);

    new_alm->tot_car = 0;

    return new_alm;
}


// Se recorre hashmap de marcas por ser de menor tamanyo que el de productos.
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
