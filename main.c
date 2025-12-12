#include "laberinto.h"

int main() {
    // Lectura de dimensiones del laberinto
    printf("Ingrese numero de filas: ");
    scanf("%d", &FILAS);
    printf("Ingrese numero de columnas: ");
    scanf("%d", &COLUMNAS);

    // Reserva de memoria dinámica para la matriz (matriz[FILAS][COLUMNAS])
    matriz = malloc(FILAS * sizeof(char *));
    for (int i = 0; i < FILAS; i++)
        matriz[i] = malloc(COLUMNAS * sizeof(char));

    // Generación del Laberinto
    srand(time(NULL));
    crear_matriz();              // Llena la matriz con caminos y paredes
    insertar_entrada_salida();   // Coloca 'E' y 'S' en el laberinto

    printf("Laberinto generado:\n");
    imprimir_matriz();

    // Inicio de la medición del tiempo
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Búsqueda del camino usando BFS (Breadth-First Search)
    Pos ruta[FILAS*COLUMNAS]; // Almacena el camino encontrado
    int len = encontrar_camino_bfs(ruta, FILAS*COLUMNAS); // 'len' es la longitud del camino

    // Fin de la medición y cálculo del tiempo transcurrido
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    // Muestra de resultados
    if (len <= 0) {
        printf("\nNo se encontró camino de E a S.\n");
    } else {
        printf("\nCamino encontrado (longitud %d). Tiempo de busqueda: %.9f segundos\n\n", len, elapsed);
        imprimir_matriz_con_camino(ruta, len); // Muestra el laberinto con la ruta marcada
    }

    // Liberación de memoria dinámica
    for (int i = 0; i < FILAS; i++) free(matriz[i]);
    free(matriz);

    return 0;
}
