#include "hilo.h"
#include <stdio.h>
#include <unistd.h>
#include "celda.h"

// void imprimirLaberinto(Celda *laberinto[100][100], int filas, int columnas) {
//     for (int i = 0; i < filas; i++) {
//         for (int j = 0; j < columnas; j++) {
//             printf("%c ", laberinto[i][j]->caracter);
//         }
//         printf("\n");
//     }
// }

int accionMovimiento(Celda *laberinto[100][100], AtributosHilo *hilo){
    int termina = 0;
    switch (laberinto[hilo->posFila][hilo->posColumna]->caracter)
    {
    case '1':
        laberinto[hilo->posFila][hilo->posColumna]->caracter = 'R';
        break;
    
    case '/':
        laberinto[hilo->posFila][hilo->posColumna]->caracter = 'S';
        termina = 1;
        break;

    case '*':
        termina = 1;
        break;

    default:
        break;
    }

    return termina;
}

void movimientoHilo(Celda *laberinto[100][100], AtributosHilo *hilo){
    switch (hilo->direccion)
    {
    case 'A':
        hilo->posFila++;
        break;

    case 'a':
        hilo->posFila--;
        break;
    
    case 'i':
        hilo->posColumna++;
        break;

    case 'd':
        hilo->posColumna--;
        break;
    
    default:
        break;
    }
    accionMovimiento(laberinto, hilo);
}

// Implementación de la rutina del hilo
void *rutinaHilo(void *arg) {
    Celda *laberinto[100][100] = (Celda *)arg;
    printf("Laberinto:\n");
    //imprimirLaberinto(laberinto, 10, 10);
    AtributosHilo nuevoHilo;
    nuevoHilo.direccion = 'a';
    nuevoHilo.posFila = 0;
    nuevoHilo.posColumna = 0;
    nuevoHilo.celdasRecorridas = 0;

    int termina;
    while (0==0){
        termina = movimientoHilo(laberinto, nuevoHilo);
        if (termina)
            return 0
        sleep(2);
        imprimirLaberinto(laberinto, 10, 10)
    }
    
}



// void finHilo(void *arg){
//     // Convertir el argumento a un puntero de la estructura
//     Hilo *atributos = (Hilo *)arg;

    
    
//     // Acceder a los atributos
//     printf("Celdas Recorridas: %d\n", atributos->celdasRecorridas);
//     printf("Dirección: %c\n", atributos->direccion);
//     return NULL;
// }


