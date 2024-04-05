#ifndef HILO_H
#define HILO_H

#include <pthread.h>

// Estructura para los atributos del hilo
typedef struct {
    int celdasRecorridas;
    char direccion;
} AtributosHilo;

// Prototipo de la rutina del hilo
void *rutinaHilo(void *arg);

#endif 
