#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Variables globales dinámicas
extern int FILAS;
extern int COLUMNAS;
extern char **matriz;

// Estructura para posiciones
typedef struct { int i, j; } Pos;

// Prototipos
void crear_matriz();
void imprimir_matriz();
void insertar_entrada_salida();
void crear_camino(int i, int j);
int buscar_pos(char objetivo, Pos *p);
void imprimir_matriz_con_camino(Pos *camino, int len);
int encontrar_camino_bfs(Pos ruta[], int max);
