#include <stdio.h>
#include <stdlib.h>
#include <time.h>


///Lista Doble Circular (Supermercado, Estanterias y Productos)......................................


struct NodoProducto{
    int Producto;
    struct NodoProducto *sig;
};
typedef struct NodoProducto NodoPro;

struct NodoCliente{
    int Cliente;
    int Productos;
    int Tipo;
    int Total;
    struct NodoCliente *sig;
};
typedef struct NodoCliente NodoCli;

struct NodoSuper{
    int Id;
    struct NodoSuper *sig;
    struct NodoSuper *ant;
    struct NodoProducto *primeroPro;
    struct NodoProducto *ultimoPro;
    struct NodoCliente *primeroCli;
    struct NodoCliente *ultimoCli;
};

typedef struct NodoSuper NodoSu;
NodoSu *primeroSu=NULL;
NodoSu *ultimoSu=NULL;


//gcc -o practica main.c
///------------------Declaracion de los Metodos-------------------------------------------------------
void Agregar_Lista_Carretera(int id, int carro);
void Mostrar_Lista_Carretera();
void Graficar_Lista_Carretera();
void Eliminar_Lista_Carretera();
void Agregar_Lista_Parqueo();
void Graficar_Lista_Parqueo();

void Carretera();
void Entrada_Carretera();
void Parqueo();
void Agregar_Carros(int cantidad);
void Agregar_Parqueos(int cantidad);
void Agregar_Cajeros(int cantidad);
void Graficar();

void Supermercado();
void Agregar_Estanterias(int cantidad);
void Agregar_Pila_Productos(int producto);
void Agregar_Productos(int cantidad);

void Agregar_Lista_Estanterias(int id);
void Graficar_Lista_Estanterias();

void Grafica_Carretera();
void Grafica_Parqueo();
void Grafica_Supermercado();
void Graficar_Cajeros();
void Graficar_Lista_Ventas();
void Graficar_Ventas_y_SubVentas();
void Graficar_SubLista_Ventas();
void Graficar_Matriz();

void Cajeros();
void Agregar_Lista_Cajeros(int id, int cajeros);
void Graficar_Lista_Cajeros();


///............Movimientos........................
void Simular();
void Mover_Carro_A_Parqueo(int carro);
void Mover_Carro_A_Entrada(int carro);
int Random_Parqueo(int carro);
void Agregar_Pila_Clientes_Estanterias(int random, int Cliente);
void Random_Estanterias(int Cliente);
void MoverSiguiente(int n);
void MOverAnterior(int n);
void Compras(int cliente,int producto,int cantidad);
int Comprar(NodoSu *estanteria);
void Pasar_A_Caja(int cliente);
void Insertar_En_Cola_De_Cajeros(int cliente,int tipo, int productos, int total);
void Agregar_Lista_Ventas(int cajero, int cliente, int tipo, int producto, int total);
void Agregar_SubLista_Ventas(int cajero, int cliente, int tipo, int producto, int total);
void Cobrar_En_Caja(int n);
void Crear_SubLista(int cajero);
void Matriz(int cantidad);
void Crear_Matriz(int n);
void Agregar_Venta_A_Matriz(int cajero, int cliente, int tipo, int producto, int total);
void Insertar_Recorrido_Filas(int cajero, int cliente, int tipo, int producto, int total);
void Insertar_Recorrido_Columna(int cajero, int cliente, int tipo, int producto, int total);
void Recorrdio_Filas();
void Recorrdio_Columnas();
void Graficar_Recorrido_Filas();
void Graficar_Recorrido_Columna();
void MapeoIJ(int i, int j);
void MapeoJI(int j, int i);



///--------------------------------Declaracion de Variables-------------------------------------------
FILE *gra;
int Cant_Parqueo=0;
int Cant_Estanterias=0;
int Cant_Cajeros=0;
int Cant_Ventas=0;
int Entrada=0;
int Contador_Random=0;

///-------------------------------( CARRETERA )-------------------------------------------------------

///Lista Simple de de la (Carretera)........................................................
struct nodoCarretera{
    int Id;
    int Carro;
    struct nodoCarretera *sig;
    struct nodoCarretera *ant;
};
typedef struct nodoCarretera NodoCa;
NodoCa *primeroCa;
NodoCa *ultimoCa;

///Agregar a la Lista Simple de la Carretera................................................
void Agregar_Lista_Carretera(int id, int carro){
    NodoCa *nuevo;
    nuevo=(NodoCa*)malloc(sizeof(struct nodoCarretera));
    nuevo->Id=id;
    nuevo->Carro=carro;
    nuevo->sig=NULL;
    nuevo->ant=NULL;

    if(primeroCa==NULL){
        nuevo->sig=NULL;
        nuevo->ant=NULL;
        primeroCa=nuevo;
        ultimoCa=nuevo;
    }else{
        nuevo->ant=NULL;
        nuevo->sig=primeroCa;
        primeroCa->ant=nuevo;
        primeroCa=nuevo;

    }

}

///Mostrar Lista Simple (Carretera)..........................................................
void Mostrar_Lista_Carretera(){
    printf("Motrar Carretera!\n");
    NodoCa *aux=primeroCa;
    while(aux!=NULL){
        printf("aux:%d \n",aux->Id);
        aux=aux->sig;
    }
}

///Eliminar Lista Simple (Carretera).......................................................
void Eliminar_Lista_Carretera(){
    if(primeroCa!=ultimoCa){
        ultimoCa->ant->sig=NULL;
        ultimoCa=ultimoCa->ant;
    }else{
        primeroCa=ultimoCa=NULL;

    }
}

///Opcion para definir la (Entrada) de la carretera........................................
void Entrada_Carretera(){
    int n;
    printf( "\n   Introduzca un Numero para la posicion de la Entrada...");
    scanf( "%d", &n );
    NodoCa *aux=primeroCa;
    while(aux!=NULL){
        if(aux->Id==n){
            Entrada=n;
            break;
        }
        aux=aux->sig;
    }

}


///Graficar Lista Simple de la Carretera...................................................
void Graficar_Lista_Carretera(){ ///Primera Grafica...(Todo)

       gra=fopen("Grafica.dot","wt");
       fputs("digraph g {\n ",gra);
       fputs("rankdir= \"LR\";\n",gra);
       fputs("node [\n" ,gra);
       fputs("fontsize = \"10\"\n",gra);
       fputs("shape = \"Mrecord\"\n",gra);
       fputs("color=\"darkslateblue\"\n",gra);
       fputs("style =\"filled, bold\"\n",gra);
       fputs("];\n",gra);

       if(primeroCa!=NULL){
       int a=0;
       NodoCa *aux=primeroCa;
       while(aux!=NULL){
           fputs("\"",gra);
           fputs("nodoCarretera",gra);
           fprintf(gra,"%d",a);
           fputs("\"",gra);
           fputs("\n[ ",gra);
           fprintf(gra, "label=\" " );
          if(aux->Carro==Entrada){
                fputs("ENTRADA",gra);
                fputs("\"];\n",gra);

           }else if(aux->Carro==0){
               fputs("ID: ",gra);
               fprintf(gra, "%d",aux->Id);
               fputs(" &#92;n ",gra);
               fputs("NULL ",gra);
               fputs("\"];\n",gra);
           }else{
               fputs("ID: ",gra);
               fprintf(gra, "%d",aux->Id);
               fputs(" &#92;n ",gra);
               fputs("Carro: ",gra);
               fprintf(gra, "%d",aux->Carro);
               fputs("\"];\n",gra);
           }
           a++;
           aux=aux->sig;

       }


       int b =0;
       int c =b+1;

       aux=primeroCa;
       while(aux->sig!=NULL){
           /// nodo1---->nodo2 siguintes
           fputs("\"nodoCarretera",gra);
           fprintf(gra,"%d",b);
           fputs("\"-> \"nodoCarretera",gra);
           fprintf(gra,"%d",c);
           fputs( "\";\n",gra);

               aux=aux->sig;
               b++;
               c++;
       }


    }else{
        ///La lista esta Vacia...

           fputs("\"",gra);
           fputs("nodoEntrada",gra);
           fputs("\"",gra);
           fputs("\n[ ",gra);
           fprintf(gra, "label=\" Entrada" );
           fputs("\"];\n",gra);


          printf("Lista de la Carretera esta vacia, esta Vacia...");


     }

        Graficar_Lista_Parqueo();
        Graficar_Lista_Estanterias();
        Graficar_Lista_Cajeros();
        Graficar_Lista_Ventas();
        Graficar_SubLista_Ventas();

    fputs("}",gra);


    fclose(gra);
    system("dot -Tpng Grafica.dot -o Grafica.png");
    system("kfmclient exec Grafica.png");

     Graficar_Matriz();

}

/// Grafica individual de la Carretera...........................................................
void Grafica_Carretera(){
       gra=fopen("Carretera.dot","wt");
       fputs("digraph g {\n ",gra);
       fputs("rankdir= \"LR\";\n",gra);
       fputs("node [\n" ,gra);
       fputs("fontsize = \"10\"\n",gra);
       fputs("shape = \"Mrecord\"\n",gra);
       fputs("color=\"darkslateblue\"\n",gra);
       fputs("style =\"filled, bold\"\n",gra);
       fputs("];\n",gra);

       if(primeroCa!=NULL){
       int a=0;
       NodoCa *aux=primeroCa;
       while(aux!=NULL){
           fputs("\"",gra);
           fputs("nodoCarretera",gra);
           fprintf(gra,"%d",a);
           fputs("\"",gra);
           fputs("\n[ ",gra);
           fprintf(gra, "label=\" " );
           if(aux->Carro==Entrada){
                fputs("ENTRADA",gra);
                fputs("\"];\n",gra);

           }else if(aux->Carro==0){
               fputs("ID: ",gra);
               fprintf(gra, "%d",aux->Id);
               fputs(" &#92;n ",gra);
               fputs("NULL ",gra);
               fputs("\"];\n",gra);
           }else{
               fputs("ID: ",gra);
               fprintf(gra, "%d",aux->Id);
               fputs(" &#92;n ",gra);
               fputs("Carro: ",gra);
               fprintf(gra, "%d",aux->Carro);
               fputs("\"];\n",gra);
           }
           a++;
           aux=aux->sig;

       }


       int b =0;
       int c =b+1;

       aux=primeroCa;
       while(aux->sig!=NULL){
           /// nodo1---->nodo2 siguintes
           fputs("\"nodoCarretera",gra);
           fprintf(gra,"%d",b);
           fputs("\"-> \"nodoCarretera",gra);
           fprintf(gra,"%d",c);
           fputs( "\";\n",gra);

               aux=aux->sig;
               b++;
               c++;
       }

    }else{
        ///La lista esta Vacia...

           fputs("\"",gra);
           fputs("nodoEntrada",gra);
           fputs("\"",gra);
           fputs("\n[ ",gra);
           fprintf(gra, "label=\" Entrada" );
           fputs("\"];\n",gra);


          printf("Lista de la Carretera esta vacia, esta Vacia...");


     }


    fputs("}",gra);

    fclose(gra);
    system("dot -Tpng Carretera.dot -o Carretera.png");
    system("kfmclient exec Carretera.png");

}

///-----------------------------( VARIOS )-----------------------------------------------------------

///Agregar una cantidad de carros a la Lista Simple de la (Carretera)...................
void Agregar_Carros(int cantidad){
    for(int x=1; x<= cantidad; x++){
        Agregar_Lista_Carretera(x,x);
    }
}

///Agregar la cantidad de espacion en el (Parqueo).......
void Agregar_Parqueos(int cantidad){
    for(int x=1; x<= cantidad; x++){
        Agregar_Lista_Parqueo(x,0);
    }
}



///Agregar la cantidad Cajeros(Cajeros)..............
void Agregar_Cajeros(int cantidad){
for(int x=1; x<= cantidad; x++){
        Agregar_Lista_Cajeros(x,x);
    }
}


///Graficar todo......................................................................
void Graficar(){
    Graficar_Lista_Carretera();
}

///---------------------------------( PARQUEO )---------------------------------------------------------

