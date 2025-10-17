#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOP 10
#define LONGITUD_NOMBRE 20

typedef struct record {
    char nombre[LONGITUD_NOMBRE];
    int puntuacion;
}Record;

void bubbleSort(Record arr[], int n);

void createFileIfNotExist1();
void createFileIfNotExist2();
void createFileIfNotExist3();

void updateRecords1(int newScore);
void updateRecords2(int newScore);
void updateRecords3(int newScore);

void records(int newScore, int dif);
