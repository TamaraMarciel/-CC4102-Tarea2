#include "trie.h"
#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

Trie::Trie() : nodos(0) {}

void Trie::crear_nodo(Nodo *n, int i){
    Nodo m;
    &n->next[i] = m; //algo falla
    nodos++;
}

void Trie::insert(string w){
    int largo = w.size();
    Nodo *n = &raiz;
    for (int i = 0; i < largo; i++){
        char caracter = w[i];
        int indice = static_cast<int>(caracter) - 97; //ASCII 97 = a
        /**
         * Si nodo en next existe bajar por ahi
         * Si no crear nodo en next y bajar
         */
        if (&n->next[i] == nullptr){
            crear_nodo(n, i);
        }
        n = n->next[i];
    }
    /**
     * añadir $
     */
}