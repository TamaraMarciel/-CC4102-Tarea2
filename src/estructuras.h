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
    vector<Nodo*> next[27];
    long long priority; //vi que era mejor porque podía ser un número muy grande
    string str; //entiendo que c++ ya maneja los strings por debajo como punteros
    Nodo *best_terminal;
    long long best_priority; //tipo cambiado por long long
};

#endif // ESTRUCTURAS_H