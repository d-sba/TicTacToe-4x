#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "funcionesJuego.h"
#include "miniMax.h"



/**<                     ------------------------------ ARBOL ------------------------------                             */
/**<                                    ------------------------------------ */

/**< Funciones para crear los distintos elementos del arbol */
Node *creaArrel(int tauler[N][N]){
    Node *p=malloc(sizeof(Node));
    copiaMatriz(p->tauler, tauler);
    p->n_fills=contarColumnasLibres(p->tauler);
    p->fills = (Node **) malloc(p->n_fills*sizeof(Node *));
    p->cols=(int *)malloc(p->n_fills*sizeof(int));
    int j=0;
    for (int i=0;i<N;i++){
        if(p->tauler[0][i]==0){
            p->cols[j]=i;
            j+=1;
        }
    }

    return p;
}

Node *creaNode(Node *pare, int profunditat, int col,int jug, int dificultad, int *m){
    int j=0;
    Node *p=malloc(sizeof(Node));
    *m+=1;
    copiaMatriz(p->tauler,pare->tauler);
    tirar(p->tauler,col,jug);

    if (profunditat<2*dificultad && ganador(p->tauler,jug!=1)){
        p->n_fills=contarColumnasLibres(p->tauler);
        p->fills = (Node **) malloc(p->n_fills*sizeof(Node *));
        p->cols = (int *) malloc(p->n_fills*sizeof(int));
        *m+=2;
        for(int i=0;i<N;i++){
            if(p->tauler[0][i] == 0){
                p->cols[j] = i;
                j += 1;
            }
        }
    }
    else{
        p->n_fills=0;
        p->fills = NULL;
        p->cols = NULL;
    }

    return p;
}

void crea1Nivell(Node *pare,int profunditat, int jug, int dificultad,int *m){
    for (int i=0;i<pare->n_fills;i++){
        Node *hijo=creaNode(pare,profunditat+1,pare->cols[i],jug,dificultad,m);
        pare->fills[i]=hijo;
    }
}

void crea2Nivell(Node *pare, int profunditat,int dificultad, int *m){
    crea1Nivell(pare,profunditat,ord,dificultad,m);
    for (int i=0;i<pare->n_fills;i++){
        crea1Nivell(pare->fills[i],profunditat+1,hum,dificultad,m);
    }
}


/**< Funciones para el arbol */
void creaArbre (Node *arrel, int profunditat,int dificultad, int *m){
    crea2Nivell(arrel,profunditat,dificultad,m);
    if (profunditat==2*(dificultad-1)){
        return;
    }else {
        for (int i=0;i<arrel->n_fills;i++){
            for (int j=0;j<arrel->fills[i]->n_fills;j++){
                creaArbre(arrel->fills[i]->fills[j],profunditat+2,dificultad,m);
            }
        }
    }
}

void borrarArbre(Node *arrel, int *f){
   if (arrel->n_fills==0){
        free(arrel);       //como es fulla, no tenemos los mallocs de fills i cols
        *f+=1;
   }else{
        for (int i=0;i<arrel->n_fills;i++){
            borrarArbre(arrel->fills[i],f);
        }
        free(arrel->fills);
        free(arrel->cols);
        free(arrel);
        *f+=3;
   }
}


/**<                     ------------------------------ MINIMAX ------------------------------                             */
/**<                                    ------------------------------------ */


/**< Funciones para valorar los distintos componentes */
int heuristica(int tauler[N][N]){
    if(ganador(tauler,ord)==1) return victoria;
    if (ganador(tauler,hum)==1) return -victoria;
    else return heuristica2(tauler);
}

