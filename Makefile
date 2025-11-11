# Makefile para Tarea 2 - Tries para Autocompletado

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
HEADERS = src/trie.h src/estructuras.h

# Targets
TARGET_MAIN = trie_test
TARGET_EXP = trie_experimentos

# Archivos fuente
TRIE_SRC = src/trie.cpp
MAIN_SRC = src/main.cpp
EXP_SRC = src/experimentos.cpp

# Archivos objeto
TRIE_OBJ = src/trie.o
MAIN_OBJ = src/main.o
EXP_OBJ = src/experimentos.o

# Regla principal: compila ambos programas
all: $(TARGET_MAIN) $(TARGET_EXP)

# Programa de prueba simple
$(TARGET_MAIN): $(TRIE_OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET_MAIN) $(TRIE_OBJ) $(MAIN_OBJ)

# Programa de experimentación completa
$(TARGET_EXP): $(TRIE_OBJ) $(EXP_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET_EXP) $(TRIE_OBJ) $(EXP_OBJ)

# Compilar archivos objeto
src/%.o: src/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(TRIE_OBJ) $(MAIN_OBJ) $(EXP_OBJ)
	rm -f $(TARGET_MAIN) $(TARGET_EXP)
	rm -rf output/

# Ejecutar programa de prueba
test: $(TARGET_MAIN)
	./$(TARGET_MAIN)

# Ejecutar experimentación completa
run: $(TARGET_EXP)
	./$(TARGET_EXP)

# Ayuda
help:
	@echo "Makefile para Tarea 2 - Tries para Autocompletado"
	@echo ""
	@echo "IMPORTANTE: Los archivos .txt deben estar en ./data/"
	@echo ""
	@echo "Uso:"
	@echo "  make              - Compila ambos programas"
	@echo "  make test         - Compila y ejecuta pruebas simples"
	@echo "  make run          - Compila y ejecuta experimentación completa"
	@echo "  make clean        - Elimina archivos generados"
	@echo "  make help         - Muestra esta ayuda"
	@echo ""
	@echo "Programas generados:"
	@echo "  trie_test         - Pruebas básicas y debugging"
	@echo "  trie_experimentos - Experimentación completa con salida a CSV"

.PHONY: all clean run test help