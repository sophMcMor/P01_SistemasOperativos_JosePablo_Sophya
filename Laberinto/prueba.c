#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "celda.h" // Asegúrate de incluir la definición de Celda

int main() {
    const char *nombreArchivo = "/home/sophy/Desktop/P01_SistemasOperativos_JosePablo_Sophya-Sophy/Ejemplos laberintos/lab1.txt"; // Nombre del archivo
    FILE *archivo;
    char linea[100]; // Buffer para leer cada línea del archivo
    int fila = 0; // Contador de filas del archivo 
   
    //Cantidad de filas de la matriz 
    int filasLab;
    //Cantidad de columnas de la matriz
    int columnasLab;

    // Abre el archivo para leer
    archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    // Mientras haya líneas por leer en el archivo
    while (fgets(linea, sizeof(linea), archivo) != NULL) {

        //Obtener las dimensiones del laberinto (Primera línea del archivo)
        if(fila== 0){
            if (sscanf(linea, "%d %d", &filasLab, &columnasLab) == 2) {
                printf("Dimensiones del laberinto: filas=%d, columnas=%d\n", filasLab, columnasLab);
                //Como ya sabemos las dimensiones del laberinto, creamos el array
                Celda laberinto[filasLab][columnasLab];
                fila++;
                return;
            } 
            else{
                printf("Error al obtener las dimensiones del laberinto.\n");
                fclose(archivo);
                return;
            }       
        }//Fin if fila 0
        else{
            // Creamos una lista para almacenar las celdas de la fila actual
            Celda listaCeldas[1][columnasLab]; //Es un array de 1 fila x cant columnas 
            // Recorremos cada caracter de la línea
            for (int i = 0; i < strlen(linea); i++) {
                char caracter = linea[i];
                if (caracter == ' ') {
                    //Significa Celda disponible, la marcamos con 0
                    // Creamos una nueva celda y la agregamos a la lista de celdas
                    Celda nuevaCelda;
                    nuevaCelda.caracter='0';
                    nuevaCelda.arriba= 0;
                    nuevaCelda.abajo= 0;
                    nuevaCelda.izquierda= 0;
                    nuevaCelda.derecha= 0;
                    listaCeldas[i].valor = nuevaCelda;
                }                
                if (caracter == '*') {
                    //Significa PARED del laberinto
                    // Creamos una nueva celda y la agregamos a la lista de celdas
                    Celda nuevaCelda;
                    nuevaCelda.caracter='*';
                    nuevaCelda.arriba= 0;
                    nuevaCelda.abajo= 0;
                    nuevaCelda.izquierda= 0;
                    nuevaCelda.derecha= 0;
                    listaCeldas[i].valor = nuevaCelda;
                } 
                if (caracter == '/') {
                    //Significa SALIDA del laberinto
                    // Creamos una nueva celda y la agregamos a la lista de celdas
                    Celda nuevaCelda;
                    nuevaCelda.caracter='/';
                    nuevaCelda.arriba= 0;
                    nuevaCelda.abajo= 0;
                    nuevaCelda.izquierda= 0;
                    nuevaCelda.derecha= 0;
                    listaCeldas[i].valor = nuevaCelda;
                }                 
            }//Fin else 

            // Agregamos la lista de celdas al laberinto
            laberinto[fila] = listaCeldas;

            fila++; // Incrementamos el contador de filas
        }
    }

    // Cierra el archivo
    fclose(archivo);


    return 0;
}
