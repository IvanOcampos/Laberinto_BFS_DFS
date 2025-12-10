#include "laberinto.h"

int main() {
    printf("Ingrese numero de filas: ");
    scanf("%d", &FILAS);
    printf("Ingrese numero de columnas: ");
    scanf("%d", &COLUMNAS);

    // reservar memoria dinámica
    matriz = malloc(FILAS * sizeof(char *));
    for (int i = 0; i < FILAS; i++)
        matriz[i] = malloc(COLUMNAS * sizeof(char));

    srand(time(NULL));
    crear_matriz();
    insertar_entrada_salida();

    printf("Laberinto generado:\n");
    imprimir_matriz();

    // Medir tiempo real con clock_gettime
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    Pos ruta[FILAS*COLUMNAS];
    int len = encontrar_camino_bfs(ruta, FILAS*COLUMNAS);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    if (len <= 0) {
        printf("\nNo se encontró camino de E a S.\n");
    } else {
        printf("\nCamino encontrado (longitud %d). Tiempo de busqueda: %.9f segundos\n\n", len, elapsed);
        imprimir_matriz_con_camino(ruta, len);
    }

    // liberar memoria
    for (int i = 0; i < FILAS; i++) free(matriz[i]);
    free(matriz);

    return 0;
}

