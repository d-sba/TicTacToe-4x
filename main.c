#include<stdio.h>
#include<stdlib.h>

#include "funcionesJuego.h"

int main()
{
    int t[N][N];
    iniciar(t);


    if (elegirModo(t)==1){
        system("cls");
        Jugs(t);   //modo dos jugadores
    }else{
        system("cls");
        CPU(t);    //modo contra la CPU
    }

    return 0;
}
