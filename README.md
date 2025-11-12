# GUÍA COMPLETA: EJECUTAR EXPERIMENTOS EN WINDOWS

## 📋 Pre-requisitos

Antes de ejecutar los experimentos, verifica que tienes:

### 1. Estructura de Directorios

```
-CC4102-Tarea2/
├── src/
│   ├── estructuras.h (CORREGIDO)
│   ├── trie.h
│   ├── trie.cpp (CORREGIDO)
│   ├── main.cpp
│   ├── experimentos.cpp
│   └── validacion.cpp (opcional)
├── data/
│   ├── words.txt (262,144 palabras - 2^18)
│   ├── wikipedia.txt (4,194,304 palabras - 2^22)
│   ├── random.txt (4,194,304 palabras - 2^22)
│   └── random_with_distribution.txt (4,194,304 palabras - 2^22)
├── output/ (se creará automáticamente)
├── Makefile
└── README.md
```

### 2. Verificar que tienes los archivos corregidos

**IMPORTANTE:** Asegúrate de haber aplicado las correcciones a:
- ✅ `src/estructuras.h` - Con constructor de inicialización
- ✅ `src/trie.cpp` - Con update_priority corregido

---

## 🚀 PASO 1: Verificar el Proyecto

Ejecuta el script de verificación en PowerShell:

```powershell
# Ir a la raíz del proyecto
cd "N:\u\Primavera 2025\Algoritmos\-CC4102-Tarea2"

# Ejecutar script de verificación (si lo tienes)
.\check_proyecto.ps1

# O verifica manualmente:
Get-ChildItem -Recurse | Select-Object FullName
```

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
- Verifica que aplicaste las correcciones
- Revisa que `estructuras.h` tenga el constructor
- Asegúrate de estar usando C++17 o superior

---

## 🧪 PASO 3: Ejecutar los Experimentos

### Ejecución Completa

```powershell
# Asegúrate de estar en la raíz del proyecto
cd "N:\u\Primavera 2025\Algoritmos\-CC4102-Tarea2"

# Ejecutar experimentos
.\trie_experimentos.exe
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
```

---