int heuristica2(int tauler[N][N]){
    //HORIZONTAL
    int n=0;
    int k=1;

    //Horizontal
    for (int i=0;i<N;i++){
        for (int j=0;j<(N-3);j++){
            if (tauler[i][j]==k){
                if (tauler[i][j+1]==k){
                    if (tauler[i][j+2]==k && tauler [i][j+3]==0){
                        return -75;
                    }else if (tauler[i][j+2]==0 && tauler [i][j+3]==0){
                        n=-50;
                    }
                }
            }
        }
    }

    //Vertical
    for (int i=3;i<N;i++){
        for (int j=0;j<N;j++){
            if (tauler[i][j]==k){
                if (tauler[i-1][j]==k){
                    if (tauler[i-2][j]==k && tauler[i-3][j]==0){
                        return -75;
                    }else if (tauler[i-2][j]==0 && tauler[i-3][j]==0){
                        n=-50;
                    }
                }
            }
        }
    }

    //Arriba derecha
    for (int i=3;i<N;i++){
        for (int j=0;j<(N-3);j++){
            if (tauler[i][j]==k){
                if (tauler[i-1][j+1]==k){
                    if (tauler [i-2][j+2]==k && tauler [i-3][j+3]==0){
                        return -75;
                    }else if (tauler [i-2][j+2]==0 && tauler [i-3][j+3]==0){
                        n=-50;
                    }
                }
            }
        }
    }

    //Arriba izq
    for (int i=3;i<N;i++){
        for (int j=3;j<N;j++){
            if (tauler[i][j]==k){
                if (tauler[i-1][j-1]==k){
                    if (tauler [i-2][j-2]==k && tauler [i-3][j-3]==0){
                        return -75;
                    }else if (tauler [i-2][j-2]==0 && tauler [i-3][j-3]==0){
                        n=-50;
                    }
                }
            }
        }
    }

    //Abajo izq
    for (int i=0;i<(N-3);i++){
        for (int j=3;j<N;j++){
            if (tauler[i][j]==k){
                if (tauler[i+1][j-1]==k){
                    if (tauler [i+2][j-2]==k && tauler [i+3][j-3]==0){
                        return -75;
                    }else if (tauler [i+2][j-2]==0 && tauler [i+3][j-3]==0){
                        n=-50;
                    }
                }
            }
        }
    }

    //Abajo derecha
    for (int i=0;i<(N-3);i++){
        for (int j=0;j<(N-3);j++){
            if (tauler[i][j]==k){
                if (tauler[i+1][j+1]==k){
                    if (tauler [i+2][j+2]==k && tauler [i+3][j+3]==0){
                        return -75;
                    }else if (tauler [i+2][j+2]==0 && tauler [i+3][j+3]==0){
                        n=-50;
                    }
                }
            }
        }
    }

    return n;
}



void valorarFullas(Node *arrel){
    if (arrel->n_fills==0){
        arrel->heu=heuristica(arrel->tauler);
    }else{
        for (int i=0;i<arrel->n_fills;i++){
            valorarFullas(arrel->fills[i]);
        }
    }
}

void valoraArbol (Node *arrel, int dificultad){        //No estoy del todo seguro de si esta funcion es buena
    if (dificultad==1){
        //min
        int valor1=101;
        for (int i=0;i<arrel->n_fills;i++){
            for (int j=0;j<arrel->fills[i]->n_fills;j++){
                if (arrel->fills[i]->fills[j]->heu<valor1){
                    valor1=arrel->fills[i]->fills[j]->heu;
                    arrel->fills[i]->heu=valor1;
                }
            }
            valor1=101;
        }

        //max
        int valor2=-101;
        for (int i=0;i<arrel->n_fills;i++){
            if (arrel->fills[i]->heu>valor2){
                arrel->heu=arrel->fills[i]->heu;
                valor2=arrel->fills[i]->heu;
            }
        }
    }
    else{
        for (int i=0;i<arrel->n_fills;i++){
            for (int j=0;j<arrel->fills[i]->n_fills;j++){
                valoraArbol(arrel->fills[i]->fills[j],dificultad-1);
            }
        }
        valoraArbol(arrel,1);
    }
}


/**< MiniMax */
int miniMax (Node *arrel,int dificultad){
    valorarFullas(arrel);
    valoraArbol(arrel,dificultad);
    /*if (arrel->heu==-100){
        printf("Si juegas bien, ya tienes ganada la partida...");
    }*/

    int j=0;
    int opciones[N];
    for (int i=0;i<arrel->n_fills;i++){
        if (arrel->fills[i]->heu==arrel->heu){
            opciones[j]=arrel->cols[i];
            j+=1;
        }
    }

    srand(time(NULL));
    int ind=rand()%j;
    return opciones[ind];
}


void dibujaPuntos1 (Node *arrel){
    printf("arrel->heu:%d\n",arrel->heu);
    for (int i=0;i<arrel->n_fills;i++){
        printf("arrel->fills[%d]->heu:%d\n",i,arrel->fills[i]->heu);
        for (int j=0;j<arrel->fills[i]->n_fills;j++){
            printf("arrel->fills[%d]->fills[%d]->heu:%d\n",i,j,arrel->fills[i]->fills[j]->heu);
        }
    }
}


void dibujaPuntos2 (Node *arrel){
    printf("arrel->heu:%d\n",arrel->heu);
    for (int i=0;i<arrel->n_fills;i++){
        printf("arrel->fills[%d]->heu:%d\n",i,arrel->fills[i]->heu);
        for (int j=0;j<arrel->fills[i]->n_fills;j++){
            printf("arrel->fills[%d]->fills[%d]->heu:%d\n",i,j,arrel->fills[i]->fills[j]->heu);
            for (int k=0;k<arrel->fills[i]->fills[j]->n_fills;k++){
                printf("arrel->fills[%d]->fills[%d]->fills[%d]->heu:%d\n",i,j,k,arrel->fills[i]->fills[j]->fills[k]->heu);
                for (int l=0;l<arrel->fills[i]->fills[j]->fills[k]->n_fills;l++){
                    printf("arrel->fills[%d]->fills[%d]->fills[%d]->fills[%d]->heu:%d\n",i,j,k,l,arrel->fills[i]->fills[j]->fills[k]->fills[l]->heu);
                }
            }
        }
    }
}
