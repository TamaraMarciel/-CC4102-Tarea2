# GUÍA COMPLETA: EJECUTAR EXPERIMENTOS EN WINDOWS

## 📋 Pre-requisitos

Antes de ejecutar los experimentos, verifica que tienes:

### 1. Estructura de Directorios

```
-CC4102-Tarea2/
├── src/
│   ├── estructuras.h 
│   ├── trie.h
│   ├── trie.cpp 
│   ├── experimentos.cpp
│   └── validacion_simple.cpp (opcional)
├── data/
│   ├── words.txt 
│   ├── wikipedia.txt 
│   ├── random.txt 
│   └── random_with_distribution.txt 
├── output/ (crearlo)
├── Makefile
└── README.md
```

### 2. Verificar que tienes los archivos corregidos
---

## 🚀 PASO 1: Verificar el Proyecto

Ejecuta el script de verificación en PowerShell:

```powershell
# Ir a la raíz del proyecto
cd "\-CC4102-Tarea2"

**Verifica que existan:**
- ✅ Carpeta `data/` con los 4 archivos .txt
- ✅ Carpeta `src/` con todos los archivos de código
- ✅ Carpeta `output/` (si no existe, créala)

**Crear output/ si no existe:**
```powershell
New-Item -ItemType Directory -Path "output" -Force
```

---

## 🔨 PASO 2: Compilar el Proyecto

### Opción A: Con Makefile (si tienes make)

```powershell
# Limpiar compilaciones anteriores
make clean

# Compilar todo
make

# Deberías ver:
# trie_test.exe
# trie_experimentos.exe
```

### Opción B: Compilar manualmente con g++

```powershell
# Ir a la carpeta src
cd src

# Compilar trie.cpp
g++ -std=c++17 -Wall -Wextra -O2 -c trie.cpp -o trie.o

# Compilar experimentos.cpp
g++ -std=c++17 -Wall -Wextra -O2 -c experimentos.cpp -o experimentos.o

# Enlazar para crear el ejecutable
g++ -std=c++17 -Wall -Wextra -O2 -o ..\trie_experimentos.exe trie.o experimentos.o

# Volver a la raíz
cd ..
```

**Si ves errores de compilación:**
- Asegúrate de estar usando C++17 o superior

---

## 🧪 PASO 3: Ejecutar los Experimentos

### Ejecución Completa

```powershell
# Asegúrate de estar en la raíz del proyecto
cd "\-CC4102-Tarea2"

# Ejecutar experimentos
make run
```

### Salida Esperada

Deberías ver algo como:

```
============================================
  TAREA 2: TRIES PARA AUTOCOMPLETADO
============================================

Leyendo diccionario (data/words.txt)...
Leídas 262144 palabras de data/words.txt

========== EXPERIMENTO 1: MEMORIA ==========
   Palabras |      Nodos |   Caracteres | Nodos/Char
------------------------------------------------------------
           1 |          6 |            5 | 1.200000
           2 |         11 |           12 | 0.916667
           4 |         22 |           24 | 0.916667
        ...
      262144 |    xxxxxx |      xxxxxxx | x.xxxxxx

Resultados guardados en output/resultados_memoria.csv

========== EXPERIMENTO 2: TIEMPO ==========
 Grupo |  Tiempo(ms) |   Caracteres | ms/Char
-----------------------------------------------
     1 |         xxx |        xxxxx | x.xxxxxxxx
     2 |         xxx |        xxxxx | x.xxxxxxxx
    ...
    16 |         xxx |        xxxxx | x.xxxxxxxx

Resultados guardados en output/resultados_tiempo.csv

========== EXPERIMENTO 3: AUTOCOMPLETADO ==========

Leyendo datasets de prueba...
Leídas 4194304 palabras de data/wikipedia.txt
Leídas 4194304 palabras de data/random.txt
Leídas 4194304 palabras de data/random_with_distribution.txt

Creando Trie (modo frecuente)...
Creando Trie (modo reciente)...

--- Procesando wikipedia ---
Ejecutando modo frecuente...
  Palabras: 4194304
  Encontradas: xxxxxxx
  Porcentaje escrito: xx.xx%
  Tiempo: xxxxx ms
Ejecutando modo reciente...
  ...

--- Procesando random ---
...

--- Procesando random_dist ---
...

Resultados guardados en output/resultados_autocompletado.csv

============================================
  EXPERIMENTOS COMPLETADOS
============================================

Archivos generados:
  - resultados_memoria.csv
  - resultados_tiempo.csv
  - resultados_autocompletado.csv
  - resultados_autocompletado_detallado.csv (evoluci├│n)
```

---