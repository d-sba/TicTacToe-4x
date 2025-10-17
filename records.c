#include "records.h"



//algoritmo de burbuja para ordenar (las puntuaciones mas altas van "flotando" hacia arriba
void bubbleSort(Record arr[], int n) {
    int i, j;
    Record temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].puntuacion > arr[j + 1].puntuacion) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void createFileIfNotExist1() {
    FILE *file = fopen("recordsFaciles.txt", "a+");
    if (file == NULL) {
        printf("No se pudo crear el archivo.");
        exit(1);
    }
    fclose(file);
}

void createFileIfNotExist2() {
    FILE *file = fopen("recordsMedios.txt", "a+");
    if (file == NULL) {
        printf("No se pudo crear el archivo.");
        exit(1);
    }
    fclose(file);
}

void createFileIfNotExist3() {
    FILE *file = fopen("recordsDificiles.txt", "a+");
    if (file == NULL) {
        printf("No se pudo crear el archivo.");
        exit(1);
    }
    fclose(file);
}

void updateRecords1(int puntuacion) {
    Record records[TOP];
    int cont = 0;

    createFileIfNotExist1();

    FILE *file = fopen("recordsFaciles.txt", "r+"); // Abrir archivo en modo lectura/escritura
    if (file == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }

    // Lee los records en el archivo y los va guardando en el array d estructuras
    while (fscanf(file, "%s %d", records[cont].nombre, &records[cont].puntuacion) == 2 && cont < TOP) {
        cont++;
    }

    // Rellenar el top con las 10 primeras puntuaciones
    if (cont < TOP) {
        char nuevoNombre[TOP];
        printf("Ingresa tu nombre (longitud maxima %d caracteres): ", LONGITUD_NOMBRE);
        scanf("%s", nuevoNombre);

        strcpy(records[cont].nombre, nuevoNombre);
        records[cont].puntuacion = puntuacion;
        cont++;

        bubbleSort(records, cont);

        printf("\nTop de puntuaciones modo facil:\n");
        for (int i = 0; i <  cont; i++) {
            printf("%d. %s - %d\n", i + 1, records[i].nombre, records[i].puntuacion);
        }

        // Mover el cursor al inicio del archivo para escribir los datos ordenados
        rewind(file);

        // Escribir los datos ordenados en el archivo
        for (int i = 0; i < cont; i++) {
            fprintf(file, "%s %d\n", records[i].nombre, records[i].puntuacion);
        }

        fclose(file);
        return;
    }

    bubbleSort(records, TOP);

    //si ya esta lleno el top y la nueva puntuacion entra, borra la puntuacion 10
    if (puntuacion < records[TOP - 1].puntuacion) {
        char nuevoNombre[LONGITUD_NOMBRE];
        printf("Enhorabuena!! Has entrado en el top 10. Ingresa tu nombre (longitud maxima %d caracteres): ", LONGITUD_NOMBRE);
        scanf("%s", nuevoNombre);

        // Sustituye la posicion 10
        strcpy(records[TOP - 1].nombre, nuevoNombre);
        records[TOP - 1].puntuacion = puntuacion;

        // Reordena
        bubbleSort(records, TOP);

        rewind(file);

        // Escribir los datos ordenados en el archivo
        for (int i = 0; i < TOP; i++) {
            fprintf(file, "%s %d\n", records[i].nombre, records[i].puntuacion);
        }

        fclose(file);
    } else {
        printf("Tu puntuacion no entra en el top 10.\n");
        printf("\nMODO FACIL ; Top 10:\n");
        for (int i = 0; i < TOP; i++) {
        printf("%d. %s - %d\n", i + 1, records[i].nombre, records[i].puntuacion);
    }
        fclose(file);
        return;
    }

    printf("\nMODO FACIL ; Top 10:\n");
    for (int i = 0; i < TOP; i++) {
        printf("%d. %s - %d\n", i + 1, records[i].nombre, records[i].puntuacion);
    }
}


