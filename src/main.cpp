#include "trie.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;

/**
 * Lee las palabras del archivo y las retorna en un vector
 */
vector<string> leer_palabras(const string& archivo) {
    vector<string> palabras;
    ifstream file(archivo);
    string palabra;
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
        return palabras;
    }
    
    while (file >> palabra) {
        palabras.push_back(palabra);
    }
    
    file.close();
    return palabras;
}

/**
 * Mide memoria durante la inserción
 * Imprime en puntos: 2^0, 2^1, ..., 2^17, N
 */
void experimento_memoria(Trie& trie, const vector<string>& palabras) {
    cout << "\n=== Experimento de Memoria ===" << endl;
    cout << "Palabras insertadas | Nodos | Caracteres | Nodos/Carácter" << endl;
    
    long long total_caracteres = 0;
    
    for (size_t i = 0; i < palabras.size(); i++) {
        trie.insert(palabras[i]);
        total_caracteres += palabras[i].length();
        
        // Verificar si debemos imprimir (potencias de 2 o final)
        bool imprimir = false;
        if (i + 1 == palabras.size()) {
            imprimir = true; // Última palabra
        } else {
            // Verificar si es potencia de 2
            int n = i + 1;
            imprimir = (n & (n - 1)) == 0; // Truco para verificar potencia de 2
        }
        
        if (imprimir) {
            long long nodos = trie.get_nodos();
            double ratio = (double)nodos / total_caracteres;
            cout << (i + 1) << " | " << nodos << " | " 
                 << total_caracteres << " | " << ratio << endl;
        }
    }
}

/**
 * Mide tiempo de inserción normalizado
 * Divide en M=16 grupos
 */
void experimento_tiempo(const vector<string>& palabras, const string& modo) {
    cout << "\n=== Experimento de Tiempo (Modo: " << modo << ") ===" << endl;
    cout << "Grupo | Palabras | Tiempo (ms) | Caracteres | ms/Carácter" << endl;
    
    const int M = 16;
    int grupo_size = palabras.size() / M;
    
    Trie trie(modo);
    
    for (int grupo = 0; grupo < M; grupo++) {
        int inicio = grupo * grupo_size;
        int fin = (grupo == M - 1) ? palabras.size() : (grupo + 1) * grupo_size;
        
        long long caracteres_grupo = 0;
        
        auto start = chrono::high_resolution_clock::now();
        
        for (int i = inicio; i < fin; i++) {
            trie.insert(palabras[i]);
            caracteres_grupo += palabras[i].length();
        }
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        double tiempo_por_caracter = (double)duration.count() / caracteres_grupo;
        
        cout << (grupo + 1) << " | " << (fin - inicio) << " | " 
             << duration.count() << " | " << caracteres_grupo << " | " 
             << tiempo_por_caracter << endl;
    }
}

/**
 * Simula escritura de texto y mide autocompletado
 */