///Lista Simple Circular (Parqueo de los Carros)......................................
///
struct NodoParqueo{
    int Id;
    int Carro;
    struct NodoParqueo *sig;
};
typedef struct NodoParqueo NodoPa;
NodoPa *primeroPa;
NodoPa *ultimoPa;

///Agregar a la Lista Circular (Parqueo).........................................
void Agregar_Lista_Parqueo(int id, int carro){
    NodoPa *nuevo;
    nuevo = (NodoPa*)malloc(sizeof(struct NodoParqueo));
    nuevo->Id=id;
    nuevo->Carro=carro;
    nuevo->sig=NULL;

    if(primeroPa==NULL){
        nuevo->sig=NULL;
        primeroPa=nuevo;
        primeroPa->sig=primeroPa;
        ultimoPa=nuevo;
        Cant_Parqueo++;
    }else{
        ultimoPa->sig=nuevo;
        nuevo->sig=primeroPa;
        ultimoPa=nuevo;
        Cant_Parqueo++;
    }

}

///Graficar lista Circular (Parqueo).(Todo)...........................................
void Graficar_Lista_Parqueo(){

    if(primeroPa!=NULL){
        fputs("\n subgraph cluster_1 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=1;
        NodoPa *aux=primeroPa;
        for(int i=0; i<=Cant_Parqueo-1; i++){
          fputs("\"",gra);
          fputs("nodoPa",gra);
          fprintf(gra,"%d",a);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("ID: ",gra);
          fprintf(gra, "%d",a);
          if(aux->Carro!=0){
              fputs(" &#92;n ",gra);
              fputs("Carro: ",gra);
              fprintf(gra, "%d",aux->Carro);
              fputs("\"];\n",gra);
          }else{
              fputs(" &#92;n ",gra);
              fputs("Carro: NULL ",gra);

              fputs("\"];\n",gra);
          }
          a++;
              aux=aux->sig;
        }

        int b=1;
        int c=b+1;
        aux=primeroPa;
        int i=0;
        for(i=0; i<Cant_Parqueo-1; i++){
           /// nodo1---->nodo2
          fputs("\"nodoPa",gra);
          fprintf(gra,"%d",b);
          fputs("\"-> \"nodoPa",gra);
          fprintf(gra,"%d",c);
          fputs( "\";\n",gra);
              aux=aux->sig;
              b++;
              c++;
        }

        fputs("\"nodoPa",gra);
        fprintf(gra,"%d",i+1);
        fputs("\"-> \"nodoPa",gra);
        fprintf(gra,"%d",1);
        fputs( "\";\n",gra);

         fputs("fontsize = \"10\"\n",gra);
         fputs("shape = \"Mrecord\"\n",gra);
         fputs("color=\"orange\"\n",gra);
         fputs("style =\"filled, bold\"\n",gra);
         fputs("label =\"Parqueo\"\n",gra);
         fputs("}\n",gra);

    }else{
         fputs("\n subgraph cluster_1 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoPa",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("NULL ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"orange\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"Parqueo\"\n",gra);
          fputs("}\n",gra);

    }

}

///Grafica Individual del Parqueo...................................................................
void Grafica_Parqueo(){
       gra=fopen("Parqueo.dot","wt");
       fputs("digraph g {\n ",gra);
       fputs("rankdir= \"LR\";\n",gra);
       fputs("node [\n" ,gra);
       fputs("fontsize = \"10\"\n",gra);
       fputs("shape = \"Mrecord\"\n",gra);
       fputs("color=\"darkslateblue\"\n",gra);
       fputs("style =\"filled, bold\"\n",gra);
       fputs("];\n",gra);

    if(primeroPa!=NULL){
        fputs("\n subgraph cluster_1 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=1;
        NodoPa *aux=primeroPa;
        for(int i=0; i<=Cant_Parqueo-1; i++){
          fputs("\"",gra);
          fputs("nodoPa",gra);
          fprintf(gra,"%d",a);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("ID: ",gra);
          fprintf(gra, "%d",a);
          if(aux->Carro!=0){
              fputs(" &#92;n ",gra);
              fputs("Carro: ",gra);
              fprintf(gra, "%d",aux->Carro);
              fputs("\"];\n",gra);
          }else{
              fputs(" &#92;n ",gra);
              fputs("Carro: NULL ",gra);

              fputs("\"];\n",gra);
          }
          a++;
              aux=aux->sig;
        }

        int b=1;
        int c=b+1;
        aux=primeroPa;
        int i=0;
        for(i=0; i<Cant_Parqueo-1; i++){
           /// nodo1---->nodo2
          fputs("\"nodoPa",gra);
          fprintf(gra,"%d",b);
          fputs("\"-> \"nodoPa",gra);
          fprintf(gra,"%d",c);
          fputs( "\";\n",gra);
              aux=aux->sig;
              b++;
              c++;
        }

        fputs("\"nodoPa",gra);
        fprintf(gra,"%d",i+1);
        fputs("\"-> \"nodoPa",gra);
        fprintf(gra,"%d",1);
        fputs( "\";\n",gra);

         fputs("fontsize = \"10\"\n",gra);
         fputs("shape = \"Mrecord\"\n",gra);
         fputs("color=\"orange\"\n",gra);
         fputs("style =\"filled, bold\"\n",gra);
         fputs("label =\"Parqueo\"\n",gra);
         fputs("}\n",gra);

    }else{
         fputs("\n subgraph cluster_1 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoPa",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("NULL ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"orange\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"Parqueo\"\n",gra);
          fputs("}\n",gra);

    }

        fputs("}",gra);

    fclose(gra);
    system("dot -Tpng Parqueo.dot -o Parqueo.png");
    system("kfmclient exec Parqueo.png");

}


///-------------------( SUPERMERCADO, ESTANTERIAS Y PRODUCTOS )---------------------------------------
///Agregar a la Lista Doble Circular ( Estanterias ).........................................
void Agregar_Lista_Estanterias(int id){

    NodoSu *nuevo;
    nuevo = (NodoSu*)malloc(sizeof(struct NodoSuper));
    nuevo->Id=id;
    nuevo->sig=NULL;
    nuevo->ant=NULL;
    nuevo->primeroPro=NULL;
    nuevo->primeroCli=NULL;
    nuevo->ultimoPro=NULL;
    nuevo->ultimoCli=NULL;

    if(primeroSu==NULL){
        nuevo->sig=NULL;
        nuevo->ant=NULL;
        primeroSu=nuevo;
        primeroSu->sig=primeroSu;
        nuevo->ant=ultimoSu;
        ultimoSu=nuevo;
        Cant_Estanterias++;

    }else{
        ultimoSu->sig=nuevo;
        nuevo->sig=primeroSu;
        nuevo->ant=ultimoSu;
        ultimoSu=nuevo;
        primeroSu->ant=ultimoSu;
        Cant_Estanterias++;

    }

}

///Agregar a las Pilas de los Productos (Estanterias)..........................................
void Agregar_Pila_Productos(int producto){

    NodoSu *aux=primeroSu;

          for(int i=0; i<Cant_Estanterias; i++){
              for(int i=0; i<producto; i++){
                NodoPro *nuevo;
                nuevo = (NodoPro*)malloc(sizeof(struct NodoProducto));
                nuevo->Producto=aux->Id;
                nuevo->sig=NULL;

                if(aux->primeroPro==NULL){
                    nuevo->sig=NULL;
                    aux->primeroPro=nuevo;
                    aux->ultimoPro=nuevo;
                }else{
                    nuevo->sig=NULL;
                    aux->ultimoPro->sig=nuevo;
                    aux->ultimoPro=nuevo;

                }

            }
            aux=aux->sig;
        }

}

///Mover un Cliente (Sig-->)...........................................................................
void MoverSiguiente(int cliente){
    NodoSu *estanteria=primeroSu;
    for(int i=0; i<Cant_Estanterias; i++){
        if(estanteria->primeroCli!=NULL){
        if(estanteria->ultimoCli->Cliente==cliente){
            printf("\n Se movio un estante Sig-->\n");
            NodoCli *nuevo;
            nuevo = (NodoCli*)malloc(sizeof(struct NodoCliente));
            nuevo->Cliente=cliente;
            nuevo->Tipo=estanteria->ultimoCli->Tipo;
            nuevo->Productos=estanteria->ultimoCli->Productos;
            nuevo->Total=estanteria->ultimoCli->Total;
            nuevo->sig=NULL;

            if(estanteria->sig->primeroCli==NULL){
                nuevo->sig=NULL;
                estanteria->sig->primeroCli=nuevo;
                estanteria->sig->ultimoCli=nuevo;
            }else{
                nuevo->sig=NULL;
                estanteria->sig->ultimoCli->sig=nuevo;
                estanteria->sig->ultimoCli=nuevo;
            }

            if(estanteria->primeroCli==estanteria->ultimoCli){
                estanteria->primeroCli=NULL;
                estanteria->ultimoCli=NULL;
            }else{
                NodoCli *aux=estanteria->primeroCli;
                while(aux->sig!=estanteria->ultimoCli){
                    aux=aux->sig;
                }
                estanteria->ultimoCli=aux;
                estanteria->ultimoCli->sig=NULL;
            }



            break;

            }
        }

    estanteria=estanteria->sig;
    }

}

///Mover un Cliente (<--Ant).........................................................................
void MOverAnterior(int cliente){
    NodoSu *estanteria=ultimoSu;
    for(int i=0; i<Cant_Estanterias; i++){
        if(estanteria->primeroCli!=NULL){
        if(estanteria->ultimoCli->Cliente==cliente){

            printf("\n Se movio un estante <--Ant\n");
            NodoCli *nuevo;
            nuevo = (NodoCli*)malloc(sizeof(struct NodoCliente));
            nuevo->Cliente=cliente;
            nuevo->Tipo=estanteria->ultimoCli->Tipo;
            nuevo->Productos=estanteria->ultimoCli->Productos;
            nuevo->Total=estanteria->ultimoCli->Total;
            nuevo->sig=NULL;

            if(estanteria->ant->primeroCli==NULL){
                nuevo->sig=NULL;
                estanteria->ant->primeroCli=nuevo;
                estanteria->ant->ultimoCli=nuevo;
            }else{
                nuevo->sig=NULL;
                estanteria->ant->ultimoCli->sig=nuevo;
                estanteria->ant->ultimoCli=nuevo;
            }

            if(estanteria->primeroCli==estanteria->ultimoCli){
                estanteria->primeroCli=NULL;
                estanteria->ultimoCli=NULL;
            }else{
                NodoCli *aux=estanteria->primeroCli;
                while(aux->sig!=estanteria->ultimoCli){
                    aux=aux->sig;
                }
                estanteria->ultimoCli=aux;
                estanteria->ultimoCli->sig=NULL;
            }

            break;

            }
        }

    estanteria=estanteria->sig;
    }

}

int Comprar(NodoSu *estanteria){
    int estado=0;
    NodoPro *producto=estanteria->primeroPro;
    if(producto!=NULL){
        estado=1;
        if(estanteria->primeroPro==estanteria->ultimoPro){
            estanteria->primeroPro=NULL;
            estanteria->ultimoPro=NULL;
        }else{
            while(producto->sig!=estanteria->ultimoPro){
                producto=producto->sig;
            }
            estanteria->ultimoPro=producto;
            estanteria->ultimoPro->sig=NULL;
        }

        return 1;
    }else{
        return 0;
    }
}

void Compras(int cliente, int producto, int cantidad){
    int a=0;
    NodoSu *estanteria=ultimoSu;
    for(int i=0; i<Cant_Estanterias; i++){
        NodoCli *pila=estanteria->primeroCli;

        while(pila!=NULL){
            if(pila->Cliente==cliente && estanteria->Id==producto){
                ///Realizar la Compra...
                 for(int i=0; i<cantidad; i++){
                     a = Comprar(estanteria);
                     if(a==1){
                        pila->Productos++;
                        pila->Total=pila->Total+ (100*producto);
                     }
                 }

             }

        pila=pila->sig;
        }

    estanteria=estanteria->sig;
    }

    if(a==1){
        printf("\n --> Se Realizo la Compra Correctamente...");
    }else{
        printf("\n --> Error, Puede que se acabaran los productos...");
    }

}

///Agregar la cantidad en las Estanterias(Supermercado)..............
void Agregar_Estanterias(int cantidad){
    primeroSu=ultimoSu=NULL;
    for(int x=1; x<=cantidad; x++){

            Agregar_Lista_Estanterias(x);


        }

}


/// Graficar Lista Doble Circular( Estanterias ).(Todo)..............................................
void Graficar_Lista_Estanterias(){
         if(primeroSu!=NULL){
           fputs("\n subgraph cluster_2 {\n",gra);
           fputs("node [style=filled];\n",gra);

              int a=1;
              NodoSu *aux=primeroSu;
              for(int i=0; i<Cant_Estanterias; i++){
                  fputs("\"",gra);
                  fputs("nodoSu",gra);
                  fprintf(gra,"%d",a);
                  fputs("\"",gra);
                  fputs("\n[ ",gra);
                  fprintf(gra, "label=\" " );
                  fputs("ID: ",gra);
                  fprintf(gra, "%d",a);
                  fputs("\"];\n",gra);
                  a++;
                  int aa=0;
                  ///Crear nodos de las pilas(Productos)...
                  NodoPro *temp=aux->primeroPro;
                  if(temp!=NULL){
                  while(temp!=NULL){
                      fputs("\"",gra);
                      fputs("nodoPro",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",aa);
                      fputs("\"",gra);
                      fputs("\n[ ",gra);
                      fprintf(gra, "label=\" " );
                      fputs("Producto: ",gra);
                      fprintf(gra, "%d",aux->Id);
                      fputs("\"];\n",gra);
                      aa++;

                    temp=temp->sig;
                  }
                  }

                  ///Crear nodos de las pilas(Clientes)...
                  aa=0;
                  NodoCli *temp1=aux->primeroCli;
                  if(temp1!=NULL){
                  while(temp1!=NULL){
                      fputs("\"",gra);
                      fputs("nodoCli",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",aa);
                      fputs("\"",gra);
                      fputs("\n[ ",gra);
                      fprintf(gra, "label=\" " );
                      fputs("Cliente: ",gra);
                      fprintf(gra, "%d",temp1->Cliente);
                      fputs(" &#92;n ",gra);
                      fputs("Producto: ",gra);
                      fprintf(gra, "%d",temp1->Tipo);
                      fputs(" &#92;n ",gra);
                      fputs("Cantidad: ",gra);
                      fprintf(gra, "%d",temp1->Productos);
                      fputs(" &#92;n ",gra);
                      fputs("Total: ",gra);
                      fprintf(gra, "%d",temp1->Total);
                      fputs("\"];\n",gra);
                      aa++;

                    temp1=temp1->sig;
                  }
                  }


                      aux=aux->sig;
              }

              int b =1;
              int c =b+1;
              aux=primeroSu;
              int i=0;
              for(i=0; i<Cant_Estanterias; i++){
                  if(b<Cant_Estanterias){
                  // nodo1---->nodo2 siguintes
                  fputs("\"nodoSu",gra);
                  fprintf(gra,"%d",b);
                  fputs("\"-> \"nodoSu",gra);
                  fprintf(gra,"%d",c);
                  fputs( "\";\n",gra);

                  // nodo1<----nodo2 siguintes
                  fputs("\"nodoSu",gra);
                  fprintf(gra,"%d",c);
                  fputs("\"-> \"nodoSu",gra);
                  fprintf(gra,"%d",b);
                  fputs( "\";\n",gra);
                   }
                  int bb =0;
                  int cc =bb+1;

                  ///Crear nodos de las pilas(Productos)... nodoPro-->nodoPro
                  NodoPro *temp=aux->primeroPro;
                   if(temp!=NULL){
                      fputs("\"nodoSu",gra);
                      fprintf(gra,"%d",i+1);
                      fputs("\"-> \"nodoPro",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",0);
                      fputs( "\";\n",gra);
                  while(temp->sig!=NULL){
                      fputs("\"nodoPro",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",bb);
                      fputs("\"-> \"nodoPro",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",cc);
                      fputs( "\";\n",gra);

                      temp=temp->sig;
                      bb++;
                      cc++;
                  }
                  }

                  bb =0;
                  cc =bb+1;

                 NodoCli *actual=aux->primeroCli;
                 if(actual!=NULL){

                      fputs("\"nodoSu",gra);
                      fprintf(gra,"%d",i+1);
                      fputs("\"-> \"nodoCli",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",0);
                      fputs( "\";\n",gra);

                      while(actual->sig!=NULL){
                      fputs("\"nodoCli",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",bb);
                      fputs("\"-> \"nodoCli",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",cc);
                      fputs( "\";\n",gra);

                      actual=actual->sig;
                      bb++;
                      cc++;
                      }
                 }



                      aux=aux->sig;
                      b++;
                      c++;
              }
              fputs("\"nodoSu",gra);
              fprintf(gra,"%d",i);
              fputs("\"-> \"nodoSu",gra);
              fprintf(gra,"%d",1);
              fputs( "\";\n",gra);

              fputs("\"nodoSu",gra);
              fprintf(gra,"%d",1);
              fputs("\"-> \"nodoSu",gra);
              fprintf(gra,"%d",i);
              fputs( "\";\n",gra);


           fputs("fontsize = \"10\"\n",gra);
           fputs("shape = \"Mrecord\"\n",gra);
           fputs("color=\"LIMEGREEN\"\n",gra);
           fputs("style =\"filled, bold\"\n",gra);
           fputs("label =\"Supermercado\"\n",gra);
           fputs("}\n",gra);
         }else{
         fputs("\n subgraph cluster_2 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoSu",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("NULL ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"LIMEGREEN\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"Supermercado\"\n",gra);
          fputs("}\n",gra);

         }
}

///Graficar Supermercado por separado............................................................
void Grafica_Supermercado(){
       gra=fopen("Supermercado.dot","wt");
       fputs("digraph g {\n ",gra);
       fputs("rankdir= \"LR\";\n",gra);
       fputs("node [\n" ,gra);
       fputs("fontsize = \"10\"\n",gra);
       fputs("shape = \"Mrecord\"\n",gra);
       fputs("color=\"darkslateblue\"\n",gra);
       fputs("style =\"filled, bold\"\n",gra);
       fputs("];\n",gra);

       if(primeroSu!=NULL){
           fputs("\n subgraph cluster_2 {\n",gra);
           fputs("node [style=filled];\n",gra);

              int a=1;
              NodoSu *aux=primeroSu;
              for(int i=0; i<Cant_Estanterias; i++){
                  fputs("\"",gra);
                  fputs("nodoSu",gra);
                  fprintf(gra,"%d",a);
                  fputs("\"",gra);
                  fputs("\n[ ",gra);
                  fprintf(gra, "label=\" " );
                  fputs("ID: ",gra);
                  fprintf(gra, "%d",a);
                  fputs("\"];\n",gra);
                  a++;
                  int aa=0;
                  ///Crear nodos de las pilas(Productos)...
                  NodoPro *temp=aux->primeroPro;
                  if(temp!=NULL){
                  while(temp!=NULL){
                      fputs("\"",gra);
                      fputs("nodoPro",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",aa);
                      fputs("\"",gra);
                      fputs("\n[ ",gra);
                      fprintf(gra, "label=\" " );
                      fputs("Producto: ",gra);
                      fprintf(gra, "%d",aux->Id);
                      fputs("\"];\n",gra);
                      aa++;

                    temp=temp->sig;
                  }
                  }

                  ///Crear nodos de las pilas(Clientes)...
                  aa=0;
                  NodoCli *temp1=aux->primeroCli;
                  if(temp1!=NULL){
                  while(temp1!=NULL){
                      fputs("\"",gra);
                      fputs("nodoCli",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",aa);
                      fputs("\"",gra);
                      fputs("\n[ ",gra);
                      fprintf(gra, "label=\" " );
                      fputs("Cliente: ",gra);
                      fprintf(gra, "%d",temp1->Cliente);
                      fputs(" &#92;n ",gra);
                      fputs("Producto: ",gra);
                      fprintf(gra, "%d",temp1->Tipo);
                      fputs(" &#92;n ",gra);
                      fputs("Cantidad: ",gra);
                      fprintf(gra, "%d",temp1->Productos);
                      fputs(" &#92;n ",gra);
                      fputs("Total: ",gra);
                      fprintf(gra, "%d",temp1->Total);
                      fputs("\"];\n",gra);
                      aa++;

                    temp1=temp1->sig;
                  }
                  }


                      aux=aux->sig;
              }

              int b =1;
              int c =b+1;
              aux=primeroSu;
              int i=0;
              for(i=0; i<Cant_Estanterias; i++){
                  if(b<Cant_Estanterias){
                  // nodo1---->nodo2 siguintes
                  fputs("\"nodoSu",gra);
                  fprintf(gra,"%d",b);
                  fputs("\"-> \"nodoSu",gra);
                  fprintf(gra,"%d",c);
                  fputs( "\";\n",gra);

                  // nodo1<----nodo2 siguintes
                  fputs("\"nodoSu",gra);
                  fprintf(gra,"%d",c);
                  fputs("\"-> \"nodoSu",gra);
                  fprintf(gra,"%d",b);
                  fputs( "\";\n",gra);
                   }
                  int bb =0;
                  int cc =bb+1;

                  ///Crear nodos de las pilas(Productos)... nodoPro-->nodoPro
                  NodoPro *temp=aux->primeroPro;
                   if(temp!=NULL){
                      fputs("\"nodoSu",gra);
                      fprintf(gra,"%d",i+1);
                      fputs("\"-> \"nodoPro",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",0);
                      fputs( "\";\n",gra);
                  while(temp->sig!=NULL){
                      fputs("\"nodoPro",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",bb);
                      fputs("\"-> \"nodoPro",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",cc);
                      fputs( "\";\n",gra);

                      temp=temp->sig;
                      bb++;
                      cc++;
                  }
                  }

                  bb =0;
                  cc =bb+1;

                 NodoCli *actual=aux->primeroCli;
                 if(actual!=NULL){
                      fputs("\"nodoSu",gra);
                      fprintf(gra,"%d",i+1);
                      fputs("\"-> \"nodoCli",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",0);
                      fputs( "\";\n",gra);

                      while(actual->sig!=NULL){
                      fputs("\"nodoCli",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",bb);
                      fputs("\"-> \"nodoCli",gra);
                      fprintf(gra, "%d",aux->Id);
                      fprintf(gra,"%d",cc);
                      fputs( "\";\n",gra);

                      actual=actual->sig;
                      bb++;
                      cc++;
                      }
                 }



                      aux=aux->sig;
                      b++;
                      c++;
              }
              fputs("\"nodoSu",gra);
              fprintf(gra,"%d",i);
              fputs("\"-> \"nodoSu",gra);
              fprintf(gra,"%d",1);
              fputs( "\";\n",gra);

              fputs("\"nodoSu",gra);
              fprintf(gra,"%d",1);
              fputs("\"-> \"nodoSu",gra);
              fprintf(gra,"%d",i);
              fputs( "\";\n",gra);


           fputs("fontsize = \"10\"\n",gra);
           fputs("shape = \"Mrecord\"\n",gra);
           fputs("color=\"LIMEGREEN\"\n",gra);
           fputs("style =\"filled, bold\"\n",gra);
           fputs("label =\"Supermercado\"\n",gra);
           fputs("}\n",gra);
         }else{
         fputs("\n subgraph cluster_2 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoSu",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("NULL ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"LIMEGREEN\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"Supermercado\"\n",gra);
          fputs("}\n",gra);

         }

         fputs("}",gra);

    fclose(gra);
    system("dot -Tpng Supermercado.dot -o Supermercado.png");
    system("kfmclient exec Supermercado.png");

}

///-------------------------------( CAJEROS )-----------------------------------------------------

///Lista Simple (Cajeros).........................................................................
struct nodoCajCliente{
    int cliente;
    int tipo;
    int productos;
    int total;
    struct nodoCajCliente *sig;

};

struct nodoCajeros{
    int Id;
    int Cajero;
    struct nodoCajeros *sig;
    struct nodoCajCliente *primeroCajCliente;
    struct nodoCajCliente *ultimoCajCliente;
};
typedef struct nodoCajeros NodoCaj;
NodoCaj *primeroCaj;
NodoCaj *ultimoCaj;

typedef struct nodoCajCliente NodoCajClie;


///Agregar a la Lista Simple de Cajeros...........................................................
void Agregar_Lista_Cajeros(int id, int cajero){
    NodoCaj *nuevo;
    nuevo=(NodoCaj*)malloc(sizeof(struct nodoCajeros));
    nuevo->Id=id;
    nuevo->Cajero=cajero;
    nuevo->sig=NULL;
    nuevo->primeroCajCliente=NULL;
    nuevo->ultimoCajCliente=NULL;

    if(primeroCaj==NULL){
        nuevo->sig=NULL;
        primeroCaj=nuevo;
        ultimoCaj=nuevo;
        Cant_Cajeros++;
    }else{
        nuevo->sig=NULL;
        ultimoCaj->sig=nuevo;
        ultimoCaj=nuevo;
        Cant_Cajeros++;

    }

}



///Graficar Lista de Cajeros.(Todo)...........................................................
void Graficar_Lista_Cajeros(){

    if(primeroCaj!=NULL){
        fputs("\n subgraph cluster_3 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=1;
        NodoCaj *aux=primeroCaj;
        for(int i=0; i<Cant_Cajeros; i++){
          fputs("\"",gra);
          fputs("nodoCaj",gra);
          fprintf(gra,"%d",a);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("ID: ",gra);
          fprintf(gra, "%d",aux->Cajero);
          fputs(" &#92;n ",gra);
          fputs("Cajero: ",gra);
          fprintf(gra, "%d",aux->Cajero);
          fputs("\"];\n",gra);
          a++;
                int aa=1;
                        ///Crear nodos de los Clientes....
                NodoCajClie *clientes=aux->primeroCajCliente;
                while(clientes!=NULL){
                      fputs("\"",gra);
                      fputs("nodoCajClie",gra);
                      fprintf(gra,"%d",aux->Id);
                      fprintf(gra,"%d",aa);
                      fputs("\"",gra);
                      fputs("\n[ ",gra);
                      fprintf(gra, "label=\" " );
                      fputs("Cliente: ",gra);
                      fprintf(gra, "%d",clientes->cliente);
                      fputs(" &#92;n ",gra);
                      fputs("Producto: ",gra);
                      fprintf(gra, "%d",clientes->tipo);
                      fputs(" &#92;n ",gra);
                      fputs("Cantidad: ",gra);
                      fprintf(gra, "%d",clientes->productos);
                      fputs(" &#92;n ",gra);
                      fputs("Total: ",gra);
                      fprintf(gra, "%d",clientes->total);
                      fputs("\"];\n",gra);
                      aa++;
                 clientes=clientes->sig;
                }


        aux=aux->sig;
        }

        int b=1;
        int c=b+1;
        aux=primeroCaj;
        for(int i=0; i<Cant_Cajeros;i++){
          /// nodo1---->nodo2
          if(b<Cant_Cajeros){
              fputs("\"nodoCaj",gra);
              fprintf(gra,"%d",b);
              fputs("\"-> \"nodoCaj",gra);
              fprintf(gra,"%d",c);
              fputs( "\";\n",gra);
        }
                int bb=1;
                int cc=bb+1;
                NodoCajClie *clientes=aux->primeroCajCliente;
                if(clientes!=NULL){
                    fputs("\"nodoCaj",gra);
                    fprintf(gra,"%d",b);
                    fputs("\"-> \"nodoCajClie",gra);
                    fprintf(gra,"%d",aux->Id);
                    fprintf(gra,"%d",1);
                    fputs( "\";\n",gra);

                       while(clientes->sig!=NULL){
                             fputs("\"nodoCajClie",gra);
                             fprintf(gra,"%d",aux->Id);
                             fprintf(gra,"%d",bb);
                             fputs("\"-> \"nodoCajClie",gra);
                             fprintf(gra,"%d",aux->Id);
                             fprintf(gra,"%d",cc);
                             fputs( "\";\n",gra);

                        clientes=clientes->sig;
                       }


                  }
            aux=aux->sig;
            b++;
            c++;
        }


         fputs("fontsize = \"10\"\n",gra);
         fputs("shape = \"Mrecord\"\n",gra);
         fputs("color=\"TOMATO\"\n",gra);
         fputs("style =\"filled, bold\"\n",gra);
         fputs("label =\"Cajeros\"\n",gra);
         fputs("}\n",gra);

    }else{
         fputs("\n subgraph cluster_3 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoCaj",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("NULL ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"TOMATO\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"Cajeros\"\n",gra);
          fputs("}\n",gra);

    }

}

///Grafica Individual de los Cajeros y sus Clientes...................................................
void Graficar_Cajeros(){
       gra=fopen("Cajeros.dot","wt");
       fputs("digraph g {\n ",gra);
       fputs("rankdir= \"LR\";\n",gra);
       fputs("node [\n" ,gra);
       fputs("fontsize = \"10\"\n",gra);
       fputs("shape = \"Mrecord\"\n",gra);
       fputs("color=\"darkslateblue\"\n",gra);
       fputs("style =\"filled, bold\"\n",gra);
       fputs("];\n",gra);

     if(primeroCaj!=NULL){
        fputs("\n subgraph cluster_3 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=1;
        NodoCaj *aux=primeroCaj;
        for(int i=0; i<Cant_Cajeros; i++){
          fputs("\"",gra);
          fputs("nodoCaj",gra);
          fprintf(gra,"%d",a);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("ID: ",gra);
          fprintf(gra, "%d",aux->Cajero);
          fputs(" &#92;n ",gra);
          fputs("Cajero: ",gra);
          fprintf(gra, "%d",aux->Cajero);
          fputs("\"];\n",gra);
          a++;
                int aa=1;
                        ///Crear nodos de los Clientes....
                NodoCajClie *clientes=aux->primeroCajCliente;
                while(clientes!=NULL){
                      fputs("\"",gra);
                      fputs("nodoCajClie",gra);
                      fprintf(gra,"%d",aux->Id);
                      fprintf(gra,"%d",aa);
                      fputs("\"",gra);
                      fputs("\n[ ",gra);
                      fprintf(gra, "label=\" " );
                      fputs("Cliente: ",gra);
                      fprintf(gra, "%d",clientes->cliente);
                      fputs(" &#92;n ",gra);
                      fputs("Producto: ",gra);
                      fprintf(gra, "%d",clientes->tipo);
                      fputs(" &#92;n ",gra);
                      fputs("Productos: ",gra);
                      fprintf(gra, "%d",clientes->productos);
                      fputs(" &#92;n ",gra);
                      fputs("Total: ",gra);
                      fprintf(gra, "%d",clientes->total);
                      fputs("\"];\n",gra);
                      aa++;
                 clientes=clientes->sig;
                }


        aux=aux->sig;
        }

        int b=1;
        int c=b+1;
        aux=primeroCaj;
        for(int i=0; i<Cant_Cajeros;i++){
          /// nodo1---->nodo2
          if(b<Cant_Cajeros){
              fputs("\"nodoCaj",gra);
              fprintf(gra,"%d",b);
              fputs("\"-> \"nodoCaj",gra);
              fprintf(gra,"%d",c);
              fputs( "\";\n",gra);
        }
                int bb=1;
                int cc=bb+1;
                NodoCajClie *clientes=aux->primeroCajCliente;
                if(clientes!=NULL){
                    fputs("\"nodoCaj",gra);
                    fprintf(gra,"%d",b);
                    fputs("\"-> \"nodoCajClie",gra);
                    fprintf(gra,"%d",aux->Id);
                    fprintf(gra,"%d",1);
                    fputs( "\";\n",gra);

                       while(clientes->sig!=NULL){
                             fputs("\"nodoCajClie",gra);
                             fprintf(gra,"%d",aux->Id);
                             fprintf(gra,"%d",bb);
                             fputs("\"-> \"nodoCajClie",gra);
                             fprintf(gra,"%d",aux->Id);
                             fprintf(gra,"%d",cc);
                             fputs( "\";\n",gra);

                        clientes=clientes->sig;
                       }


                  }
            aux=aux->sig;
            b++;
            c++;
        }


         fputs("fontsize = \"10\"\n",gra);
         fputs("shape = \"Mrecord\"\n",gra);
         fputs("color=\"TOMATO\"\n",gra);
         fputs("style =\"filled, bold\"\n",gra);
         fputs("label =\"Cajeros\"\n",gra);
         fputs("}\n",gra);

    }else{
         fputs("\n subgraph cluster_3 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoCaj",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("NULL ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"TOMATO\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"Cajeros\"\n",gra);
          fputs("}\n",gra);

    }

    fputs("}",gra);

    fclose(gra);
    system("dot -Tpng Cajeros.dot -o Cajeros.png");
    system("kfmclient exec Cajeros.png");

}

///--------------------------------( VENTAS)-------------------------------------------------------
///Estructura de la Lista Simple de las (Ventas)...................................................
struct NodoVentas{
    int Cajero;
    int Cliente;
    int Tipo;
    int Productos;
    int Total;
    struct NodoVentas *sig;
};
typedef struct NodoVentas NodoV;
NodoV *primeroV;
NodoV *ultimoV;
///Estructura de las Sub Ventas...............................
struct NodoSubVentas{
    int Cajero;
    int Cliente;
    int Tipo;
    int Productos;
    int Total;
    struct NodoSubVentas *sig;
};
typedef struct NodoSubVentas NodoSub;
NodoSub *primeroSub;
NodoSub *ultimoSub;

///Agregar a la Lista Simple de las (Ventas).......................................................
void Agregar_Lista_Ventas(int cajero, int cliente, int tipo,  int producto, int total){
    NodoV *nuevo;
    nuevo=(NodoV*)malloc(sizeof(struct NodoVentas));
    nuevo->Cajero=cajero;
    nuevo->Cliente=cliente;
    nuevo->Tipo=tipo;
    nuevo->Productos=producto;
    nuevo->Total=total;
    nuevo->sig=NULL;


    if(primeroV==NULL){
        nuevo->sig=NULL;
        primeroV=nuevo;
        ultimoV=nuevo;
    }else{
        nuevo->sig=NULL;
        ultimoV->sig=nuevo;
        ultimoV=nuevo;
    }

  }

  void Agregar_SubLista_Ventas(int cajero, int cliente, int tipo, int producto, int total){
    NodoSub *nuevo;
    nuevo=(NodoSub*)malloc(sizeof(struct NodoSubVentas));
    nuevo->Cajero=cajero;
    nuevo->Cliente=cliente;
    nuevo->Tipo=tipo;
    nuevo->Productos=producto;
    nuevo->Total=total;
    nuevo->sig=NULL;


    if(primeroSub==NULL){
        nuevo->sig=NULL;
        primeroSub=nuevo;
        ultimoSub=nuevo;
    }else{
        nuevo->sig=NULL;
        ultimoSub->sig=nuevo;
        ultimoSub=nuevo;
    }

  }

void Crear_SubLista(int cajero){
    primeroSub=ultimoSub=NULL;
    if(primeroV!=NULL){
        NodoV *ventas=primeroV;
        while(ventas!=NULL){
            if(ventas->Cajero==cajero){
                Agregar_SubLista_Ventas(cajero, ventas->Cliente, ventas->Tipo,ventas->Productos, ventas->Total);
            }
        ventas=ventas->sig;
        }
    }
}


///Graficar Lista Simple de las (Ventas).(Todo)...........................................................
void Graficar_Lista_Ventas(){
    if(primeroCaj!=NULL){
        fputs("\n subgraph cluster_4 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=1;
        NodoV *aux=primeroV;
        while(aux!=NULL){
          fputs("\"",gra);
          fputs("nodoV",gra);
          fprintf(gra,"%d",a);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("Cajero: ",gra);
          fprintf(gra, "%d",aux->Cajero);
          fputs(" &#92;n ",gra);
          fputs("Cliente: ",gra);
          fprintf(gra, "%d",aux->Cliente);
          fputs(" &#92;n ",gra);
          fputs("Producto: ",gra);
          fprintf(gra, "%d",aux->Tipo);
          fputs(" &#92;n ",gra);
          fputs("Cantidad: ",gra);
          fprintf(gra, "%d",aux->Productos);
          fputs(" &#92;n ",gra);
          fputs("Total: ",gra);
          fprintf(gra, "%d",aux->Total);
          fputs("\"];\n",gra);
          a++;

          aux=aux->sig;
        }

        int b=1;
        int c=b+1;
        aux=primeroV;
        if(aux!=NULL){
        while(aux->sig!=NULL){
          /// nodo1---->nodo2

              fputs("\"nodoV",gra);
              fprintf(gra,"%d",b);
              fputs("\"-> \"nodoV",gra);
              fprintf(gra,"%d",c);
              fputs( "\";\n",gra);

            aux=aux->sig;
            b++;
            c++;
        }
        }

         fputs("fontsize = \"10\"\n",gra);
         fputs("shape = \"Mrecord\"\n",gra);
         fputs("color=\"SKYBLUE\"\n",gra);
         fputs("style =\"filled, bold\"\n",gra);
         fputs("label =\"Ventas\"\n",gra);
         fputs("}\n",gra);

    }else{
         fputs("\n subgraph cluster_4 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoV",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("NULL ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"SKYBLUE\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"Ventas\"\n",gra);
          fputs("}\n",gra);

    }

}

///Graficar Sub Lista de Ventas (Todo).............................................................
void Graficar_SubLista_Ventas(){
    if(primeroSub!=NULL){
        fputs("\n subgraph cluster_5 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=1;
        NodoSub *aux=primeroSub;
        while(aux!=NULL){
          fputs("\"",gra);
          fputs("nodoSub",gra);
          fprintf(gra,"%d",a);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("Cajero: ",gra);
          fprintf(gra, "%d",aux->Cajero);
          fputs(" &#92;n ",gra);
          fputs("Cliente: ",gra);
          fprintf(gra, "%d",aux->Cliente);
          fputs(" &#92;n ",gra);
          fputs("Producto: ",gra);
          fprintf(gra, "%d",aux->Tipo);
          fputs(" &#92;n ",gra);
          fputs("Cantidad: ",gra);
          fprintf(gra, "%d",aux->Productos);
          fputs(" &#92;n ",gra);
          fputs("Total: ",gra);
          fprintf(gra, "%d",aux->Total);
          fputs("\"];\n",gra);
          a++;

          aux=aux->sig;
        }

        int b=1;
        int c=b+1;
        aux=primeroSub;
        if(aux!=NULL){
        while(aux->sig!=NULL){
          /// nodo1---->nodo2

              fputs("\"nodoSub",gra);
              fprintf(gra,"%d",b);
              fputs("\"-> \"nodoSub",gra);
              fprintf(gra,"%d",c);
              fputs( "\";\n",gra);

            aux=aux->sig;
            b++;
            c++;
        }
        }

         fputs("fontsize = \"10\"\n",gra);
         fputs("shape = \"Mrecord\"\n",gra);
         fputs("color=\"SKYBLUE\"\n",gra);
         fputs("style =\"filled, bold\"\n",gra);
         fputs("label =\"SubLista Ventas\"\n",gra);
         fputs("}\n",gra);

    }else{
         fputs("\n subgraph cluster_5 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoSub",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("NULL ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"SKYBLUE\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"SubLista Ventas\"\n",gra);
          fputs("}\n",gra);

    }
}

///Graficar Lista Simple de las Ventas y Sub lista (Individual).................................................
void Graficar_Ventas_y_SubVentas(){
       gra=fopen("Ventas.dot","wt");
       fputs("digraph g {\n ",gra);
       fputs("rankdir= \"LR\";\n",gra);
       fputs("node [\n" ,gra);
       fputs("fontsize = \"10\"\n",gra);
       fputs("shape = \"Mrecord\"\n",gra);
       fputs("color=\"darkslateblue\"\n",gra);
       fputs("style =\"filled, bold\"\n",gra);
       fputs("];\n",gra);
    /// LISTA VENTAS....................

    if(primeroCaj!=NULL){
        fputs("\n subgraph cluster_4 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=1;
        NodoV *aux=primeroV;
        while(aux!=NULL){
          fputs("\"",gra);
          fputs("nodoV",gra);
          fprintf(gra,"%d",a);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("Cajero: ",gra);
          fprintf(gra, "%d",aux->Cajero);
          fputs(" &#92;n ",gra);
          fputs("Cliente: ",gra);
          fprintf(gra, "%d",aux->Cliente);
          fputs("Producto: ",gra);
          fprintf(gra, "%d",aux->Tipo);
          fputs(" &#92;n ",gra);
          fputs("Cantidad: ",gra);
          fprintf(gra, "%d",aux->Productos);
          fputs(" &#92;n ",gra);
          fputs("Total: ",gra);
          fprintf(gra, "%d",aux->Total);
          fputs("\"];\n",gra);
          a++;

          aux=aux->sig;
        }

        int b=1;
        int c=b+1;
        aux=primeroV;
        if(aux!=NULL){
        while(aux->sig!=NULL){
          /// nodo1---->nodo2

              fputs("\"nodoV",gra);
              fprintf(gra,"%d",b);
              fputs("\"-> \"nodoV",gra);
              fprintf(gra,"%d",c);
              fputs( "\";\n",gra);

            aux=aux->sig;
            b++;
            c++;
        }
        }

         fputs("fontsize = \"10\"\n",gra);
         fputs("shape = \"Mrecord\"\n",gra);
         fputs("color=\"SKYBLUE\"\n",gra);
         fputs("style =\"filled, bold\"\n",gra);
         fputs("label =\"Cajeros\"\n",gra);
         fputs("}\n",gra);

    }else{
         fputs("\n subgraph cluster_4 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoV",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("NULL ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"SKYBLUE\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"Ventas\"\n",gra);
          fputs("}\n",gra);

    }

    ///SUB LISTA VENTAS..........

     if(primeroSub!=NULL){
        fputs("\n subgraph cluster_5 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=1;
        NodoSub *aux=primeroSub;
        while(aux!=NULL){
          fputs("\"",gra);
          fputs("nodoSub",gra);
          fprintf(gra,"%d",a);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("Cajero: ",gra);
          fprintf(gra, "%d",aux->Cajero);
          fputs(" &#92;n ",gra);
          fputs("Cliente: ",gra);
          fprintf(gra, "%d",aux->Cliente);
          fputs(" &#92;n ",gra);
          fputs("Producto: ",gra);
          fprintf(gra, "%d",aux->Tipo);
          fputs(" &#92;n ",gra);
          fputs("Cantidad: ",gra);
          fprintf(gra, "%d",aux->Productos);
          fputs(" &#92;n ",gra);
          fputs("Total: ",gra);
          fprintf(gra, "%d",aux->Total);
          fputs("\"];\n",gra);
          a++;

          aux=aux->sig;
        }

        int b=1;
        int c=b+1;
        aux=primeroSub;
        if(aux!=NULL){
        while(aux->sig!=NULL){
          /// nodo1---->nodo2

              fputs("\"nodoSub",gra);
              fprintf(gra,"%d",b);
              fputs("\"-> \"nodoSub",gra);
              fprintf(gra,"%d",c);
              fputs( "\";\n",gra);

            aux=aux->sig;
            b++;
            c++;
        }
        }

         fputs("fontsize = \"10\"\n",gra);
         fputs("shape = \"Mrecord\"\n",gra);
         fputs("color=\"SKYBLUE\"\n",gra);
         fputs("style =\"filled, bold\"\n",gra);
         fputs("label =\"SubLista Ventas\"\n",gra);
         fputs("}\n",gra);

    }else{
         fputs("\n subgraph cluster_5 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoSub",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("NULL ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"SKYBLUE\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"SubLista Ventas\"\n",gra);
          fputs("}\n",gra);

    }






    fputs("}",gra);

    fclose(gra);
    system("dot -Tpng Ventas.dot -o Ventas.png");
    system("kfmclient exec Ventas.png");

}

///-------------------------------( MATRIZ )-------------------------------------------------------
///Estructura de la Matriz.........................................................................
struct NodoLista2{
    int Cajero;
    int Cliente;
    int Tipo;
    int Producto;
    int Total;
    struct NodoLista2 *sig;

};
typedef struct NodoLista2 NodoL2;

struct NodoLista1{
    int producto;
    struct NodoLista1 *sig;
    struct NodoLista2 *primeroL2;
    struct NodoLista2 *ultimoL2;
};
typedef struct NodoLista1 NodoL1;
NodoL1 *primeroL1;
NodoL1 *ultimoL1;

///Crear Matriz..................................................................
void Crear_Matriz(int producto){
    NodoL1 *nuevo;
    nuevo = (NodoL1*)malloc(sizeof(struct NodoLista1));
    nuevo->producto=producto;
    nuevo->sig=NULL;
    nuevo->primeroL2=NULL;
    nuevo->ultimoL2=NULL;

    if(primeroL1==NULL){
        nuevo->sig=NULL;
        primeroL1=nuevo;
        ultimoL1=nuevo;

                for(int i=0; i<4; i++){
                    NodoL2*nuevo2;
                    nuevo2 = (NodoL2*)malloc(sizeof(struct NodoLista2));
                    nuevo2->Cajero=0;
                    nuevo2->Cliente=0;
                    nuevo2->Tipo=0;
                    nuevo2->Producto=0;
                    nuevo2->Total=0;
                    nuevo2->sig=NULL;

                    if(primeroL1->primeroL2==NULL){
                        nuevo2->sig=NULL;
                        primeroL1->primeroL2=nuevo2;
                        primeroL1->ultimoL2=nuevo2;
                    }else{
                        nuevo2->sig=NULL;
                        primeroL1->ultimoL2->sig=nuevo2;
                        primeroL1->ultimoL2=nuevo2;
                    }
                }

    }else{
        nuevo->sig=NULL;
        ultimoL1->sig=nuevo;
        ultimoL1=nuevo;

                for(int i=0; i<4; i++){
                    NodoL2 *nuevo2;
                    nuevo2 = (NodoL2*)malloc(sizeof(struct NodoLista2));
                    nuevo2->Cajero=0;
                    nuevo2->Cliente=0;

                    if(ultimoL1->primeroL2==NULL){
                        nuevo2->sig=NULL;
                        ultimoL1->primeroL2=nuevo2;
                        ultimoL1->ultimoL2=nuevo2;
                    }else{
                        nuevo2->sig=NULL;
                        ultimoL1->ultimoL2->sig=nuevo2;
                        ultimoL1->ultimoL2=nuevo2;
                    }
                }
    }

}

///Agregar las Ventas a la Matriz Disperza........................................................
void Agregar_Venta_A_Matriz(int cajero, int cliente, int tipo, int producto, int total){
    srand(time(NULL));
    int random=1+rand()%(4);
    printf("***Random para la Matriz: %d\n",random);
    NodoL1 *Fila=primeroL1;
    if(Fila!=NULL){
        while(Fila!=NULL){
            if(Fila->producto==tipo){
            NodoL2 *Columna=Fila->primeroL2;
                for(int i=1; i<=4; i++){
                       if(i==random){
                            Columna->Cajero=cajero;
                            Columna->Cliente=cliente;
                            Columna->Tipo=tipo;
                            Columna->Producto=producto;
                            Columna->Total=total;
                        break;
                        }

                    Columna=Columna->sig;
                }
              break;
            }
        Fila=Fila->sig;
        }
    }

}

///Matriz.........................................................................................
void Matriz(int cantida){
    for(int i=1; i<=cantida; i++){
        Crear_Matriz(i);
    }

}

///----------------------------------(Recorrido por Filas)----------------------------------------
struct nodoRFilas{
    int cajero;
    int cliente;
    int tipo;
    int producto;
    int total;
    struct nodoRFilas *sig;
    struct nodoRFilas *ant;
};
typedef struct nodoRFilas nodoRF;
nodoRF *primeroRF;
nodoRF *ultimoRF;

///-----------------------------------(Recorrido por Columnas)------------------------------------
struct nodoRColumnas{
    int cajero;
    int cliente;
    int tipo;
    int producto;
    int total;
    struct nodoRColumnas *sig;
    struct nodoRColumnas *ant;
};
typedef struct nodoRColumnas nodoRC;
nodoRC *primeroRC;
nodoRC *ultimoRC;


///Insertar en Lista Doble Por Filas..............................................................
void Insertar_Recorrido_Filas(int cajero, int cliente, int tipo, int producto, int total){
    nodoRF *nuevo;
    nuevo=(nodoRF*)malloc(sizeof(struct nodoRFilas));
    nuevo->cajero=cajero;
    nuevo->cliente=cliente;
    nuevo->tipo=tipo;
    nuevo->producto=producto;
    nuevo->total=total;
    nuevo->sig=NULL;


    if(primeroRF==NULL){
        nuevo->sig=NULL;
        nuevo->ant=NULL;
        primeroRF=nuevo;
        ultimoRF=nuevo;
    }else{
        nuevo->sig=NULL;
        nuevo->ant=ultimoRF;
        ultimoRF->sig=nuevo;
        ultimoRF=nuevo;
    }

}

///Insertar en Lista Doble por Columnas...........................................................
void Insertar_Recorrido_Columna(int cajero, int cliente, int tipo, int producto, int total){
    nodoRC *nuevo;
    nuevo=(nodoRC*)malloc(sizeof(struct nodoRColumnas));
    nuevo->cajero=cajero;
    nuevo->cliente=cliente;
    nuevo->tipo=tipo;
    nuevo->producto=producto;
    nuevo->total=total;
    nuevo->sig=NULL;


    if(primeroRC==NULL){
        nuevo->sig=NULL;
        nuevo->ant=NULL;
        primeroRC=nuevo;
        ultimoRC=nuevo;
    }else{
        nuevo->sig=NULL;
        nuevo->ant=ultimoRC;
        ultimoRC->sig=nuevo;
        ultimoRC=nuevo;
    }

}


///Recorrido de Matriz por (Filas)................................................................
void Recorrdio_Filas(){
    primeroRF=ultimoRF=NULL;
    NodoL1 *Fila=primeroL1;
    if(Fila!=NULL){
        while(Fila!=NULL){
            Insertar_Recorrido_Filas(0,0,Fila->producto,0,0);
            NodoL2 *Columna=Fila->primeroL2;
            if(Columna!=NULL){
                while(Columna!=NULL){
                    Insertar_Recorrido_Filas(Columna->Cajero,Columna->Cliente,0,Columna->Producto,Columna->Total);
                Columna=Columna->sig;
                }
            }
        Fila=Fila->sig;
        }
    }

}

///Recorrido de Matriz por (Columnas)................................................................
void Recorrdio_Columnas(){
    primeroRC=ultimoRC=NULL;
    NodoL1 *Fila=primeroL1;
    if(Fila!=NULL){
        while(Fila!=NULL){
             Insertar_Recorrido_Columna(0,0,Fila->producto,0,0);
        Fila=Fila->sig;
        }
    }


        Fila=primeroL1;
        if(Fila!=NULL){
        while(Fila!=NULL){
             NodoL2 *Columna=Fila->primeroL2;
             if(Columna!=NULL){
                Insertar_Recorrido_Columna(Columna->Cajero,Columna->Cliente,0,Columna->Producto,Columna->Total);
              }

            Fila=Fila->sig;
            }
         }

         Fila=primeroL1;
        if(Fila!=NULL){
        while(Fila!=NULL){
             NodoL2 *Columna=Fila->primeroL2->sig;
             if(Columna!=NULL){
                Insertar_Recorrido_Columna(Columna->Cajero,Columna->Cliente,0,Columna->Producto,Columna->Total);
              }

            Fila=Fila->sig;
            }
         }

        Fila=primeroL1;
        if(Fila!=NULL){
        while(Fila!=NULL){
             NodoL2 *Columna=Fila->primeroL2->sig->sig;
             if(Columna!=NULL){
                Insertar_Recorrido_Columna(Columna->Cajero,Columna->Cliente,0,Columna->Producto,Columna->Total);
              }

            Fila=Fila->sig;
            }
         }

         Fila=primeroL1;
        if(Fila!=NULL){
        while(Fila!=NULL){
             NodoL2 *Columna=Fila->primeroL2->sig->sig->sig;
             if(Columna!=NULL){
                Insertar_Recorrido_Columna(Columna->Cajero,Columna->Cliente,0,Columna->Producto,Columna->Total);
              }

            Fila=Fila->sig;
            }
         }



    }



void MapeoIJ(int i, int j){
    int k= (j-1)*(5)+i;
    nodoRF *aux=primeroRF;
    for(int x=1; x<=k; x++){
        if(x==k){
           if(aux->cliente==0){
                printf("Mensaje de 200915305: Es un Nodo NULO, no posee informacion...\n");
           }else{
            printf("Cajero: %d \n",aux->cajero);
            printf("Cliente: %d \n",aux->cliente);
            printf("Producto: %d \n",j);
            printf("Cantidad: %d \n",aux->producto);
            printf("Total: %d \n",aux->total);
            }
        }
    aux=aux->sig;
    }

}

void MapeoJI(int j, int i){
    int k=(i-1)*(Cant_Estanterias)+j;
    nodoRC *aux=primeroRC;
    for(int x=1; x<=k; x++){
        if(x==k){
           if(aux->cliente==0){
                printf("\n Mensaje de 200915305: Es un Nodo NULO, no posee informacion...\n");
           }else{
            printf("Cajero: %d \n",aux->cajero);
            printf("Cliente: %d \n",aux->cliente);
            printf("Producto: %d \n",j);
            printf("Cantidad: %d \n",aux->producto);
            printf("Total: %d \n",aux->total);
            }
        }
    aux=aux->sig;
    }


}

void Graficar_Recorrido_Filas(){
     if(primeroRF!=NULL){
        fputs("\n subgraph cluster_8 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=1;
        nodoRF *aux=primeroRF;
        while(aux!=NULL){
          fputs("\"",gra);
          fputs("nodoRF",gra);
          fprintf(gra,"%d",a);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );

              if(aux->cajero==0 && aux->cliente==0){
                fprintf(gra,"%d",a);
                fputs(" &#92;n ",gra);
                fputs("NULL",gra);
                fputs("\"];\n",gra);
              }else if(aux->cajero==0 && aux->cliente==0 && aux->tipo!=0){
                fprintf(gra,"%d",a);
                fputs(" &#92;n ",gra);
                fputs("Producto: ",gra);
                fprintf(gra, "%d",aux->tipo);
                fputs("\"];\n",gra);
              }else{
                fprintf(gra,"%d",a);
                fputs(" &#92;n ",gra);
                fputs("Cajero: ",gra);
                fprintf(gra, "%d",aux->cajero);
                fputs(" &#92;n ",gra);
                fputs("Cliente: ",gra);
                fprintf(gra, "%d",aux->cliente);
                fputs(" &#92;n ",gra);
                fputs("Cantidad: ",gra);
                fprintf(gra, "%d",aux->producto);
                fputs(" &#92;n ",gra);
                fputs("Total: ",gra);
                fprintf(gra, "%d",aux->total);
                 fputs("\"];\n",gra);
              }
          a++;
          aux=aux->sig;
        }


        int b=1;
        int c=b+1;
        aux=primeroRF;
        if(aux!=NULL){
        while(aux->sig!=NULL){
          /// nodo1---->nodo2

              fputs("\"nodoRF",gra);
              fprintf(gra,"%d",b);
              fputs("\"-> \"nodoRF",gra);
              fprintf(gra,"%d",c);
              fputs( "\";\n",gra);

            fputs("\"nodoRF",gra);
              fprintf(gra,"%d",c);
              fputs("\"-> \"nodoRF",gra);
              fprintf(gra,"%d",b);
              fputs( "\";\n",gra);


            aux=aux->sig;
            b++;
            c++;
        }
        }

         fputs("fontsize = \"10\"\n",gra);
         fputs("shape = \"Mrecord\"\n",gra);
         fputs("color=\"BROWN\"\n",gra);
         fputs("style =\"filled, bold\"\n",gra);
         fputs("label =\"Recorrido Por Filas\"\n",gra);
         fputs("}\n",gra);

    }else{
         fputs("\n subgraph cluster_8 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoRF",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("NULL ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"BROWN\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"Recorrido Por Filas\"\n",gra);
          fputs("}\n",gra);

    }

}

void Graficar_Recorrido_Columna(){
     if(primeroRC!=NULL){
        fputs("\n subgraph cluster_9 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=1;
        nodoRC *aux=primeroRC;
        while(aux!=NULL){
          fputs("\"",gra);
          fputs("nodoRC",gra);
          fprintf(gra,"%d",a);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );

              if(aux->cajero==0 && aux->cliente==0){
                fprintf(gra,"%d",a);
                fputs(" &#92;n ",gra);
                fputs("NULL",gra);
                fputs("\"];\n",gra);
              }else if(aux->cajero==0 && aux->cliente==0 && aux->tipo!=0){
                fprintf(gra,"%d",a);
                fputs(" &#92;n ",gra);
                fputs("Producto: ",gra);
                fprintf(gra, "%d",aux->tipo);
                fputs("\"];\n",gra);
              }else{
                fprintf(gra,"%d",a);
                fputs(" &#92;n ",gra);
                fputs("Cajero: ",gra);
                fprintf(gra, "%d",aux->cajero);
                fputs(" &#92;n ",gra);
                fputs("Cliente: ",gra);
                fprintf(gra, "%d",aux->cliente);
                fputs(" &#92;n ",gra);
                fputs("Cantidad: ",gra);
                fprintf(gra, "%d",aux->producto);
                fputs(" &#92;n ",gra);
                fputs("Total: ",gra);
                fprintf(gra, "%d",aux->total);
                 fputs("\"];\n",gra);
              }
          a++;
          aux=aux->sig;
        }


        int b=1;
        int c=b+1;
        aux=primeroRC;
        if(aux!=NULL){
        while(aux->sig!=NULL){
          /// nodo1---->nodo2

              fputs("\"nodoRC",gra);
              fprintf(gra,"%d",b);
              fputs("\"-> \"nodoRC",gra);
              fprintf(gra,"%d",c);
              fputs( "\";\n",gra);


              fputs("\"nodoRC",gra);
              fprintf(gra,"%d",c);
              fputs("\"-> \"nodoRC",gra);
              fprintf(gra,"%d",b);
              fputs( "\";\n",gra);

            aux=aux->sig;
            b++;
            c++;
        }
        }

         fputs("fontsize = \"10\"\n",gra);
         fputs("shape = \"Mrecord\"\n",gra);
         fputs("color=\"BROWN\"\n",gra);
         fputs("style =\"filled, bold\"\n",gra);
         fputs("label =\"Recorrido Por Columnas\"\n",gra);
         fputs("}\n",gra);

    }else{
         fputs("\n subgraph cluster_9 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoRC",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("NULL ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"BROWN\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"Recorrido Por Columnas\"\n",gra);
          fputs("}\n",gra);

    }

}

///Graficar Matriz................................................................................
void Graficar_Matriz(){

       gra=fopen("Matriz.dot","wt");
       fputs("digraph g {\n ",gra);
       fputs("node [\n" ,gra);
       fputs("fontsize = \"10\"\n",gra);
       fputs("shape = \"Mrecord\"\n",gra);
       fputs("color=\"darkslateblue\"\n",gra);
       fputs("style =\"filled, bold\"\n",gra);
       fputs("];\n",gra);

    if(primeroL1!=NULL){
        fputs("\n subgraph cluster_6 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=1;
        NodoL1 *Fila=primeroL1;
        while(Fila!=NULL){
          fputs("\"",gra);
          fputs("nodoF",gra);
          fprintf(gra,"%d",a);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("Producto: ",gra);
          fprintf(gra, "%d",Fila->producto);
          fputs("\"];\n",gra);
          a++;
                int aa=1;
                NodoL2 *Columna=Fila->primeroL2;
                if(Columna!=NULL){
                    while(Columna!=NULL){
                        fputs("\"",gra);
                        fputs("nodoC",gra);
                        fprintf(gra,"%d",Fila->producto);
                        fprintf(gra,"%d",aa);
                        fputs("\"",gra);
                        fputs("\n[ ",gra);
                        fprintf(gra, "label=\" " );
                        if(Columna->Cajero==0 &&Columna->Cliente==0){
                            fputs("NULL",gra);
                        }else{
                            fputs("Cajero: ",gra);
                            fprintf(gra, "%d",Columna->Cajero);
                            fputs(" &#92;n ",gra);
                            fputs("Cliente: ",gra);
                            fprintf(gra, "%d",Columna->Cliente);
                            fputs(" &#92;n ",gra);
                            fputs("Producto: ",gra);
                            fprintf(gra, "%d",Columna->Tipo);
                            fputs(" &#92;n ",gra);
                            fputs("Cantidad: ",gra);
                            fprintf(gra, "%d",Columna->Producto);
                            fputs(" &#92;n ",gra);
                            fputs("Total: ",gra);
                            fprintf(gra, "%d",Columna->Total);
                        }
                        fputs("\"];\n",gra);
                        aa++;
                    Columna=Columna->sig;
                    }
                }

          Fila=Fila->sig;
        }
        a=1;
        Fila=primeroL1;
        while(Fila!=NULL){
          fputs("{rank = same; ",gra);
          fputs("\"",gra);
          fputs("nodoF",gra);
          fprintf(gra,"%d",a);
          fputs("\"",gra);
          fputs(";",gra);
          a++;
                int aa=1;
                NodoL2 *Columna=Fila->primeroL2;
                if(Columna!=NULL){
                    while(Columna!=NULL){
                        fputs("\"",gra);
                        fputs("nodoC",gra);
                        fprintf(gra,"%d",Fila->producto);
                        fprintf(gra,"%d",aa);
                        fputs("\"",gra);
                        fputs(";",gra);
                        aa++;
                    Columna=Columna->sig;
                    }
                }
          fputs("}\n",gra);
          Fila=Fila->sig;
        }



        int b=1;
        int c=b+1;
        Fila=primeroL1;
        if(Fila!=NULL){
        while(Fila!=NULL){
          /// nodo1---->nodo2

              fputs("\"nodoF",gra);
              fprintf(gra,"%d",b);
              fputs("\"-> \"nodoC",gra);
              fprintf(gra,"%d",Fila->producto);
              fprintf(gra,"%d",1);
              fputs( "\";\n",gra);
            if(Fila!=ultimoL1){
              fputs("\"nodoF",gra);
              fprintf(gra,"%d",b);
              fputs("\"-> \"nodoF",gra);
              fprintf(gra,"%d",c);
              fputs( "\";\n",gra);
            }

                         int bb=1;
                         int cc=bb+1;
                         NodoL2 *Columna=Fila->primeroL2;
                         if(Columna!=NULL){
                            while(Columna!=NULL){
                                if(Columna!=Fila->ultimoL2){
                                    fputs("\"nodoC",gra);
                                    fprintf(gra,"%d",Fila->producto);
                                    fprintf(gra,"%d",bb);
                                    fputs("\"-> \"nodoC",gra);
                                    fprintf(gra,"%d",Fila->producto);
                                    fprintf(gra,"%d",cc);
                                    fputs( "\";\n",gra);
                                }
                            bb++;
                            cc++;
                            Columna=Columna->sig;
                            }
                         }

            Fila=Fila->sig;
            b++;
            c++;


        }
        }



         fputs("fontsize = \"10\"\n",gra);
         fputs("shape = \"Mrecord\"\n",gra);
         fputs("color=\"BROWN\"\n",gra);
         fputs("style =\"filled, bold\"\n",gra);
         fputs("label =\"Matriz\"\n",gra);
         fputs("}\n",gra);

    }else{
         fputs("\n subgraph cluster_6 {\n",gra);
         fputs("node [style=filled];\n",gra);

          fputs("\"",gra);
          fputs("nodoF",gra);
          fputs("\"",gra);
          fputs("\n[ ",gra);
          fprintf(gra, "label=\" " );
          fputs("Matriz ",gra);
          fputs("\"];\n",gra);

          fputs("fontsize = \"10\"\n",gra);
          fputs("shape = \"Mrecord\"\n",gra);
          fputs("color=\"BROWN\"\n",gra);
          fputs("style =\"filled, bold\"\n",gra);
          fputs("label =\"Matriz\"\n",gra);
          fputs("}\n",gra);

    }


    Recorrdio_Filas();
    Graficar_Recorrido_Filas();
    Recorrdio_Columnas();
    Graficar_Recorrido_Columna();


      fputs("}",gra);

    fclose(gra);
    system("dot -Tpng Matriz.dot -o Matriz.png");
    system("kfmclient exec Matriz.png");


}


///-----------------------------( MOVIMIENTOS )----------------------------------------------------

/// Mover al carro una posicion hacia adelante...................................
void Mover_Carro_A_Entrada(int carro){
    NodoCa *actual=primeroCa;
    while(actual!=NULL){
        if(actual->Carro==carro){
            if(actual->sig==NULL){
                printf("\n***No se puede realizar el Movimiento...\n");
            }else if(actual->sig->Id==Entrada){
                printf("\n***El carro ya esta Frente a la Entrada...\n");
            }else if(actual->Id==Entrada){
                printf("\n***No se puede realizar el Movimiento...\n");


            }else{
                int aux=actual->Carro;
                actual->Carro=actual->sig->Carro;
                actual->sig->Carro=aux;
            }

         break;
        }else if(actual->Id==Entrada){
            printf("\n***No se puede realizar el Movimiento...\n");
         break;
        }
        actual=actual->sig;
    }

}

///Calcular un Numero random para Insertar el Carro a la Lista Circular(Parqueo)..........................
int Random_Parqueo(int carro){

    srand(time(NULL));
    if(Cant_Parqueo>0){
        int random=1+rand()%(Cant_Parqueo);
        NodoPa *actual=primeroPa;
        for(int i=0;i<Cant_Parqueo;i++){
            if(actual->Id==random){
                if(actual->Carro==0){
                    printf("\n***Numero Random: %d \n",random);
                    actual->Carro=carro;
                    Contador_Random=0;
                    return 1;
                }
                break;
            }

            actual=actual->sig;
        }
        Contador_Random++;
    }

    return 0;
}


///Agregar a las Pilas de los Clientes (Estanterias)..............................................
void Agregar_Pila_Clientes_Estanterias(int random, int Cliente){
    NodoSu *aux=primeroSu;
        for(int i=0; i<Cant_Estanterias; i++){
            if(aux->Id==random){
                NodoCli *nuevo;
                nuevo = (NodoCli*)malloc(sizeof(struct NodoCliente));
                nuevo->Cliente=Cliente;
                nuevo->Tipo=aux->Id;
                nuevo->Productos=0;
                nuevo->Total=0;
                nuevo->sig=NULL;

                if(aux->primeroCli==NULL){
                    nuevo->sig=NULL;
                    aux->primeroCli=nuevo;
                    aux->ultimoCli=nuevo;
                }else{
                    nuevo->sig=NULL;
                    aux->ultimoCli->sig=nuevo;
                    aux->ultimoCli=nuevo;
                }

            }

            aux=aux->sig;
        }

}


///Calcular un Numero random para Insertar al Cliente en la Lista Circular(Estanterias)...............
void Random_Estanterias(int Cliente){
 srand(time(NULL));
    if(Cant_Estanterias>0){
        int random=1+rand()%(Cant_Estanterias);
        NodoPa *actual=primeroPa;
        for(int i=0;i<Cant_Parqueo;i++){
            if(actual->Carro==Cliente){
                printf("\n***Numero Random: %d \n",random);
                Agregar_Pila_Clientes_Estanterias(random,Cliente);
                actual->Carro=0;
                break;
            }

            actual=actual->sig;
        }

    }

 }

///Mover un Carro hacia la lista Circular que es el Parqueo...........................................
void Mover_Carro_A_Parqueo(int carro){

    NodoCa *actual=primeroCa;
    if(actual!=NULL){
        while(actual!=NULL){
            if(actual->Carro==carro && actual->sig->Carro==Entrada){
                int a = Random_Parqueo(actual->Carro);
                if(a==1){
                 actual->Carro=0;
                }

            }

            actual=actual->sig;
        }
    }
}

///Agregar a las Pilas de los Clientes en (Estanterias)...............................................
void Mover_Cliente_A_Supermercado(int carro){
   Random_Estanterias(carro);
}

///Insertar en la Cola de las Cajas (Estructura de las Cajas)..........................................
void Insertar_En_Cola_De_Cajeros(int cliente,int tipo, int productos, int total){
    srand(time(NULL));
    if(Cant_Cajeros>0){
        int random=1+rand()%(Cant_Cajeros);
        printf("\n***Numero Random: %d \n",random);
        NodoCaj *cajero=primeroCaj;
        while(cajero!=NULL){
            if(cajero->Id==random){
            printf("Encontro Cajero...\n");
                NodoCajClie *nuevo;
                nuevo = (NodoCajClie*)malloc(sizeof(struct nodoCajCliente));
                nuevo->cliente=cliente;
                nuevo->tipo=tipo;
                nuevo->productos=productos;
                nuevo->total=total;
                nuevo->sig=NULL;


                if(cajero->primeroCajCliente==NULL){
                    nuevo->sig=NULL;
                    cajero->primeroCajCliente=nuevo;
                    cajero->ultimoCajCliente=nuevo;
                }else{
                    nuevo->sig=NULL;
                    cajero->ultimoCajCliente->sig=nuevo;
                    cajero->ultimoCajCliente=nuevo;
                }
             break;
            }
        cajero=cajero->sig;
        }
    }

}

///Pasar a Caja (Estructura del Supermercado).............................................................
void Pasar_A_Caja(int cliente){
    NodoSu *estanteria=primeroSu;
    for(int i=0; i<Cant_Estanterias; i++){
        NodoCli *actual = estanteria->primeroCli;
        if(actual!=NULL){
            NodoCli *ultimo = estanteria->ultimoCli;
            if(ultimo->Cliente==cliente){
                ///Eliminar Ultimo Cliente...
                if(estanteria->primeroCli==estanteria->ultimoCli){
                    Insertar_En_Cola_De_Cajeros(estanteria->ultimoCli->Cliente,estanteria->ultimoCli->Tipo,estanteria->ultimoCli->Productos,estanteria->ultimoCli->Total);
                    estanteria->primeroCli=NULL;
                    estanteria->ultimoCli=NULL;
                }else{
                    NodoCli *aux=estanteria->primeroCli;
                    while(aux->sig!=estanteria->ultimoCli){
                        aux=aux->sig;
                    }
                    Insertar_En_Cola_De_Cajeros(estanteria->ultimoCli->Cliente,estanteria->ultimoCli->Tipo,estanteria->ultimoCli->Productos,estanteria->ultimoCli->Total);
                    estanteria->ultimoCli=aux;
                    estanteria->ultimoCli->sig=NULL;
                }

                printf("\n--> Se movio a Caja...");
                break;

            }
        }else{
            //printf("\n--> Error, no se pudo realizar el Movimiento...");

        }

    estanteria=estanteria->sig;
    }


}
///Cobrar en Caja y pasar a la Lista de Ventas........................................................
void Cobrar_En_Caja(int caja){
    ///Buscar si existe la caja...
    NodoCaj *actual=primeroCaj;
    if(actual!=NULL){
        while(actual!=NULL){
            if(actual->Id==caja){/// Si existe la caja...
                if(actual->primeroCajCliente!=NULL){
                ///Pasar a la Lista de las Ventas.............
                    Agregar_Lista_Ventas(actual->Cajero,actual->primeroCajCliente->cliente,actual->primeroCajCliente->tipo,actual->primeroCajCliente->productos,actual->primeroCajCliente->total);
                ///Pasar a la Matriz..........................
                    Agregar_Venta_A_Matriz(actual->Cajero,actual->primeroCajCliente->cliente,actual->primeroCajCliente->tipo,actual->primeroCajCliente->productos,actual->primeroCajCliente->total);
                    actual->primeroCajCliente=actual->primeroCajCliente->sig;
                }

            }
        actual=actual->sig;
        }
    }
}



///-----------------------------( MENU DE OPCIONES )-----------------------------------------------

///Menu de Opciones de la ( Simulacion )...........................................................
void Simular(){
int n, opcion, cliente, producto, cantidad;
   do
    {
       // system("clear");
        printf( "\n************************( Simulacion )************************");
        printf( "\n   1. Mover Carro al Parqueo...");
        printf( "\n   2. Mover Carro a la Entrada...");
        printf( "\n   3. Mover Cliente al Supermercado...");
        printf( "\n   4. Mover Cliente en el Supermercado (Sig-->)...");
        printf( "\n   5. Mover Cliente en el Supermercado (<--Ant)...");
        printf( "\n   6. Comprar Productos...." );
        printf( "\n   7. Pasar a Caja...." );
        printf( "\n   8. Cobrar en Caja...." );
        printf( "\n   9. Crear Sub Lista por Cajero...." );
        printf( "\n   10. Graficar Todo...." );
        printf( "\n   11. Graficar Matriz...." );
        printf( "\n   12. Salir...." );
        printf( "\n\n   Introduzca opcion (1-12): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: system("clear");
                    printf( "\n   Ingrese el Carro que desea Ingresar al Parqueo...");
                    scanf( "%d", &n );
                    Mover_Carro_A_Parqueo(n);

                    break;


            case 2: system("clear");
                    printf( "\n   Cual carro desea ingresar a la Entrada... ");
                    scanf( "%d", &n );
                    Mover_Carro_A_Entrada(n);
                    break;

            case 3: system("clear");
                    printf( "\n   Cual Cliente desea ingresar al Supermercado... ");
                    scanf( "%d", &n );
                    Mover_Cliente_A_Supermercado(n);
                    break;

            case 4: system("clear");
                    printf( "\n   Cual Cliente desea mover (Sig-->)... ");
                    scanf( "%d", &n );
                    MoverSiguiente(n);
                    break;

            case 5: system("clear");
                    printf( "\n   Cual Cliente desea mover (<--Ant)... ");
                    scanf( "%d", &n );
                    MOverAnterior(n);
                    break;

            case 6: system("clear");
                    printf( "\n   **********Puede Realizar Su Compra********** ");
                    printf( "\n   Cual Cliente desea que Compre... ");
                    scanf( "%d", &cliente );
                    printf( "\n   Que Producto desea que Compre... ");
                    scanf( "%d", &producto );
                    printf( "\n   Cuantos Productos desa Comprar... ");
                    scanf( "%d", &cantidad );
                    Compras(cliente,producto,cantidad);
                    break;

            case 7: system("clear");
                    printf( "\n   **********Pasar a Caja********** ");
                    printf( "\n   Cual Cliente desea que pase a Caja... ");
                    scanf( "%d", &cliente );
                    Pasar_A_Caja(cliente);
                    break;

            case 8: system("clear");
                    printf( "\n   **********Cobrar en Caja********** ");
                    printf( "\n   En cual caja desea Cobrar?... ");
                    scanf( "%d", &n );
                    Cobrar_En_Caja(n);
                    break;

            case 9: system("clear");
                    printf( "\n   **********Crear Sub Lista Por Cajero********** ");
                    printf( "\n   Escoja un Cajero... ");
                    scanf( "%d", &n );
                    Crear_SubLista(n);
                    break;


            case 10:
                    printf( "\n   Graficar Todo... ");
                    Graficar();
                    break;

            case 11:
                    printf( "\n   Graficar Matriz... ");
                    Graficar_Matriz();
                    break;

            case 12:
                    system("clear");
                    break;

        }

         /* Fin del anidamiento */

    } while ( opcion != 12 );

}

///Menu de Ventas..................................................................................
void Ventas(){
   int n, opcion, i, j;
   do
    {

        printf( "\n************************( Ventas )************************");
        printf( "\n   1. Graficar Lista Ventas...");
        printf( "\n   2. Graficar Matriz de Ventas...");
        printf( "\n   3. Mapeo Lexicografico por Filas...");
        printf( "\n   4. Mapeo Lexicografico por Columnas...");
        printf( "\n   5. Salir...." );
        printf( "\n\n   Introduzca opcion (1-5): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1:
                    printf( "\n  Lista de Ventas...");
                    Graficar_Ventas_y_SubVentas();
                    break;


            case 2:
                    printf( "\n  Matriz de Ventas... ");
                    Graficar_Matriz();
                    break;

            case 3: system("clear");
                    printf( "\n Ingrese posicion ( i )...");
                    scanf( "%d", &i );
                    printf( "\n Ingrese posicion ( j )...");
                    scanf( "%d", &j );
                    MapeoIJ(i,j);
                    break;

            case 4: system("clear");
                    printf( "\n Ingrese posicion ( j )...");
                    scanf( "%d", &j );
                    printf( "\n Ingrese posicion ( i )...");
                    scanf( "%d", &i );
                    MapeoJI(j,i);
                    break;

            case 5:
                    system("clear");
                    break;

        }

         /* Fin del anidamiento */

    } while ( opcion != 5 );


}


///Menu de Opciones de ( Cajeros ) ................................................................

void Cajeros(){
   int n, opcion;
   do
    {

        printf( "\n************************( Cajeros )************************");
        printf( "\n   1. Agregar Cantidad de Cajeros...");
        printf( "\n   2. Graficar Cajeros...");
        printf( "\n   3. Graficar Todo...");
        printf( "\n   4. Salir...." );
        printf( "\n\n   Introduzca opcion (1-4): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: system("clear");
                    printf( "\n   Introduzca Cantidad de Cajeros...");
                    scanf( "%d", &n );
                    Agregar_Cajeros(n);
                    break;


            case 2:
                    printf( "\n   Graficar Cajeros... ");
                    Graficar_Cajeros();
                    break;

            case 3:
                    printf( "\n   Graficar Todo... ");
                    Graficar();
                    break;

            case 4:
                    system("clear");
                    break;

        }

         /* Fin del anidamiento */

    } while ( opcion != 4 );

}


///Menu de Opciones del ( Supermercado, Estanterias y Productos) ..................................
void Supermercado(){
   int n=0;
   int opcion=0;
   do
    {

        printf( "\n************************( SUPERMERCADO, ESTANTERIAS Y PRODUCTOS )************************");
        printf( "\n   1. Agregar Cantidad de Estanterias...");
        printf( "\n   2. Agregar Cantidad de Productos...");
        printf( "\n   3. Graficar Supermercado...");
        printf( "\n   4. Graficar Todo...");
        printf( "\n   5. Salir...." );
        printf( "\n\n   Introduzca opcion (1-5): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: system("clear");
                    printf( "\n   Introduzca Cantidad de Estanterias...");
                    scanf( "%d", &n );
                    Agregar_Estanterias(n);
                    Matriz(n);
                    break;

            case 2: system("clear");
                    printf( "\n   Introduzca Cantidad de Productos.. ");
                    scanf( "%d", &n );
                    Agregar_Pila_Productos(n);
                    break;

            case 3:
                    printf( "\n   Graficar Supermercado... ");
                    Grafica_Supermercado();
                    break;

            case 4:
                    printf( "\n   Graficar Todo... ");
                    Graficar();
                    break;

            case 5:
                    system("clear");
                    break;

        }

         /* Fin del anidamiento */

    } while ( opcion != 5 );

}

///Menu de Opciones de la (Carretera).......................................................
void Carretera(){

   int n, opcion;
   do
    {

        printf( "\n************************( CARRETERA )************************");
        printf( "\n   1. Agregar Cantidad de Carros...");
        printf( "\n   2. Cual sera tu nodo ENTRADA...");
        printf( "\n   3. Agregar un nuevo Carro...");
        printf( "\n   4. Graficar Carretera...");
        printf( "\n   5. Graficar Todo...");
        printf( "\n   6. Salir...." );
        printf( "\n\n   Introduzca opcion (1-6): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: system("clear");
                    printf( "\n   Introduzca Cantidad de Carros...");
                    scanf( "%d", &n );
                    Agregar_Carros(n);
                    break;

            case 2: system("clear");
                    printf( "\n   Cual sera tu nodo ENTRADA... ");
                    Entrada_Carretera();
                    break;


            case 3: system("clear");
                    printf( "\n   Agregar un nuevo Carro... ");

                    break;

            case 4:
                    printf( "\n   Graficar Carretera... ");
                    Grafica_Carretera();
                    break;

            case 5:
                    printf( "\n   Graficar Todo... ");
                    Graficar();
                    break;

            case 6:
                    system("clear");
                    break;

        }

         /* Fin del anidamiento */

    } while ( opcion != 6 );

}

///Menu de Opciones del (Parqueo)............................................................
void Parqueo(){
int n, opcion;
   do
    {

        printf( "\n************************( PARQUEO )************************");
        printf( "\n   1. Agregar Cantidad de Espacion en el Parqueo...");
        printf( "\n   2. Agregar mas espacion en el Parqueo...");
        printf( "\n   3. Eliminar espacion en el Parqueo...");
        printf( "\n   4. Graficar Parqueo...");
        printf( "\n   5. Graficar Todo...");
        printf( "\n   6. Salir...." );
        printf( "\n\n   Introduzca opcion (1-6): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: system("clear");
                    printf( "\n   Introduzca Cantidad de espacion en el Parqueo...");
                    scanf( "%d", &n );
                    Agregar_Parqueos(n);
                    break;

            case 2: system("clear");
                    printf( "\n   Introduzca un nuevo Carro... ");

                    break;

            case 3: system("clear");
                    printf( "\n   Eliminar Carro Carro... ");

                    break;

            case 4:
                    printf( "\n   Graficar Parqueo... ");
                    Grafica_Parqueo();
                    break;

            case 5:
                    printf( "\n   Graficar Todo... ");
                    Graficar();
                    break;

            case 6:
                    system("clear");
                    break;

        }

         /* Fin del anidamiento */

    } while ( opcion != 6 );
}


///Metodo Main del programa................................................................

int main()
{

    int n, opcion;

    do
    {

        printf( "\n************************( Wall-E-Mart )************************");
        printf( "\n   1. Carretera.");
        printf( "\n   2. Parqueo.");
        printf( "\n   3. Supermercado, Estanterias y Productos.");
        printf( "\n   4. Cajas." );
        printf( "\n   5. Ventas." );
        printf( "\n   6. Simular." );
        printf( "\n   7. Grafica." );
        printf( "\n   8. Salir." );
        printf( "\n\n   Introduzca opcion (1-8): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: system("clear");
                  //  printf( "\n *************** Carretera ***************\n ");
                    Carretera();
                    break;

            case 2: system("clear");
                   // printf( "\n *************** Parqueo ***************\n ");
                    Parqueo();
                    break;

            case 3: system("clear");
                   // printf( "\n *************** Supermercado, Estanterias y Productos. ***************\n ");
                    Supermercado();
                    break;

            case 4: system("clear");
                    //printf( "\n *************** Cajas ***************\n ");
                    Cajeros();
                    break;

            case 5: system("clear");
                   // printf( "\n *************** Ventas ***************\n ");
                    Ventas();
                    break;

            case 6: system("clear");
                    //printf( "\n *************** Simular ***************\n ");
                    Simular();
                    break;

            case 7:
                    printf( "\n *************** Grafica ***************\n ");
                    Graficar();
                    break;

            case 8:
                    system("clear");
                    break;
         }

         /* Fin del anidamiento */

    } while ( opcion != 8 );

    return 0;
}

