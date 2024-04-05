87 % de almacenamiento usado … Si te quedas sin espacio, no podrás crear, editar ni subir archivos. Disfruta de 100 GB de almacenamiento por ₡1 090,00 ₡275,00 al mes durante 3 meses.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "celda.h"

#define MAX_FILAS 100
#define MAX_COLUMNAS 100

void imprimirLaberinto(Celda laberinto[MAX_FILAS][MAX_COLUMNAS], int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%c ", laberinto[i][j].caracter);
        }
        printf("\n");
    }
}

int main() {
    const char *nombreArchivo = "/home/sophy/Desktop/P01_SistemasOperativos_JosePablo_Sophya-Sophy/Ejemplos laberintos/lab1.txt";
    FILE *archivo;
    char linea[100];
    int fila = 0;

    int filasLab;
    int columnasLab;

    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    if (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (sscanf(linea, "%d %d", &filasLab, &columnasLab) != 2) {
            printf("Error al obtener las dimensiones del laberinto.\n");
            fclose(archivo);
            return 1;
        }
        printf("Dimensiones del laberinto: filas=%d, columnas=%d\n", filasLab, columnasLab);
    } else {
        printf("Error: archivo vacío.\n");
        fclose(archivo);
        return 1;
    }

    Celda laberinto[MAX_FILAS][MAX_COLUMNAS];

    while (fgets(linea, sizeof(linea), archivo) != NULL && fila < filasLab) {
        for (int i = 0; i < columnasLab && i < strlen(linea); i++) {
            char caracter = linea[i];
            Celda nuevaCelda;
            if(caracter == ' '){
                nuevaCelda.caracter = '1';
            }
            else{
                nuevaCelda.caracter = caracter;
            }
            
            nuevaCelda.arriba = 0;
            nuevaCelda.abajo = 0;
            nuevaCelda.izquierda = 0;
            nuevaCelda.derecha = 0;
            laberinto[fila][i] = nuevaCelda;
        }
        fila++;
    }

    fclose(archivo);

    printf("Laberinto:\n");
    imprimirLaberinto(laberinto, filasLab, columnasLab);

    return 0;
}