#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <celda.h>

// Variables necesarias
//Matriz que representa al laberinto (puntero a un array porque no sabemos dimensiones)
int **Celda[]
//Cada fila es una línea del TXT
//Cada campo de la fila representa una celda 
//CAMPO: Fila con el char, y direcciones a las que fue recorrido
// [   [ ['1','izq','der','arr','abj'],['*','izq','der','arr','abj']],
//     [ ['1','izq','der','arr','abj'],['*','izq','der','arr','abj']],
//     [ ['1','izq','der','arr','abj'],['*','izq','der','arr','abj']]
// ]

//Cantidad de filas de la matriz 
int filasLab;
//Cantidad de columnas de la matriz
int columnasLab;

void leerArchivo(const char *nombreArchivo) {
    FILE *archivo;
    char linea[100];

    archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("Error al intentar abrir el archivo.\n");
        return;
    }

    // Obtener las dimensiones del laberinto (Están en la primera línea del archivo)
    if (fgets(linea, sizeof(linea), archivo) != NULL) {
        // Analiza los números de la primera línea
        if (sscanf(linea, "%d %d", &filasLab, &columnasLab) != 2) {
            printf("Error al obtener las dimensiones del laberinto.\n");
            fclose(archivo);
            return;
        }
        else{
            printf("Dimensiones del laberinto: filas=%d, columnas=%d\n", filasLab, columnasLab);
        }
    }
    
    // Leer y procesar el resto del archivo línea por línea
    // while (fgets(linea, sizeof(linea), archivo) != NULL) {
    //     Procesa la línea como desees aquí
    //     Por ejemplo, imprime cada línea
    //     printf("%s", linea);
    // }

    fclose(archivo);
}

int main() {
    const char *nombreArchivo = "/home/sophy/Desktop/P01_SistemasOperativos_JosePablo_Sophya-Sophy/Ejemplos laberintos/lab1.txt";
    leerArchivo(nombreArchivo);
    return 0;
};