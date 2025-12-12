## 🚀 Laberinto BSF/DFS

Este proyecto implementa un generador de laberintos aleatorios utilizando un algoritmo de **Búsqueda en Profundidad (DFS - Depth-First Search)** para la creación de caminos, y un algoritmo de **Búsqueda en Amplitud (BFS - Breadth-First Search)** para encontrar el camino más corto desde la entrada ('E') hasta la salida ('S').

---

## 🎯 Características

* **Generación Aleatoria de Laberintos:** Utiliza un enfoque basado en DFS para asegurar que el laberinto tenga una solución.
* **Búsqueda del Camino Más Corto:** Implementa el algoritmo BFS para encontrar la ruta más eficiente desde la entrada a la salida.
* **Medición de Rendimiento:** Mide el tiempo de ejecución del algoritmo BFS para la búsqueda del camino (utilizando `clock_gettime`).
* **Visualización del Laberinto y el Camino:** Muestra el laberinto generado y, si se encuentra, el camino más corto marcado con puntos (`.`).

---

## 🛠️ Estructura del Proyecto

El proyecto está organizado en los siguientes archivos principales:

| Archivo | Descripción |
| :--- | :--- |
| `main.c` | Contiene la lógica principal: manejo de entrada/salida de filas y columnas, asignación/liberación de memoria, generación de laberinto y llamada a la búsqueda BFS. |
| `laberinto.c` | Implementa las funciones relacionadas con la manipulación del laberinto: `crear_matriz()`, `imprimir_matriz()`, **`crear_camino()` (DFS)**, `insertar_entrada_salida()`, `buscar_pos()`, `imprimir_matriz_con_camino()`, y **`encontrar_camino_bfs()` (BFS)**. |
| `laberinto.h` | Archivo de cabecera que define la estructura `Pos`, declara las variables globales (`FILAS`, `COLUMNAS`, `matriz`) y los prototipos de las funciones. |

---

## 🖥️ Uso (Compilación y Ejecución)

### Requisitos

Necesitas un compilador de C (como `gcc`) instalado en tu sistema.

### Compilación

Puedes compilar el proyecto utilizando el siguiente comando en la terminal:

```bash
gcc main.c laberinto.c -o laberinto -lrt
```
Nota: Se utiliza la bandera -lrt para enlazar la librería de tiempo real, necesaria para la función clock_gettime().

### Ejecución

Ejecuta el programa compilado:

```bash
./laberinto
```
El programa te pedirá que ingreses el número de filas y columnas para generar el laberinto.

### Ejemplo de Salida
```bash
Ingrese numero de filas: 11
Ingrese numero de columnas: 21
Laberinto generado:
# # # # # # # # # # # # # # # # # # # # #
# E #           #                       #
#   #   # # #   # # # # #   #   # # # # #
#   #       #           #   #           #
#   # # #   # # # # #   #   # # # # #   #
#           #       #   #   #           #
# # # # # # #   #   #   # # #   # # #   #
#               #   #       #       #   #
#   # # # # # # # # # # #   # # #   #   #
#                                   # S #
# # # # # # # # # # # # # # # # # # # # #

Camino encontrado (longitud 51). Tiempo de busqueda: 0.000042100 segundos

# # # # # # # # # # # # # # # # # # # # #
# E # . . . . . #                       #
# . # . # # # . # # # # #   #   # # # # #
# . # . . . # . . . . . #   #           #
# . # # # . # # # # # . #   # # # # #   #
# . . . . . #       # . #   # . . . . . #
# # # # # # #   #   # . # # # . # # # . #
#               #   # . . . # . . . # . #
#   # # # # # # # # # # # . # # # . # . #
#                         . . . . . # S #
# # # # # # # # # # # # # # # # # # # # #

Process returned 0 (0x0)   execution time : 2.061 s
Press any key to continue.
```

## ⚙️ Algoritmos Clave

### Generación de Laberinto (DFS)

La función `crear_camino` utiliza un algoritmo de **Búsqueda en Profundidad (DFS)** recursivo. Comienza en un punto, borra las paredes a posiciones adyacentes no visitadas (con un salto de 2 para asegurar el grosor de las paredes) y luego llama recursivamente a la función para continuar el camino. 

### Búsqueda del Camino Más Corto (BFS)

La función `encontrar_camino_bfs` utiliza la **Búsqueda en Amplitud (BFS)**. Este algoritmo explora el laberinto capa por capa desde la entrada. Utiliza una **cola**, una matriz `visited` y una matriz `parent` para reconstruir la ruta más corta una vez que se encuentra la salida.
