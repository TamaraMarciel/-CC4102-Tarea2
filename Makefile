# Makefile para Tarea 2 - Tries para Autocompletado
# Optimizado para Windows (MinGW/MSYS2)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
HEADERS = src/trie.h src/estructuras.h

# Targets
TARGET_EXP = trie_experimentos.exe

# Archivos fuente y objeto
TRIE_OBJ = src/trie.o
EXP_OBJ = src/experimentos.o

# Regla por defecto: compilar experimentos
all: $(TARGET_EXP)
	@echo.
	@echo ============================================
	@echo   COMPILACION EXITOSA
	@echo ============================================
	@echo.
	@echo Para ejecutar: make run
	@echo.

# Programa de experimentación
$(TARGET_EXP): $(TRIE_OBJ) $(EXP_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET_EXP) $(TRIE_OBJ) $(EXP_OBJ)

# Compilar trie.cpp
src/trie.o: src/trie.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c src/trie.cpp -o src/trie.o

# Compilar experimentos.cpp
src/experimentos.o: src/experimentos.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c src/experimentos.cpp -o src/experimentos.o

# Ejecutar experimentos
run: $(TARGET_EXP)
	@if not exist output mkdir output
	@echo.
	@echo Ejecutando experimentos...
	@echo ADVERTENCIA: Esto puede tardar 20-40 minutos
	@echo.
	$(TARGET_EXP)

# Limpiar (compatible con Windows)
clean:
	@echo Limpiando archivos...
	@if exist src\trie.o del src\trie.o
	@if exist src\experimentos.o del src\experimentos.o
	@if exist $(TARGET_EXP) del $(TARGET_EXP)
	@echo Limpieza completa.

# Limpiar todo incluyendo output/
clean-all: clean
	@if exist output rmdir /S /Q output
	@echo Output eliminado.

# Ayuda
help:
	@echo ============================================
	@echo   MAKEFILE - TAREA 2 TRIES
	@echo ============================================
	@echo.
	@echo Comandos:
	@echo   make          - Compila el proyecto
	@echo   make run      - Ejecuta experimentos (20-40 min)
	@echo   make clean    - Limpia .o y .exe
	@echo   make clean-all- Limpia todo incluyendo output/
	@echo   make help     - Muestra esta ayuda
	@echo.
	@echo Archivos necesarios en data/:
	@echo   - words.txt
	@echo   - wikipedia.txt  
	@echo   - random.txt
	@echo   - random_with_distribution.txt
	@echo.
	@echo Resultados CSV en output/:
	@echo   - resultados_memoria.csv
	@echo   - resultados_tiempo.csv
	@echo   - resultados_autocompletado.csv
	@echo.

.PHONY: all clean clean-all run help