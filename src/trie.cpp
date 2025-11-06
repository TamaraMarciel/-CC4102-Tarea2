#include "trie.h"
#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

Trie::Trie() : nodos(0) {} //definición del constructor de la clase Trie

void Trie::crear_nodo(Nodo *n, int i){
    n->next[i] = new Nodo(); //crea nuevo nodo hijo dinámicamente
    nodos++;                 //aumenta contador de nodos
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
        if (n->next[i] == nullptr){
            crear_nodo(n, i);
        }
        n = n->next[i];
    }
    /**
     * añadir $
     */

     //insertar el carácter '$' que marca el fin de palabra
    int fin = 26;
    if (n->next[fin] == nullptr)
        crear_nodo(n, fin);

    //el nodo alcanzado por '$' es el terminal
    n = n->next[fin];
    n->str = new string(w);  // guarda la palabra asociada
    n->priority = 0;         // prioridad inicial
    n->best_terminal = n;    // por ahora él mismo es el mejor
    n->best_priority = 0;
}

Nodo * Trie :: descend(Nodo *v, char c){

}

Nodo * Trie :: autocomplete(Nodo *v){

}