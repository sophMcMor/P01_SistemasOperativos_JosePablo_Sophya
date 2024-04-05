#ifndef CELDA_H
#define CELDA_H

//Archivo para especificar las CELDAS del laberinto
//Una celda se compone del caracter leído del archivo (1,0,* o /)
//Y de 4 posiciones para saber dónde ha sido recorrido (0=No recorrido, 1=Recorrido)
//Ej.["1",0,0,0,0] 
//Typedef struct sirve para crear una clase como en Java o como una interface
typedef struct {
    //Variables
    char caracter; //1=Celda llena, * =Pared, / = Salida, 0  = Vacia

    //Posiciones en las que ha sido recorrida esa celda. 0 si NO, 1 en caso de que SI
    int izquierda;
    int derecha;
    int arriba;
    int abajo;
} Celda;


#endif 