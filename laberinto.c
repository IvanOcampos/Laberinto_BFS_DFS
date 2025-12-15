#include "laberinto.h"

// Variables globales
int FILAS;
int COLUMNAS;
char **matriz;

// Rellenar con paredes
void crear_matriz() {
    // Inicializa todas las celdas del laberinto con el carácter de pared ('#').
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            matriz[i][j] = '#';
}

// Imprimir matriz
void imprimir_matriz() {
    // Recorre e imprime la matriz, celda por celda.
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++)
            printf("%c ", matriz[i][j]);
        printf("\n");
    }
}

// DFS para crear caminos (Algoritmo Recursivo de Generación de Laberintos)
void crear_camino(int i, int j) {
    // Arreglo de direcciones: (Derecha, Abajo, Izquierda, Arriba)
    int dirs[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };

    // Aleatorización del orden de las direcciones
    for (int k = 0; k < 4; k++) {
        int r = rand() % 4; // Elige un índice aleatorio
        // Intercambio de la dirección actual (k) con la dirección aleatoria (r)
        int t0 = dirs[k][0], t1 = dirs[k][1];
        dirs[k][0] = dirs[r][0]; dirs[k][1] = dirs[r][1];
        dirs[r][0] = t0; dirs[r][1] = t1;
    }

    // Intenta moverse en las 4 direcciones aleatorias
    for (int k = 0; k < 4; k++) {
        // ni, nj son las coordenadas de la celda a dos pasos de distancia
        int ni = i + dirs[k][0] * 2;
        int nj = j + dirs[k][1] * 2;

        // Validación de movimiento:
        if (ni > 0 && ni < FILAS - 1 && nj > 0 && nj < COLUMNAS - 1 && matriz[ni][nj] == '#') {
            // Convierte la celda intermedia (a un paso de distancia) en camino (' ')
            matriz[i + dirs[k][0]][j + dirs[k][1]] = ' ';
            // Convierte la celda de destino (a dos pasos de distancia) en camino (' ')
            matriz[ni][nj] = ' ';
            crear_camino(ni, nj);
        }
    }
}

// Insertar entrada y salida
void insertar_entrada_salida() {
    matriz[1][1] = 'E';
    // Llama al generador DFS, empezando a abrir el camino desde 'E'.
    crear_camino(1, 1);
    
    // Recorre la penúltima fila (FILAS - 2) de derecha a izquierda.
    for (int col = COLUMNAS - 2; col >= 1; col--) {
        // La salida se coloca en la primera celda que ya sea un camino (' ').
        if (matriz[FILAS - 2][col] == ' ') {
            matriz[FILAS - 2][col] = 'S';
            break; // Sale tan pronto como encuentra una posición válida
        }
    }
}

// Buscar posición de un caracter
int buscar_pos(char objetivo, Pos *p) {
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            if (matriz[i][j] == objetivo) { 
                p->i = i; 
                p->j = j; 
                return 1; // Posición encontrada
            }
    return 0; // Posición no encontrada
}

// Imprimir matriz con camino marcado
void imprimir_matriz_con_camino(Pos *camino, int len) {
    // Reserva memoria para una copia temporal de la matriz original.
    char **copia = malloc(FILAS * sizeof(char *));
    for (int i = 0; i < FILAS; i++) {
        copia[i] = malloc(COLUMNAS * sizeof(char));
        // Copia el contenido de la matriz original
        memcpy(copia[i], matriz[i], COLUMNAS * sizeof(char));
    }

    // Marca el camino en la copia
    for (int k = 0; k < len; k++) {
        int i = camino[k].i, j = camino[k].j;
        // Marca la celda con '.' solo si no es la Entrada ('E') o la Salida ('S')
        if (copia[i][j] != 'E' && copia[i][j] != 'S') copia[i][j] = '.';
    }

    // Imprime la matriz con el camino
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++)
            printf("%c ", copia[i][j]);
        printf("\n");
    }

    // Libera la memoria de la copia.
    for (int i = 0; i < FILAS; i++) free(copia[i]);
    free(copia);
}


// BFS para encontrar camino más corto 
int encontrar_camino_bfs(Pos ruta[], int max) {
    Pos start, goal;
    // Busca las posiciones de Entrada y Salida
    if (!buscar_pos('E', &start)) return -1;
    if (!buscar_pos('S', &goal)) return -1;

    // Inicialización de estructuras auxiliares
    // 'visited': Matriz para saber si una celda ya fue visitada (entero)
    // 'parent': Matriz para reconstruir la ruta, guarda la posición previa (estructura Pos)
    int **visited = malloc(FILAS * sizeof(int *));
    Pos **parent = malloc(FILAS * sizeof(Pos *));
    for (int i = 0; i < FILAS; i++) {
        visited[i] = calloc(COLUMNAS, sizeof(int)); // calloc inicializa a 0
        parent[i] = malloc(COLUMNAS * sizeof(Pos));
        // Inicializa el padre de todas las celdas a (-1, -1)
        for (int j = 0; j < COLUMNAS; j++) parent[i][j].i = parent[i][j].j = -1;
    }

    // Inicialización de la cola (queue) para BFS
    Pos *queue = malloc(FILAS * COLUMNAS * sizeof(Pos));
    int qh = 0, qt = 0; // qh = head (cabeza), qt = tail (cola/fin)
    queue[qt++] = start; // Encola la posición de inicio
    visited[start.i][start.j] = 1;

    // 4. Bucle principal de BFS
    int dirs[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} }; // Direcciones de movimiento
    int found = 0;
    while (qh < qt) {
        Pos cur = queue[qh++]; // Desencola la posición actual
        
        if (cur.i == goal.i && cur.j == goal.j) { 
            found = 1; 
            break; // ¡Se encontró la salida!
        }
        
        // Explora los vecinos
        for (int d = 0; d < 4; d++) {
            int ni = cur.i + dirs[d][0];
            int nj = cur.j + dirs[d][1];
            
            // Condiciones para visitar:
            if (ni >= 0 && ni < FILAS && nj >= 0 && nj < COLUMNAS && !visited[ni][nj] && matriz[ni][nj] != '#') {// Dentro de los límites, no visitado y no es pared
                visited[ni][nj] = 1;
                parent[ni][nj] = cur;        // Establece la posición actual como padre
                queue[qt++] = (Pos){ni, nj}; // Encola el nuevo vecino
            }
        }
    }
    
    if (!found) return -1; // No se encontró camino

    // Reconstrucción de la Ruta
    Pos cur = goal;
    int len = 0;
    // Se recorre desde la meta ('goal') hasta el inicio ('start') usando la matriz 'parent'
    while (!(cur.i == start.i && cur.j == start.j)) {
        ruta[len++] = cur;
        cur = parent[cur.i][cur.j]; // Mueve a la posición padre
        if (cur.i == -1 && cur.j == -1) break; // Parada de seguridad si el padre no está definido
    }
    ruta[len++] = start; // Añade la posición de inicio

    // Inversión de la Ruta, La ruta se construyó de S a E, se invierte para que vaya de E a S.
    for (int a = 0, b = len-1; a < b; a++, b--) {
        Pos tmp = ruta[a]; ruta[a] = ruta[b]; ruta[b] = tmp;
    }

    // Liberación de la memoria auxiliar
    for (int i = 0; i < FILAS; i++) { free(visited[i]); free(parent[i]); }
    free(visited); free(parent); free(queue);

    return len; // Devuelve la longitud del camino más corto
}
