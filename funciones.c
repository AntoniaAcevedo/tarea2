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
        printf("-->%-48s Marca: %s|\n", prod -> Nom_prod, prod -> Marca);
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

Carrito * CrearCarrito(char * nCarrito,int cant){
    Carrito * aux=(Carrito *)malloc(sizeof(Carrito));
    if(aux == NULL) return 0;

    aux->tot_car=cant;
    strcpy(aux->Nom_car,nCarrito);
    aux->Productos=create_stack();

    return aux;
}
void Agregar_a_carr(char * nprod , int cantAgre,char * car ,Almacen * gl){
    Pair * aux2=searchMap(gl->Productos,nprod);
    Producto * aux3=(Producto *) return_value(aux2);
    if(aux2 == NULL){
        printf("\nNo existe El producto que deseas agregar = %s",nprod);
        return;
    }
    Carrito * aux=(Carrito * )firstList(gl->Carritos);
    if(aux == NULL){
        aux=CrearCarrito(car,cantAgre);
        Push(aux->Productos,aux3);
        aux->tot_car=cantAgre;
        pushFront(gl->Carritos,aux);
        printf("Producto agregado con exito ");

    }
    else{
        while (aux != NULL)
        {
            if(strcmp(car,aux->Nom_car)==0){
                Push(aux->Productos,aux3);
                aux->tot_car++;
                printf("Producto agregado con exito ");

                return;
            }
            aux=(Carrito *)nextList(gl->Carritos);
        }
        if( aux == NULL){
            aux=CrearCarrito(car,cantAgre);
            Push(aux->Productos,aux3);
            aux->tot_car=cantAgre;
            pushFront(gl->Carritos,aux);
            printf("Producto agregado con exito ");
        }
    }
    return;     
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
            printf("Total De Productos = %zd\n",aux->tot_car);
            aux=nextList(gl->Carritos);
            printf("\n");
        }
        printf("------------------------------------------\n");
        printf("El total de carros existentes = %d",totCarros);
    }
} 
void Elim_del_carr(char * nCar, Almacen * gl){
    Carrito * car=BuscarCarro(nCar,gl);
    if(car == NULL){
        printf("No Se a encontado tu carro: %s",nCar);
        return;
    }
    if(car->tot_car==0){
        printf("Tu Carro se encuentra Vacio");
    }
    else{
        Pop(car->Productos);
        car->tot_car--;
        printf("Ultimo producto ingresado, eliminado con exito");
    }
        
}
void mostrarCarro(Stack * Carr){
    printf("----Productos de Tu Carro ----\n");
    printf("-----------------------------------------------------------------\n");
    int precioAux=0,precioTotal=0;
    while(Carr != NULL){
        Producto * aux=(Producto *)Top(Carr);
        printf("-->%-61s|\n",  aux->Nom_prod);//imprime info producto
        printf("Marca: %-26s Stock:%4ld | Precio:%9ld |\n",aux->Marca, aux->stock, aux->precio);
        printf("                                                                |\n");
        precioAux=aux->stock * aux->precio;
        Pop(Carr);
        precioTotal=precioTotal + precioAux;
    }
    printf("%d",precioTotal);
    printf("-----------------------------------------------------------------\n");
    return; 
}

void VoltearyMostrarCarro(Carrito * car){
    Stack * aux=create_stack();
    while (car != NULL){
        Producto * aux2=(Producto *)Top(car->Productos);
        Push(aux,aux2);
        Pop(car->Productos);
    }
    mostrarCarro(aux);
}

Carrito * BuscarCarro(char * nCarrIn,Almacen * Global ){\
    Carrito * aux=(Carrito *)firstList(Global->Carritos);
    while(aux != NULL){
        if(strcmp(nCarrIn,aux->Nom_car)==0){
            printf("%s",aux->Nom_car);
            return aux;
            break;
        }
        aux=nextList(Global->Carritos);
    }
    return NULL;
}
/*/funciones Carrito //
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
