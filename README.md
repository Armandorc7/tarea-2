# Tarea 2 – Core Numeric (Programación III)

Nombre: Armando R.  
Curso: Programación III  
Lenguaje: C++ (C++20)

## Descripción
Implementación de una pequeña librería de algoritmos numéricos genéricos usando
templates y concepts.  
Los algoritmos funcionan con contenedores estándar y con tipos definidos por el
usuario, siempre que cumplan los concepts requeridos.

## Contenido
- Concepts: Iterable, Sized, Addable, Divisible, Comparable, Numeric
- Algoritmos:
  - sum
  - mean
  - variance
  - max_element
  - transform_reduce
- Variadic templates:
  - sum_variadic
  - mean_variadic
  - variance_variadic (con if constexpr)
  - max_variadic
- Pruebas con tipos básicos y con un tipo personalizado (Vector3D)

## Tests
- El `main.cpp` contiene:
  - Tests que compilan (ejecución normal)
  - Tests que NO compilan, dejados comentados, indicando qué concept falla

## Compilación
Compilar con estándar C++20.  
Ejemplo:

```bash
g++ -std=c++20 main.cpp -o main