void updateRecords2(int puntuacion) {
    Record records[TOP];
    int cont = 0;

    createFileIfNotExist2();

    FILE *file = fopen("recordsMedios.txt", "r+");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }

    while (fscanf(file, "%s %d", records[cont].nombre, &records[cont].puntuacion) == 2 && cont < TOP) {
        cont++;
    }

    if (cont < TOP) {
        char nuevoNombre[TOP];
        printf("Ingresa tu nombre (longitud maxima %d caracteres): ", LONGITUD_NOMBRE);
        scanf("%s", nuevoNombre);

        strcpy(records[cont].nombre, nuevoNombre);
        records[cont].puntuacion = puntuacion;
        cont++;

        bubbleSort(records, cont);

        printf("\nTop de puntuaciones dificultad media:\n");
        for (int i = 0; i <  cont; i++) {
            printf("%d. %s - %d\n", i + 1, records[i].nombre, records[i].puntuacion);
        }

        rewind(file);

        for (int i = 0; i < cont; i++) {
            fprintf(file, "%s %d\n", records[i].nombre, records[i].puntuacion);
        }

        fclose(file);
        return;
    }


    bubbleSort(records, TOP);

    if (puntuacion < records[TOP - 1].puntuacion) {
        char nuevoNombre[LONGITUD_NOMBRE];
        printf("Enhorabuena!! Has entrado en el top 10. Ingresa tu nombre (longitud maxima %d caracteres): ", LONGITUD_NOMBRE);
        scanf("%s", nuevoNombre);


        strcpy(records[TOP - 1].nombre, nuevoNombre);
        records[TOP - 1].puntuacion = puntuacion;


        bubbleSort(records, TOP);


        rewind(file);

        for (int i = 0; i < TOP; i++) {
            fprintf(file, "%s %d\n", records[i].nombre, records[i].puntuacion);
        }

        fclose(file);
    } else {
        printf("Tu puntuacion no entra en el top 10.\n");
        printf("\nDIFICULTAD MEDIA; Top 10:\n");
        for (int i = 0; i < TOP; i++) {
        printf("%d. %s - %d\n", i + 1, records[i].nombre, records[i].puntuacion);
    }
        fclose(file);
        return;
    }

    printf("\nDIFICULTAD MEDIA ; Top 10:\n");
    for (int i = 0; i < TOP; i++) {
        printf("%d. %s - %d\n", i + 1, records[i].nombre, records[i].puntuacion);
    }
}

void updateRecords3(int puntuacion) {
   Record records[TOP];
    int cont = 0;

    createFileIfNotExist3();

    FILE *file = fopen("recordsDificiles.txt", "r+");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }

    while (fscanf(file, "%s %d", records[cont].nombre, &records[cont].puntuacion) == 2 && cont < TOP) {
        cont++;
    }

    if (cont < TOP) {
        char nuevoNombre[TOP];
        printf("Ingresa tu nombre (longitud maxima %d caracteres): ", LONGITUD_NOMBRE);
        scanf("%s", nuevoNombre);

        strcpy(records[cont].nombre, nuevoNombre);
        records[cont].puntuacion = puntuacion;
        cont++;

        bubbleSort(records, cont);

        printf("\nTop de puntuaciones modo dificil:\n");
        for (int i = 0; i <  cont; i++) {
            printf("%d. %s - %d\n", i + 1, records[i].nombre, records[i].puntuacion);
        }


        rewind(file);


        for (int i = 0; i < cont; i++) {
            fprintf(file, "%s %d\n", records[i].nombre, records[i].puntuacion);
        }

        fclose(file);
        return;
    }


    bubbleSort(records, TOP);

    if (puntuacion < records[TOP - 1].puntuacion) {
        char nuevoNombre[LONGITUD_NOMBRE];
        printf("Enhorabuena!! Has entrado en el top 10. Ingresa tu nombre (longitud maxima %d caracteres): ", LONGITUD_NOMBRE);
        scanf("%s", nuevoNombre);


        strcpy(records[TOP - 1].nombre, nuevoNombre);
        records[TOP - 1].puntuacion = puntuacion;


        bubbleSort(records, TOP);

        rewind(file);


        for (int i = 0; i < TOP; i++) {
            fprintf(file, "%s %d\n", records[i].nombre, records[i].puntuacion);
        }

        fclose(file);
    } else {
        printf("Tu puntuacion no entra en el top 10.\n");

        printf("\nMODO DIFICIL ; Top 10:\n");
        for (int i = 0; i < TOP; i++) {
        printf("%d. %s - %d\n", i + 1, records[i].nombre, records[i].puntuacion);
    }
        fclose(file);
        return;
    }

    printf("\nMODO DIFICIL ; Top 10:\n");
    for (int i = 0; i < TOP; i++) {
        printf("%d. %s - %d\n", i + 1, records[i].nombre, records[i].puntuacion);
    }
}


void records (int puntuacion, int dif){
    if (dif==1) updateRecords1(puntuacion);
    if (dif==2) updateRecords2(puntuacion);
    if (dif==3) updateRecords3(puntuacion);
}

