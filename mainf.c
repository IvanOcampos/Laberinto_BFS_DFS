#include "mainh.h"

int FILAS;
int COLUMNAS;
char **matriz;

// Rellenar con paredes
void crear_matriz() {
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            matriz[i][j] = '#';
}

// Imprimir matriz
void imprimir_matriz() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++)
            printf("%c ", matriz[i][j]);
        printf("\n");
    }
}

// DFS para crear caminos
void crear_camino(int i, int j) {
    int dirs[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    for (int k = 0; k < 4; k++) {
        int r = rand() % 4;
        int t0 = dirs[k][0], t1 = dirs[k][1];
        dirs[k][0] = dirs[r][0]; dirs[k][1] = dirs[r][1];
        dirs[r][0] = t0; dirs[r][1] = t1;
    }
    for (int k = 0; k < 4; k++) {
        int ni = i + dirs[k][0] * 2;
        int nj = j + dirs[k][1] * 2;
        if (ni > 0 && ni < FILAS - 1 && nj > 0 && nj < COLUMNAS - 1 && matriz[ni][nj] == '#') {
            matriz[i + dirs[k][0]][j + dirs[k][1]] = ' ';
            matriz[ni][nj] = ' ';
            crear_camino(ni, nj);
        }
    }
}

// Insertar entrada y salida
void insertar_entrada_salida() {
    matriz[1][1] = 'E';
    crear_camino(1, 1);
    for (int col = COLUMNAS - 2; col >= 1; col--) {
        if (matriz[FILAS - 2][col] == ' ') {
            matriz[FILAS - 2][col] = 'S';
            break;
        }
    }
}

// Buscar posición de un caracter
int buscar_pos(char objetivo, Pos *p) {
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            if (matriz[i][j] == objetivo) { p->i = i; p->j = j; return 1; }
    return 0;
}

// Imprimir matriz con camino marcado
void imprimir_matriz_con_camino(Pos *camino, int len) {
    char **copia = malloc(FILAS * sizeof(char *));
    for (int i = 0; i < FILAS; i++) {
        copia[i] = malloc(COLUMNAS * sizeof(char));
        memcpy(copia[i], matriz[i], COLUMNAS * sizeof(char));
    }

    for (int k = 0; k < len; k++) {
        int i = camino[k].i, j = camino[k].j;
        if (copia[i][j] != 'E' && copia[i][j] != 'S') copia[i][j] = '.';
    }

        for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++)
            printf("%c ", copia[i][j]);
        printf("\n");
    }

    for (int i = 0; i < FILAS; i++) free(copia[i]);
    free(copia);
}


// BFS para encontrar camino más corto
int encontrar_camino_bfs(Pos ruta[], int max) {
    Pos start, goal;
    if (!buscar_pos('E', &start)) return -1;
    if (!buscar_pos('S', &goal)) return -1;

    int **visited = malloc(FILAS * sizeof(int *));
    Pos **parent = malloc(FILAS * sizeof(Pos *));
    for (int i = 0; i < FILAS; i++) {
        visited[i] = calloc(COLUMNAS, sizeof(int));
        parent[i] = malloc(COLUMNAS * sizeof(Pos));
        for (int j = 0; j < COLUMNAS; j++) parent[i][j].i = parent[i][j].j = -1;
    }

    Pos *queue = malloc(FILAS * COLUMNAS * sizeof(Pos));
    int qh = 0, qt = 0;
    queue[qt++] = start;
    visited[start.i][start.j] = 1;

    int dirs[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    int found = 0;
    while (qh < qt) {
        Pos cur = queue[qh++];
        if (cur.i == goal.i && cur.j == goal.j) { found = 1; break; }
        for (int d = 0; d < 4; d++) {
            int ni = cur.i + dirs[d][0];
            int nj = cur.j + dirs[d][1];
            if (ni >= 0 && ni < FILAS && nj >= 0 && nj < COLUMNAS &&
                !visited[ni][nj] && matriz[ni][nj] != '#') {
                visited[ni][nj] = 1;
                parent[ni][nj] = cur;
                queue[qt++] = (Pos){ni, nj};
            }
        }
    }
    if (!found) return -1;

    Pos cur = goal;
    int len = 0;
    while (!(cur.i == start.i && cur.j == start.j)) {
        ruta[len++] = cur;
        cur = parent[cur.i][cur.j];
        if (cur.i == -1 && cur.j == -1) break;
    }
    ruta[len++] = start;

    for (int a = 0, b = len-1; a < b; a++, b--) {
        Pos tmp = ruta[a]; ruta[a] = ruta[b]; ruta[b] = tmp;
    }

    for (int i = 0; i < FILAS; i++) { free(visited[i]); free(parent[i]); }
    free(visited); free(parent); free(queue);

    return len;
}
