#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <string>
#include "estructuras.h"

using namespace std;

/**
 * Clase para manejar el Árbol B+ en RAM (simulando disco)
 * Durante la creación, el árbol se mantiene en memoria pero se cuentan
 * las operaciones de lectura/escritura como si fueran de disco.
 */
class Trie {
private:
    Nodo raiz;
    int nodos; // contador de nodos del Trie

public:
    Trie();

    /**
     * Dado un nodo crea un nodo en la direccion i de next 
     */
    void crear_nodo(Nodo *n, int i);

    /**
     * Insetar una palabra caracter por caracter
     * Se crean Nodos en el Trie de ser necesario
     */
    void insert(string w);

    /**
     * Encuentra el puntero por el cual descender dado un caracter desde cierto nodo
     * si dicho nodo no existe retorna nulo
     */
    Nodo *descend(Nodo *v, char c);

    /**
     * Dado un Nodo devuelve un puntero al Nodo con el mejor autocompletado
     */
    Nodo *autocomplete(Nodo *v);

    /**
     * Actualiza la prioridad de un Nodo terminal y
     * actualiza a los nodos en el camino a la raiz
     */
    void update_priority(Nodo *v);

};

#endif // TRIE_H