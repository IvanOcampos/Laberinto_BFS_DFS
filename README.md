# 🧩 Generador y Solucionador de Laberintos con DFS y BFS en C  
### *Algoritmos de búsqueda, memoria dinámica y estructuras modulares*

Este proyecto implementa un sistema completo para **generar**, **visualizar** y **resolver** laberintos utilizando dos algoritmos fundamentales de teoría de grafos:

- **DFS (Depth-First Search)** → para *generar* el laberinto de forma recursiva.  
- **BFS (Breadth-First Search)** → para *encontrar el camino más corto* desde la entrada `E` hasta la salida `S`.

El proyecto está completamente desarrollado en **lenguaje C**, con uso de:
- Recursividad avanzada  
- Memoria dinámica (`malloc`, `calloc`, `free`)  
- Modularización en archivos `.c` y `.h`  
- Medición de tiempos con `clock_gettime()`  
- Reconstrucción de rutas con padre-hijos (*parent backtracking*)

---

## 📌 **Características principales**

✔ Generación automática de laberintos perfectos (sin ciclos redundantes)  
✔ Búsqueda del camino más corto mediante BFS  
✔ Imágenes del laberinto con resultados claros  
✔ Código modular dividido en 3 archivos  
✔ Manejo completo de memoria dinámica  
✔ Reconstrucción del camino con impresión final del recorrido  

---

## 🧠 **Cómo funciona el programa**

### 🔹 1. **Generación del laberinto — Algoritmo DFS**
El laberinto comienza totalmente cubierto por paredes `#`.  
El algoritmo DFS:

1. Selecciona una celda inicial (1,1) donde coloca `E`  
2. Explora recursivamente direcciones aleatorias  
3. Rompe paredes avanzando de dos en dos  
4. Construye pasillos válidos sin dejar ciclos

Esto produce un laberinto tipo *perfect maze*.

---

### 🔹 2. **Inserción automática de entrada y salida**
El programa coloca:

- Entrada **E** en `(1,1)`  
- Salida **S** en el borde inferior, buscando la primera celda accesible

---

### 🔹 3. **Búsqueda del camino más corto — Algoritmo BFS**
BFS garantiza:

✔ El camino más corto en número de movimientos  
✔ Exploración por capas (niveles)  
✔ Uso de visitados, cola y matriz `parent`  

Al encontrar la salida, el camino se reconstruye desde `S → E`.

---

### 🔹 4. **Medición del rendimiento**
El tiempo exacto de la búsqueda BFS se obtiene con:

```c
clock_gettime(CLOCK_MONOTONIC, &start);
clock_gettime(CLOCK_MONOTONIC, &end);

Mostrando precisión en nanosegundos.