void experimento_autocompletado(Trie& trie, const vector<string>& texto_test, 
                                const string& nombre_test) {
    cout << "\n=== Autocompletado: " << nombre_test << " ===" << endl;
    
    long long caracteres_totales = 0;
    long long caracteres_escritos = 0;
    long long palabras_encontradas = 0;
    long long palabras_no_encontradas = 0;
    
    for (const string& palabra : texto_test) {
        caracteres_totales += palabra.length();
        
        Nodo* nodo_actual = trie.get_raiz();
        bool palabra_existe = true;
        int chars_escritos_palabra = 0;
        
        // Descender letra por letra
        for (size_t i = 0; i < palabra.length(); i++) {
            char c = palabra[i];
            nodo_actual = trie.descend(nodo_actual, c);
            chars_escritos_palabra++;
            
            if (nodo_actual == nullptr) {
                // La palabra no existe en el trie
                caracteres_escritos += palabra.length();
                palabras_no_encontradas++;
                palabra_existe = false;
                break;
            }
            
            // Verificar autocompletado
            Nodo* mejor = trie.autocomplete(nodo_actual);
            if (mejor != nullptr && mejor->str != nullptr) {
                if (*(mejor->str) == palabra) {
                    // ¡Autocompletado exitoso!
                    caracteres_escritos += chars_escritos_palabra;
                    palabras_encontradas++;
                    palabra_existe = true;
                    break;
                }
            }
        }
        
        // Si llegamos al final sin autocompletar
        if (palabra_existe && chars_escritos_palabra == palabra.length()) {
            // Verificar si la palabra existe con $
            Nodo* terminal = trie.descend(nodo_actual, '$');
            if (terminal != nullptr) {
                caracteres_escritos += palabra.length();
                palabras_encontradas++;
                // Actualizar prioridad
                trie.update_priority(terminal);
            } else {
                caracteres_escritos += palabra.length();
                palabras_no_encontradas++;
            }
        } else if (palabra_existe) {
            // Actualizar prioridad de la palabra encontrada
            Nodo* terminal = trie.find_terminal_node(palabra);
            if (terminal != nullptr) {
                trie.update_priority(terminal);
            }
        }
    }
    
    double porcentaje = (double)caracteres_escritos / caracteres_totales * 100.0;
    
    cout << "Palabras totales: " << texto_test.size() << endl;
    cout << "Palabras encontradas: " << palabras_encontradas << endl;
    cout << "Palabras no encontradas: " << palabras_no_encontradas << endl;
    cout << "Caracteres totales: " << caracteres_totales << endl;
    cout << "Caracteres escritos: " << caracteres_escritos << endl;
    cout << "Porcentaje escrito: " << porcentaje << "%" << endl;
}

int main() {
    cout << "=== Tarea 2: Tries para Autocompletado ===" << endl;
    
    // Leer dataset principal
    cout << "\nLeyendo data/words.txt..." << endl;
    vector<string> palabras = leer_palabras("data/words.txt");
    
    if (palabras.empty()) {
        cerr << "Error: No se pudieron leer las palabras" << endl;
        return 1;
    }
    
    cout << "Palabras leídas: " << palabras.size() << endl;
    
    // Experimento 1: Memoria
    Trie trie_memoria("frecuente");
    experimento_memoria(trie_memoria, palabras);
    
    // Experimento 2: Tiempo
    experimento_tiempo(palabras, "frecuente");
    
    // Experimento 3: Autocompletado
    // Para este experimento necesitas crear tries con todas las palabras
    cout << "\n\nCreando Trie para autocompletado (modo frecuente)..." << endl;
    Trie trie_frecuente("frecuente");
    for (const auto& palabra : palabras) {
        trie_frecuente.insert(palabra);
    }
    
    cout << "Creando Trie para autocompletado (modo reciente)..." << endl;
    Trie trie_reciente("reciente");
    for (const auto& palabra : palabras) {
        trie_reciente.insert(palabra);
    }
    
    // Leer textos de prueba

    vector<string> wikipedia = leer_palabras("data/wikipedia.txt");
    vector<string> random = leer_palabras("data/random.txt");
    vector<string> random_dist = leer_palabras("data/random_with_distribution.txt");
    
    if (!wikipedia.empty()) {
        experimento_autocompletado(trie_frecuente, wikipedia, "Wikipedia - Frecuente");
        experimento_autocompletado(trie_reciente, wikipedia, "Wikipedia - Reciente");
    }
    
    if (!random.empty()) {
        experimento_autocompletado(trie_frecuente, random, "Random - Frecuente");
        experimento_autocompletado(trie_reciente, random, "Random - Reciente");
    }
    
    if (!random_dist.empty()) {
        experimento_autocompletado(trie_frecuente, random_dist, "Random Dist - Frecuente");
        experimento_autocompletado(trie_reciente, random_dist, "Random Dist - Reciente");
    }

    
    cout << "\n=== Experimentación completada ===" << endl;
    
    return 0;
}