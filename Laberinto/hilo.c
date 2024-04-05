#include "hilo.h"
#include <stdio.h>

// Implementación de la rutina del hilo
void *rutinaHilo(void *arg) {
    // Convertir el argumento a un puntero de la estructura
    AtributosHilo *atributos = (AtributosHilo *)arg;

    // Acceder a los atributos
    printf("Celdas Recorridas: %d\n", atributos->celdasRecorridas);
    printf("Dirección: %c\n", atributos->direccion);

    return NULL;
}
