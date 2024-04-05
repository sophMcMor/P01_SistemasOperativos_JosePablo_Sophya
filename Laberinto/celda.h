#ifndef CELDA_H
#define CELDA_H

//Archivo para especificar las CELDAS del laberinto
//Ej.["1",0,0,0,0] 
//Typedef struct sirve para crear una clase como en Java o como una interface
typedef struct {
    //Variables
    char caracter; //1=Celda llena, * =Pared, / = Salida, 0  = Vacia

    //Posiciones en las que ha sido recorrida esa celda. 0 si NO, 1 en caso de que SI
    int izquierda = 0;
    int derecha = 0;
    int arriba = 0;
    int abajo = 0;
} Celda;


#endif 