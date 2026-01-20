# CoreNumeric - Librería Numérica Genérica

**Estudiante:** Armando Ruesta 202410753

---

## Descripción

Librería numérica genérica moderna desarrollada en C++20 utilizando:
- Templates
- Concepts
- Variadic templates
- Fold expressions
- `if constexpr`

## Compilación

```bash
g++ -std=c++20 main.cpp -o core_numeric
./core_numeric
```

## Estructura del Proyecto

```
CoreNumeric/
├── main.cpp          # Implementación completa con tests
└── README.md         # Este archivo
```

## Características Implementadas

### 1. Concepts Obligatorios
- `Iterable`: Permite iterar contenedores
- `Addable`: Permite suma de tipos
- `Divisible`: Permite división
- `Comparable`: Concept personalizado para comparación
- `Numeric`: Concept personalizado que combina operaciones matemáticas

### 2. Algoritmos Implementados

#### Para Contenedores
- `sum()`: Suma de elementos
- `mean()`: Media aritmética
- `variance()`: Varianza
- `max()`: Elemento máximo
- `transform_reduce()`: Transformación y reducción

#### Versiones Variadic
- `sum_variadic()`
- `mean_variadic()`
- `variance_variadic()`
- `max_variadic()`

### 3. Uso de `if constexpr`
Implementado en `max_variadic()` para diferenciar entre tipos integrales y flotantes.

### 4. Tests Incluidos

**Casos que compilan:**
- Tipos fundamentales (int, double, float, char)
- Contenedores STL (vector, list)
- Objetos personalizados (Vector3D, Coordenada)

**Casos que NO compilan (comentados):**
- Tipos que no cumplen los concepts requeridos
- Explicación de qué concept falla en cada caso

## Ejemplo de Uso

```cpp
using namespace core_numeric;

// Con contenedores
vector<double> data{1.0, 2.0, 3.0};
auto s = sum(data);
auto m = mean(data);
auto v = variance(data);

// Con variadic templates
auto total = sum_variadic(1, 2, 3, 4);
auto promedio = mean_variadic(1.5, 2.5, 3.5);

// Con objetos personalizados
vector<Vector3D> vectores{...};
auto suma = sum(vectores);
```

## Requisitos

- Compilador con soporte C++20 (GCC 10+, Clang 10+, MSVC 2019+)
