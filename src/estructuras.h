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
    int priority; //??
    string *str;
    Nodo *best_terminal;
    int best_priority; //??
};

#endif // ESTRUCTURAS_H