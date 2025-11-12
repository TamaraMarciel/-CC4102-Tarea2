#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <vector>
#include <string>

using namespace std;

/**
 * estructuras.h
 * Define las estructuras básicas usadas por el Trie
 */

/**
 * Estructura de un nodo del trie
 */
struct Nodo {
    Nodo *parent;
    Nodo* next[27];
    long long priority; //vi que era mejor porque podía ser un número muy grande
    string *str; //solo != nullptr en nodos terminales, entiendo que c++ ya maneja los strings por debajo como punteros 
    Nodo *best_terminal;
    long long best_priority; //tipo cambiado por long long

    // Constructor para inicializar todos los campos
    Nodo() : parent(nullptr), priority(0), str(nullptr), best_terminal(nullptr), best_priority(0) {
        for (int i = 0; i < 27; i++) {
            next[i] = nullptr;
        }
    }
};

#endif // ESTRUCTURAS_H