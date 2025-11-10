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
    Nodo* raiz; //puntero a la raíz
    long long nodos; // contador de nodos del Trie
    string priority_mode; //variable para saber cómo se está evaluando la prioridad
    long long access_timestamp; //variable para el tiempo de acceso

public:
    Trie(const string& mode); //constructor del Trie con el modo de la prioridad
    ~Trie(); //destructor

    /**
     * Dado un nodo crea un nodo en la direccion i de next 
     */
    void crear_nodo(Nodo *n, int i); //creo que no es necesaria, lo estoy revisando

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

    //funciones de ayuda/getters
    long long get_nodos() const;
    Nodo* get_raiz();
    Nodo* find_terminal_node(const std::string& w); // Muy útil para la simulación

};

#endif // TRIE_H