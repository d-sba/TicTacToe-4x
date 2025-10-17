#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#include "funcionesJuego.h"
#include "miniMax.h"
#include"records.h"


/**< Funciones del tablero */
void iniciar (int tauler[N][N]){
    for (int i=0;i<N;i++)
    {
        for (int j=0;j<N;j++){
            tauler[i][j]=0;
        }
    }
}

void dibujarTablero (int tauler[N][N]){
    printf("\n        ----------------------------------\n");
    for (int i=0;i<N;i++)
    {
        printf("        |");
        for (int j=0;j<N;j++)
        {
            if (tauler[i][j]==0)
            {
                printf("   |");
            } else if (tauler[i][j]==1){
                printf(" X |");
            }else
            {
                printf(" O |");
            }
        }
        printf("    \n        ----------------------------------\n");
    }
    printf("\n        | ^ | ^ | ^ | ^ | ^ | ^ | ^ | ^ |");
    printf("    \n        ----------------------------------\n");
    printf("        | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |");
    printf("    \n        ----------------------------------\n");
    printf("\n");
}


void dibujarTableroGanador(int tauler[N][N],int jug, int *iAux, int *jAux,int *dir){
printf("\n        ----------------------------------\n");
    for (int i=0;i<N;i++)
    {
        printf("        |");
        for (int j=0;j<N;j++)
        {
            if (tauler[i][j]==0){
                printf("   |");
             }else if (tauler[i][j]==jug && i==*iAux && j==*jAux){
                if (jug==1) {printf("\x1b[41m X \x1B[40m|");}
                else {printf("\x1b[41m O \x1B[40m|");}
                if ((*dir)==1) *jAux+=1;
                if ((*dir)==2) *iAux+=1;
                if ((*dir)==3) {*iAux+=1;*jAux+=1;}
                if ((*dir)==4) {*iAux+=1;*jAux-=1;}
            }else{
                if (tauler[i][j]==1) printf(" X |");
                else printf(" O |");
            }
        }
        printf("    \n        ----------------------------------\n");
    }
    printf("\n        | ^ | ^ | ^ | ^ | ^ | ^ | ^ | ^ |");
    printf("    \n        ----------------------------------\n");
    printf("        | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |");
    printf("    \n        ----------------------------------\n");
    printf("\n");
}


void copiaMatriz(int copia[N][N], int original[N][N]){
    for (int i=0;i<N;i++)
    {
        for (int j=0;j<N;j++)
        {
            copia[i][j]=original[i][j];
        }
    }
}

void espejo(int tauler[N][N]){
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if (tauler[i][j]==1){
                tauler[i][j]=2;
            }else if (tauler[i][j]==2){
                tauler[i][j]=1;
            }
        }
    }
}

void destruirColumna (int tauler[N][N],int n){
    for (int i=0;i<N;i++) {
        tauler[i][n]=0;
    }
}




/**< Funciones relacionadas con el estado del tablero */
int columnaLlena(int tauler[N][N], int opc){
    if (tauler[0][opc]!=0)     //antes tenia puesto opc-1, acordarme que al meter el
    {                                     //argumento opc en esta funcion tiene que entrar con un -1
        return 1;                         //por lo menos en el turno del jugador
    }else {
        return 0;
    }
}

int contarColumnasLibres(int tauler[N][N]){
    int contador=0;
    for (int i=0;i<N;i++)
    {
        if (columnaLlena(tauler,i)!=1){
            contador ++;
        }
    }
    return contador;
}

int empate (int tauler [N][N]){
    int aux=0;
    for (int j=0;j<N;j++){
        if (tauler[0][j]!=0){
            aux++;
        }
    }
    if (aux==8){
        return 1;
    }else return 0;
}

void tirar(int tauler[N][N], int col, int jug){
    for (int i=0;i<N;i++){
        if (tauler[(N-1)-i][col]==0){
            tauler[(N-1)-i][col]=jug;
            return ;
        }
    }
}

