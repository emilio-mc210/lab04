#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/*
* Funcion para encontrar la longitud de la diagonal de 1s mas larga
* en una matriz cuadrada.
*
* Params:
* - int **matriz: Puntero a la matriz cuadrada de enteros.
* - int tamano: Tamano de la matriz (filas y columnas).
* - int *resultado: Puntero donde se devuelve el valor encontrado.
*
* Retorno:
* - No se regresa un valor, se modifica el valor en ’resultado’
*/
void encontrar_diagonal_mas_larga(int **matriz, int tamano, int *resultado) {
    *resultado = 0;
    int diagonal = 0;
    int i,j,k;

    //Revisar diagonales hacia la esquina inferior izquierda (de izquierda a derecha)
    //Ciclo que revisa diagonales desde la superior izquierda a la central
    for(k=0; k<tamano; k++){
        for(i=0, j=k; j>=0; i++, j--){
            if(*(*(matriz + i) + j) == 1){
                diagonal++;
                if(diagonal > *resultado){
                    *resultado = diagonal;
                }
            }
            else{
                diagonal = 0;
            }
        }
    }
    //Diagonales a la derecha de la central hasta la esquina inferior derecha
    for(k=1; k<tamano; k++){
        for(i=k, j=tamano-1; i<tamano; i++, j--){ 
            if(*(*(matriz + i) + j) == 1){
                diagonal++;
                if(diagonal > *resultado){
                    *resultado = diagonal;
                }
            }
            else{
                diagonal = 0;
            }
        }
    }
}

/*
* Funcion para reservar la matriz en memoria dinamica.

* Params:
* - int ***matriz: Doble puntero a la matriz cuadrada de enteros.
* - int tamano: Tamano de la matriz (filas y columnas).
*
* Retorno:
* - No se regresa un valor. Reserva memoria para la matriz.
*/
void reservar_matriz(int ***matriz, int tamano) {
    //Cantidad de filas
    *matriz = (int **)malloc(tamano * sizeof(int *));
    for(int i=0; i<tamano; i++){
        //Tamano de cada fila
        *(*matriz + i) = (int *)malloc(tamano * sizeof(int)); 
    }
}

/*
* Funcion para llenar la matriz con numeros aleatorios (0s y 1s).

* Params:
* - int **matriz: Puntero a la matriz cuadrada de enteros.
* - int tamano: Tamano de la matriz (filas y columnas).
*
* Retorno:
 - No se regresa un valor. Llena la matriz con valores aleatorios.
*/
void llenar_matriz(int **matriz, int tamano) {
    if(!matriz){
        printf("Error: puntero matriz invalido\n");
        return;
    }

    srand(time(NULL));
    for(int i=0; i<tamano; i++){
        for(int j=0; j<tamano; j++){
            *(*(matriz + i) + j) = rand() % 2;
        }
    }
}

/*
* Funcion para imprimir la matriz.
*
* Params:
* - int **matriz: Puntero a la matriz cuadrada de enteros.
* - int tamano: Tamano de la matriz (filas y columnas).
*
* Retorno:
* - No se regresa un valor. Imprime la matriz en stdout.
*/
void imprimir_matriz(int **matriz, int tamano) {
    printf("\nMatriz %dx%d:\n", tamano, tamano);
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            printf("%d ", *(*(matriz + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

/*
* Funcion para aumentar o disminuir el tamano de la matriz de forma dinamica.
*
* Params:
* - int ***matriz: Puntero a la matriz cuadrada de enteros.
* - int nuevo: Nuevo tamano de la matriz.
* - int viejo: Tamano inicial de la matriz.
*
* Retorno:
* - No se regresa un valor. Modifica la matriz.
*/
void realocar_matriz(int ***matriz, int nuevo, int viejo) {
    //Liberar exceso de filas si viejo>nuevo
    for(int i=nuevo; i<viejo; i++){
        free(*(*matriz + i));
    }

    int **temp = realloc(*matriz, nuevo * sizeof(int *));
    for(int i=0; i<nuevo; i++){
        *(temp + i) = realloc(*(temp + i), nuevo * sizeof(int));
    }
    *matriz = temp;

    //Lleno el resto de la matriz si nuevo>viejo
    //Parte nueva a la derecha
    for(int i = 0; i<nuevo; i++){
        for(int j=viejo; j<nuevo; j++){
            *(*(*matriz + i)+ j) = rand() % 2;
        }
    }
    //Parte nueva debajo
    for(int i = viejo; i<nuevo; i++){
        for(int j=0; j<viejo; j++){
            *(*(*matriz + i)+ j) = rand() % 2;
        }
    }
    
}

/*
* Funcion para liberar la memoria asignada a la matriz.
*
* Params:
* - int **matriz: Puntero a la matriz cuadrada de enteros.
* - int viejo: Tamano inicial de la matriz(filas y columnas).
* - int nuevo: Nuevo tamano de la matriz.
*
* Retorno:
* - No se regresa un valor. Libera la memoria utilizada.
*/
void liberar_matriz(int **matriz, int tamano) {
    for(int i=0; i<tamano; i++){
        free(matriz[i]);
    }
    free(matriz);
}

int main() {
    int tamano = 0, diagonal_mas_larga;
    int **matriz = NULL;

    //Obtener el tamano
    do{
        printf("\nDigite el tamano de la matriz: ");
        scanf("%i", &tamano);
    }
    while (tamano <= 0);

    //Reservar la matriz
    reservar_matriz(&matriz, tamano);

    //Llenar matriz
    llenar_matriz(matriz, tamano);
    imprimir_matriz(matriz, tamano);

    //Diagonal mas larga
    encontrar_diagonal_mas_larga(matriz, tamano, &diagonal_mas_larga);
    printf("La secuencia de 1s mas grande es: %d\n", diagonal_mas_larga);

    //Realocar matriz
    int t_nuevo = 0;
    do{
        printf("\nDigite el nuevo tamano de la matriz: ");
        scanf("%i", &t_nuevo);
    }
    while (t_nuevo <= 0);

    realocar_matriz(&matriz, t_nuevo, tamano);
    imprimir_matriz(matriz, t_nuevo);

    //Liberar memoria
    liberar_matriz(matriz, t_nuevo);
    
    return 0;
}