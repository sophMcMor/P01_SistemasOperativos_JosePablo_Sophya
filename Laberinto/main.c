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

// Estructura de los atributos que se le enviaran a la funcion que ejecuta el hilo.
typedef struct {
    Celda *laberinto;
    char direccion;
    int posFila;
    int posColumna;
    int celdasRecorridas;
    int filasLab;
    int columnasLab;
} Args;

// Estructura de los atributos del hilo
typedef struct {
    int celdasRecorridas;
    char direccion;
    int posFila;
    int posColumna;
} AtributosHilo;

// Imprime el laberinto
void imprimirLaberinto(Celda laberinto[MAX_FILAS][MAX_COLUMNAS], int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%c ", laberinto[i][j].caracter);
        }
        printf("\n");
    }
}

// Mueve el hilo a la siguiente posicion segun su direccion
void movimientoHilo(AtributosHilo *hilo){
    switch (hilo->direccion)
    {
    case 'A': //Arriba
        hilo->posFila--;
        break;

    case 'a': // Abajo
        hilo->posFila++;
        break;
    
    case 'i': // Izquierda
        hilo->posColumna--;
        break;

    case 'd': // Derecha
        hilo->posColumna++;
        break;
    
    default:
        break;
    }
}

// Analiza la celda actual y realiza la accion correspondiente
int recorrerCelda(Celda laberinto[MAX_FILAS][MAX_COLUMNAS], AtributosHilo *hilo){
    int termina = 0; // Guarda 3 posibles estados del hilo: no termina (0), termina (1), sale (2)
    switch (laberinto[hilo->posFila][hilo->posColumna].caracter)
    {
    // Si el caracter es 1, lo cambia por una "R" de recorrido y aumenta las celdas recorridas
    case '1':
        laberinto[hilo->posFila][hilo->posColumna].caracter = 'R';
        hilo->celdasRecorridas++;
        break;
    
    // Si el caracter es /, lo cambia por una "S" de salida, aumenta las celdas recorridas y retorna el estado de salida
    case '/':
        laberinto[hilo->posFila][hilo->posColumna].caracter = 'S';
        hilo->celdasRecorridas++;
        return 2;

    // Si el caracter es *, retorna el estado de terminar hilo
    case '*':
        return 1;

    default:
        printf("Valor no valido \n");
        break;
    }
    // SI llega aqui, el hilo puede seguir avanzando
    movimientoHilo(hilo);
    return 0;
}

void *rutinaHilo(void *arg);

// Analiza los vecinos de la celda y sus estados
void analizarCelda(Celda laberinto[MAX_FILAS][MAX_COLUMNAS], AtributosHilo *hilo){
    int fila = hilo->posFila;
    int col = hilo->posColumna;
    int celdas = hilo->celdasRecorridas;
    //printf("%d",hilo->celdasRecorridas);
    // Analiza arriba de la celda
    if (hilo->direccion != 'A' && fila - 1 >= 0 && laberinto[fila - 1][col].caracter == '1'){
        pthread_t nuevoHiloArr;
        Args misArgs = {laberinto, 'A', fila, col, celdas, 10, 10};
        pthread_create(&nuevoHiloArr, NULL, rutinaHilo, (void *) &misArgs);
        pthread_join(nuevoHiloArr, NULL);
    }
    // Analiza abajo de la celda
    if (hilo->direccion != 'a' && fila + 1 < 10 && laberinto[fila + 1][col].caracter == '1'){
        pthread_t nuevoHiloAba;
        Args misArgs = {laberinto, 'a', fila, col, celdas, 10, 10};
        pthread_create(&nuevoHiloAba, NULL, rutinaHilo, (void *) &misArgs);
        pthread_join(nuevoHiloAba, NULL);
    }
    // Analiza a la izquierda de la celda
    if (hilo->direccion != 'i' && col - 1 >= 0 && laberinto[fila][col - 1].caracter == '1'){
        pthread_t nuevoHiloIzq;
        Args misArgs = {laberinto, 'i', fila, col, celdas, 10, 10};
        pthread_create(&nuevoHiloIzq, NULL, rutinaHilo, (void *) &misArgs);
        pthread_join(nuevoHiloIzq, NULL);
    }
    // Analiza a la derecha de la celda
    if (hilo->direccion != 'd' && col + 1 < 10 && laberinto[fila][col + 1].caracter == '1'){
        pthread_t nuevoHiloDer;
        Args misArgs = {laberinto, 'd', fila, col, celdas, 10, 10};
        pthread_create(&nuevoHiloDer, NULL, rutinaHilo, (void *) &misArgs);
        pthread_join(nuevoHiloDer, NULL);
    }
}

// Implementación de la rutina del hilo
void *rutinaHilo(void *arg) {
    Args * args = (Args *)arg;
    
    // Prueba
    printf("Entra:\n");
    imprimirLaberinto(args->laberinto, args->filasLab, args->columnasLab);
    
    // Genera los atributos del hilo creado
    AtributosHilo nuevoHilo;
    AtributosHilo *ptrHilo = &nuevoHilo;
    ptrHilo->direccion = args->direccion;
    ptrHilo->posFila = args->posFila;
    ptrHilo->posColumna = args->posColumna;
    ptrHilo->celdasRecorridas = args->celdasRecorridas;


    int termina;
    while (0==0){
        // Analiza la celda
        analizarCelda(args->laberinto, ptrHilo);
        // Realiza lo correspondiente en la celda y ve si el hilo debe terminar
        termina = recorrerCelda(args->laberinto, &nuevoHilo);
        if (termina == 2){ // El hilo salio
            printf("HILO TERMINADO\nCantidad de Celdas Recorridas: %d\nEl hilo salio exitosamente",ptrHilo->celdasRecorridas);
            return 0;
        }
        else if (termina == 1){ // El hilo choco con pared
            printf("HILO TERMINADO\nCantidad de Celdas Recorridas: %d\nEl hilo no salio",ptrHilo->celdasRecorridas);
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