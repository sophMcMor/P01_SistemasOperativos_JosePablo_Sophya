#include <stdio.h>
#include <stdlib.h>

//Archivo principal

void leerArchivo(const char *nombreArchivo) {
    int filas;
    int columnas;
    FILE *archivo;
    char caracter;
    char linea[100];
    int laberintoInicial[2][2] ;

    archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("Error al intentar abrir el archivo.\n");
        return;
    }

    // printf("Contenido del archivo %s:\n", nombreArchivo);

    // Lee l�nea por l�nea desde el archivo
    while (fgets(linea, 100, archivo) != NULL) {
        // Imprime la l�nea
        printf("%s", linea);

        // Detecta el salto de l�nea
        if (linea[strlen(linea) - 1] == '\n') {
            printf("Se encontr� un salto de l�nea.\n");
        }
    }

    fclose(archivo);
}

int main()
{
    printf("Hello world!\n");
    const char *nombreArchivo = "C:/Users/Harrick Mc Lean M/Desktop/I Semestre 2024/Operativos/P01_SistemasOperativos_JosePablo_Sophya/Ejemplos laberintos/lab1.txt";
    leerArchivo(nombreArchivo);
    return 0;
}