int ganador(int tauler[N][N],int jug){
    //HORIZONTAL
    for (int i=0;i<N;i++){
        for (int j=0;j<(N-3);j++){
            if (tauler[i][j]==jug){
                if (tauler[i][j+1]==jug){
                    if (tauler[i][j+2]==jug){
                        if(tauler[i][j+3]==jug){
                            return 1;
                        }
                    }
                }
            }
        }
    }

    //VERTICAL
    for (int i=0;i<(N-3);i++){
        for (int j=0;j<N;j++){
            if(tauler[i][j]==jug){
                if(tauler[i+1][j]==jug){
                    if(tauler[i+2][j]==jug){
                        if (tauler[i+3][j]==jug){
                            return 1;
                        }
                    }
                }
            }
        }
    }

    //DIAG.DCHA
    for (int i=0;i<(N-3); i++){
        for (int j=0;j<(N-3);j++){
            if (tauler[i][j]==jug){
                if(tauler[i+1][j+1]==jug){
                    if(tauler[i+2][j+2]==jug){
                        if(tauler[i+3][j+3]==jug){
                            return 1;
                        }
                    }
                }
            }
        }
    }

    //DIAG.IZQ
    for (int i=0;i<(N-3);i++){
        for (int j=3;j<N;j++){
           if (tauler[i][j]==jug){
                if(tauler[i+1][j-1]==jug){
                    if(tauler[i+2][j-2]==jug){
                        if(tauler[i+3][j-3]==jug){
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void ganador2(int tauler[N][N],int jug, int* iAux, int* jAux, int* dir){
    //HORIZONTAL
    for (int i=0;i<N;i++){
        for (int j=0;j<(N-3);j++){
            if (tauler[i][j]==jug){
                if (tauler[i][j+1]==jug){
                    if (tauler[i][j+2]==jug){
                        if(tauler[i][j+3]==jug){

                            *iAux=i;
                            *jAux=j;
                            *dir=1;
                            return;
                        }
                    }
                }
            }
        }
    }

    //VERTICAL
    for (int i=0;i<(N-3);i++){
        for (int j=0;j<N;j++){
            if(tauler[i][j]==jug){
                if(tauler[i+1][j]==jug){
                    if(tauler[i+2][j]==jug){
                        if (tauler[i+3][j]==jug){
                            *iAux=i;
                            *jAux=j;
                            *dir=2;
                            return;
                        }
                    }
                }
            }
        }
    }

    //DIAG.DCHA
    for (int i=0;i<(N-3); i++){
        for (int j=0;j<(N-3);j++){
            if (tauler[i][j]==jug){
                if(tauler[i+1][j+1]==jug){
                    if(tauler[i+2][j+2]==jug){
                        if(tauler[i+3][j+3]==jug){
                            *iAux=i;
                            *jAux=j;
                            *dir=3;
                            return;
                        }
                    }
                }
            }
        }
    }

    //DIAG.IZQ
    for (int i=0;i<(N-3);i++){
        for (int j=3;j<N;j++){
           if (tauler[i][j]==jug){
                if(tauler[i+1][j-1]==jug){
                    if(tauler[i+2][j-2]==jug){
                        if(tauler[i+3][j-3]==jug){
                            *iAux=i;
                            *jAux=j;
                            *dir=4;
                            return;
                        }
                    }
                }
            }
        }
    }
}


/**< Jugadas */
void jugadaHumano(int tauler[N][N], int jug){
    int opcInt;
    printf("Jugador %d, elige donde tirar la ficha: ", jug);

    while(scanf("%d", &opcInt) != 1){    //este scanf me devuelve un 1 sii lee un entero
        while(getchar() != '\n');
        printf("Por favor, ingresa un numero: ");
    }

    if (opcInt < 1 || opcInt > N){
        printf("Fuera de rango\n");
        jugadaHumano(tauler, jug);
    } else if (columnaLlena(tauler, opcInt - 1) == 1){
        printf("Columna llena\n");
        jugadaHumano(tauler, jug);
    } else{
        tirar(tauler, opcInt-1, jug);
    }
}


void jugadaOrdenador(int tauler[N][N], int dificultad, int *ultimCol){
    //Variables para confirmar el correcto borrado del arbol
    int mallocs=3;  //empiezo ya con los 3 del creaarrel
    int frees=0;
    Node *arrel=creaArrel(tauler);
    creaArbre(arrel,0,dificultad,&mallocs);

    *ultimCol=miniMax(arrel,dificultad);
    tirar(tauler,*ultimCol,ord);
    borrarArbre(arrel, &frees);
    //printf("Hemos hecho %d mallocs y %d frees", mallocs,frees);
}


/**< Modos de juego */
int elegirModo(){
    int mod=0;


    printf(" 4    4     EEEEEEEEE   RRRRRRR\n");
    printf(" 4    4     E           R      RR       -------------\n");
    printf(" 4    4     E           R        R      | X |   | X |\n");
    printf(" 4    4     E           R      RR       -------------\n");
    printf(" 444444     EEEEEEEEE   RRRRRRR         | O | X | O |\n");
    printf("      4     E           R       R       -------------\n");
    printf("      4     E           R        R      | O | O | X |\n");
    printf("      4     E           R         R     -------------\n");
    printf("      4     EEEEEEEEE   R          R\n");


    printf("\n\n");
    printf("       Seleciona modo de juego:\n");
    printf("        1- Dos jugadores\n");
    printf("        2- Jugar contra la CPU\n");
    printf("->");

    do{
        while(scanf("%d", &mod) != 1){    //este scanf me devuelve un 1 sii lee un entero
            while(getchar() != '\n');
            printf("Por favor, ingresa un numero: ");
        }

        if (mod<0 || mod>2 || mod==0){
            printf("Opcion fuera de rango, por favor ingresa un numero: ");
        }
    }while(mod<1 || mod>2);

    return mod;
}

void fraseModoJuego(int dif,int com){
    if (dif==1){
        printf("       Modo facil ");
        if (com==0) printf("sin comodines\n");
        if (com==1) printf("con el comodin espejo");
        if (com==2) printf("con el comodin destruye columnas");
    }else if (dif==2){
        printf("       Dificultad media ");
        if (com==0) printf("sin comodines\n");
        if (com==1) printf("con el comodin espejo");
        if (com==2) printf("con el comodin destruye columnas");
    }else{
        printf("       Modo dificil ");
        if (com==0) printf("sin comodines\n");
        if (com==1) printf("con el comodin espejo");
        if (com==2) printf("con el comodin destruye columnas");
    }
}


void Jugs (int tauler[N][N]){
    int com=comodines();
    int iAux=0,jAux=0,dir=0;
    int com1=com,com2=com;

    do{
        printf("          Jugador contra Jugador\n");
        dibujarTablero(tauler);

        if (empate(tauler)==1){
            printf("No se puede continuar la partida, el tablero está lleno");
            return;
        }

        jugadaHumano(tauler,1);
        if (ganador(tauler,1)==1){
            system("cls");
            printf("        ENHORABUENA JUGADOR 1, HAS GANADO\n");
            ganador2(tauler,1,&iAux,&jAux,&dir);
            dibujarTableroGanador(tauler,1,&iAux,&jAux,&dir);
            return;
        }
        if (com1==2) {comodinColumna(tauler,&com1);}
        system("cls");

        printf("        Jugador contra Jugador\n");
        dibujarTablero(tauler);
        jugadaHumano(tauler,2);
        if (ganador(tauler,2)==1){
            system("cls");
            printf("        ENHORABUENA JUGADOR 2, HAS GANADO\n");
            ganador2(tauler,2,&iAux,&jAux,&dir);
            dibujarTableroGanador(tauler,2,&iAux,&jAux,&dir);
            return;
        }
        if (com2==2) {comodinColumna(tauler,&com2);}
        system("cls");

        if (com==1) {comodinEspejo(tauler,&com);}
    }while (ganador(tauler,1)!=1 && ganador(tauler,ord)!=1);
}




void CPU (int tauler[N][N]){
    int dif=dificultad();
    int com=comodines();
    int cont=0;
    int iAux=0,jAux=0,dir=0;
    int ultimCol;

    do{
        fraseModoJuego(dif,com);
        dibujarTablero(tauler);

        if (cont!=0) {
                printf("He tirado en la columna %d\n", ultimCol+1);
                if (com==2) {comodinColumna(tauler,&com);system("cls");fraseModoJuego(dif,com);dibujarTablero(tauler);}
        }

        if (empate(tauler)==1){
            printf("No se puede continuar la partida, el tablero está lleno");
            return;
        }

        //TURNO HUMANO
        jugadaHumano(tauler,hum);
        cont+=1;
        if (ganador(tauler,hum)==1){
            system("cls");
            printf("          ENHORABUENA, HAS GANADO EN %d JUGADAS\n", cont);
            ganador2(tauler,hum,&iAux,&jAux,&dir);
            dibujarTableroGanador(tauler,hum,&iAux,&jAux,&dir);
            records(cont,dif);
            return;
        }

        //TURNO ORDENADOR
        jugadaOrdenador(tauler,dif,&ultimCol);
        if (ganador(tauler,ord)==1){
            system("cls");
            printf("\n\n           LO SIENTO, HAS PERDIDO");
            ganador2(tauler,ord,&iAux,&jAux,&dir);
            dibujarTableroGanador(tauler,ord,&iAux,&jAux,&dir);
            return;
        }


        //COMODINES
        if (com==1) {comodinEspejo(tauler,&com);}
        system("cls");
    }while (ganador(tauler,hum)!=1 && ganador(tauler,ord)!=1);
}




/**< Extras */
int dificultad(){
    int dificultad;
    printf("Selecciona el nivel de dificultad\n");
    printf("1- Facil\n");
    printf("2- Medio\n");
    printf("3- Dificil\n");
    printf("->");

    do{
        while(scanf("%d", &dificultad) != 1){    //este scanf me devuelve un 1 sii lee un entero
            while(getchar() != '\n');
            printf("Por favor, ingresa un numero: ");
        }

        if (dificultad<0 || dificultad>3 || dificultad==0){
            printf("Opcion fuera de rango, por favor ingresa un numero: ");
        }
    }while(dificultad<0 || dificultad>3 || dificultad==0);

    system("cls");
    return dificultad;
}

int numAleat(int n){
    srand(time(NULL));
    int ind =rand()%n;
    return ind;
}

int comodines(){
    int com;
    printf("Quieres jugar con algun comodin? 1_SI || 0_NO\n");
    printf("->");

     do{
        while(scanf("%d", &com) != 1){    //este scanf me devuelve un 1 sii lee un entero
            while(getchar() != '\n');
            printf("Por favor, ingresa un numero: ");
        }

        if (com<0 || com>1){
            printf("Opcion fuera de rango, por favor ingresa un numero: ");
        }
    }while(com<0 || com>1);

    if (com==0){system("cls"); return 0;}
    else {
        system("cls");
        printf("Con cual?\n");
        printf("1-Espejo (cambia las X por O)\n");
        printf("2-Destruye columna\n");
        printf("->");

        do{
            while(scanf("%d", &com) != 1){    //este scanf me devuelve un 1 sii lee un entero
                while(getchar() != '\n');
                printf("Por favor, ingresa un numero: ");
            }

            if (com<=0 || com>2){
                printf("Opcion fuera de rango, por favor ingresa un numero: ");
            }
        }while(com<=0 || com>2);
    }
    system("cls");

    return com;
}

void comodinEspejo(int tauler[N][N],int *com){
    if(*com!=0){
            if (numAleat(10)==7){
                printf("                    SE ACTIVA EL COMODIN ESPEJO\n");
                while(getchar() != '\n');
                espejo(tauler);
                *com=0;
            }
        }
}

void comodinColumna(int tauler[N][N],int *com){
    int n;
    printf("Quieres usar el comodin columna? 1_SI || 0_NO\n");
    printf("->");
    scanf("%d", &n);

    if (n==1){
        system("cls");
        printf("           DESTRUCCION\n");
        dibujarTablero(tauler);
        do{
        printf("Que columna eliminamos?");
        scanf("%d", &n);
        }while(n<0 || n>9);
        destruirColumna(tauler,n-1);
        *com=0;
    }
}
