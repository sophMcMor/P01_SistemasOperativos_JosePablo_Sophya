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

int recorrerCelda(Celda laberinto[100][100], AtributosHilo *hilo){
    int termina = 0;
    printf("POSX:%d, POSY:%d, CARACTER:%c\n",hilo->posFila, hilo->posColumna, laberinto[hilo->posFila][hilo->posColumna].caracter);
    switch (laberinto[hilo->posFila][hilo->posColumna].caracter)
    {
    case '1':
        printf("ENTRO1\n");
        laberinto[hilo->posFila][hilo->posColumna].caracter = 'R';
        break;
    
    case '/':
        printf("ENTRO2\n");
        laberinto[hilo->posFila][hilo->posColumna].caracter = 'S';
        return 1;

    case '*':
        printf("ENTRO3\n");
        return 1;

    default:
        printf("ENTRO4\n");
        break;
    }
    movimientoHilo(hilo);
    printf("POSX:%d, POSY:%d, CARACTER:%c\n",hilo->posFila, hilo->posColumna, laberinto[hilo->posFila][hilo->posColumna].caracter);
    return 0;
}

// Implementación de la rutina del hilo
void *rutinaHilo(void *arg) {
    Celda (*laberinto)[100] = (Celda (*)[100])arg;
    
    printf("Laberinto2:\n");
    imprimirLaberinto(laberinto, 10, 10);
    AtributosHilo nuevoHilo;
    AtributosHilo *ptrHilo = &nuevoHilo;
    ptrHilo->direccion = 'a';
    ptrHilo->posFila = 0;
    ptrHilo->posColumna = 0;
    ptrHilo->celdasRecorridas = 0;

    int termina;
    while (0==0){
        termina = recorrerCelda(laberinto, &nuevoHilo);
        if (termina)
            return 0;
        sleep(2);
        system("cls");
        imprimirLaberinto(laberinto, 10, 10);
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

    pthread_create(&hilo, NULL, rutinaHilo, (void *) &laberinto);
    pthread_join(hilo, NULL);
    // while (0==0){
    //     Hilo nuevoHilo;
    //     nuevoHilo.direccion = 'a';
    //     nuevoHilo.posFila = pos[0];
    //     nuevoHilo.posColumna = pos[1];
    //     nuevoHilo.celdasRecorridas = 0;

    //     sleep(2);
    //     system("clear");
    //     salio = movimientoHilo(laberinto, filasLab, columnasLab, nuevoHilo);
    //     imprimirLaberinto(laberinto, filasLab, columnasLab);

    //     if (salio)
    //         break;
    //}

    return 0;
}