//87 % de almacenamiento usado … Si te quedas sin espacio, no podrás crear, editar ni subir archivos. Disfruta de 100 GB de almacenamiento por ₡1 090,00 ₡275,00 al mes durante 3 meses.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "celda.h"
//#include "hilo.h"
#include <pthread.h>
#include <unistd.h>

#define MAX_FILAS 100
#define MAX_COLUMNAS 100

typedef struct {
    Celda *laberinto;
    char direccion;
    int posFila;
    int posColumna;
    int celdasRecorridas;
    int filasLab;
    int columnasLab;
} Args;

typedef struct {
    int celdasRecorridas;
    char direccion;
    int posFila;
    int posColumna;
} AtributosHilo;

void imprimirLaberinto(Celda laberinto[MAX_FILAS][MAX_COLUMNAS], int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%c ", laberinto[i][j].caracter);
        }
        printf("\n");
    }
}

void movimientoHilo(AtributosHilo *hilo){
    switch (hilo->direccion)
    {
    case 'A':
        hilo->posFila--;
        break;

    case 'a':
        hilo->posFila++;
        break;
    
    case 'i':
        hilo->posColumna--;
        break;

    case 'd':
        hilo->posColumna++;
        break;
    
    default:
        break;
    }
}

int recorrerCelda(Celda laberinto[MAX_FILAS][MAX_COLUMNAS], AtributosHilo *hilo){
    int termina = 0;
    switch (laberinto[hilo->posFila][hilo->posColumna].caracter)
    {
    case '1':
        laberinto[hilo->posFila][hilo->posColumna].caracter = 'R';
        hilo->celdasRecorridas++;
        break;
    
    case '/':
        laberinto[hilo->posFila][hilo->posColumna].caracter = 'S';
        hilo->celdasRecorridas++;
        return 2;

    case '*':
        return 1;

    default:
        break;
    }
    movimientoHilo(hilo);
    return 0;
}

void *rutinaHilo(void *arg);

void analizarCelda(Celda laberinto[MAX_FILAS][MAX_COLUMNAS], AtributosHilo *hilo){
    int fila = hilo->posFila;
    int col = hilo->posColumna;
    int celdas = hilo->celdasRecorridas;
    //printf("%d",hilo->celdasRecorridas);
    // Analiza arriba de la celda
    if (hilo->direccion != 'A' && fila - 1 >= 0 && laberinto[fila - 1][col].caracter == '1'){
        pthread_t hilo;
        Args misArgs = {laberinto, 'A', fila, col, celdas, 10, 10};
        pthread_create(&hilo, NULL, rutinaHilo, (void *) &misArgs);
        pthread_join(hilo, NULL);
    }
    // Analiza abajo de la celda
    if (hilo->direccion != 'a' && fila + 1 < 10 && laberinto[fila + 1][col].caracter == '1'){
        pthread_t hilo;
        Args misArgs = {laberinto, 'a', fila, col, celdas, 10, 10};
        pthread_create(&hilo, NULL, rutinaHilo, (void *) &misArgs);
        pthread_join(hilo, NULL);
    }
    // Analiza a la izquierda de la celda
    if (hilo->direccion != 'i' && col - 1 >= 0 && laberinto[fila][col - 1].caracter == '1'){
        pthread_t hilo;
        Args misArgs = {laberinto, 'i', fila, col, celdas, 10, 10};
        pthread_create(&hilo, NULL, rutinaHilo, (void *) &misArgs);
        pthread_join(hilo, NULL);
    }
    // Analiza a la derecha de la celda
    if (hilo->direccion != 'd' && col + 1 < 10 && laberinto[fila][col + 1].caracter == '1'){
        pthread_t hilo;
        Args misArgs = {laberinto, 'd', fila, col, celdas, 10, 10};
        pthread_create(&hilo, NULL, rutinaHilo, (void *) &misArgs);
        pthread_join(hilo, NULL);
    }
}

// Implementación de la rutina del hilo
void *rutinaHilo(void *arg) {
    Args * args = (Args *)arg;
    
    printf("Entra:\n");
    imprimirLaberinto(args->laberinto, args->filasLab, args->columnasLab);
    
    AtributosHilo nuevoHilo;
    AtributosHilo *ptrHilo = &nuevoHilo;
    ptrHilo->direccion = args->direccion;
    ptrHilo->posFila = args->posFila;
    ptrHilo->posColumna = args->posColumna;
    ptrHilo->celdasRecorridas = args->celdasRecorridas;

    int termina;
    while (0==0){
        analizarCelda(args->laberinto, ptrHilo);
        termina = recorrerCelda(args->laberinto, &nuevoHilo);
        if (termina == 2){
            printf("HILO TERMINADO\nCantidad de Celdas Recorridas: %d\nEl hilo salio exitosamente",ptrHilo->celdasRecorridas);
            return 0;
        }
        sleep(5);
        system("clear");
        imprimirLaberinto(args->laberinto, args->filasLab, args->columnasLab);
    }
    
}

int main() {
    const char *nombreArchivo = "../Ejemplos laberintos/lab1.txt";
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

    int pos[2] = {0,0};

    pthread_t hilo;
    char direccion = 'a';
    int atributos[3] = {0,0,0};
    int dimensiones[2] = {filasLab, columnasLab};
    //int *ptrAtributos = 
    
    Args misArgs = {laberinto, direccion, 0, 0, 0, filasLab, columnasLab};
    //printf("Laberinto Prueba:\n");
    //imprimirLaberinto(misArgs.laberinto, filasLab, columnasLab);
    pthread_create(&hilo, NULL, rutinaHilo, (void *) &misArgs);
    pthread_join(hilo, NULL);

    return 0;
}