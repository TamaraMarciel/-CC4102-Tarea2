#include "trie.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <chrono>

using namespace std;

Trie::Trie(const string& priority_mode) 
    : nodos(1), mode(priority_mode), access_timestamp(0) {
    // La raíz ya está inicializada por su constructor
    raiz.parent = nullptr;
} //definición del constructor de la clase Trie


// Destructor
Trie::~Trie() {
    // Destruir todos los nodos excepto la raíz (que es un objeto, no puntero)
    for (int i = 0; i < 27; i++) {
        if (raiz.next[i] != nullptr) {
            destruir_nodo(raiz.next[i]);
        }
    }
}

void Trie::destruir_nodo(Nodo *n) {
    if (n == nullptr) return;
    
    // Destruir todos los hijos recursivamente
    for (int i = 0; i < 27; i++) {
        if (n->next[i] != nullptr) {
            destruir_nodo(n->next[i]);
        }
    }
    
    // Liberar el string si existe
    if (n->str != nullptr) {
        delete n->str;
    }
    
    // Liberar el nodo
    delete n;
}



void Trie::crear_nodo(Nodo *n, int i){
    n->next[i] = new Nodo(); //crea nuevo nodo hijo dinámicamente
    n->next[i] -> parent = n; // se define al padre
    nodos++;                 //aumenta contador de nodos
}

long long Trie::obtenerTimestamp() {
    auto ahora = chrono::system_clock::now();
    auto timestamp = chrono::duration_cast<chrono::seconds>(
        ahora.time_since_epoch()
    ).count();
    return timestamp;
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
        if (n->next[indice] == nullptr){
            crear_nodo(n, indice);
        }
        n = n->next[indice];
    }
    /**
     * añadir $
     */

     //insertar el carácter '$' que marca el fin de palabra
    int fin = 26;
    if (n->next[fin] == nullptr){
        crear_nodo(n, fin);
    }

    //el nodo alcanzado por '$' es el terminal
    n = n->next[fin];
    n->str = new string(w);  //guarda la palabra asociada
    n->priority = 0;         //prioridad inicial
    n->best_terminal = n;    //por ahora él mismo es el mejor
    n->best_priority = 0;
}

Nodo * Trie :: descend(Nodo *v, char c){
    int indice;
    if (c == '$') {
        indice = 26;  //el carácter especial del fin de palabra
    }
    else {
        indice = static_cast<int>(c) - 97;
    }
    Nodo * sgte = v->next[indice];
    if (sgte != nullptr) {
        return sgte;
    }
    
    else {
        return nullptr;
    }

}

void Trie :: update_priority(Nodo *v){
    if (v != nullptr) {
        if (mode == "frecuente") {
            v->priority++;
            if (v->parent != nullptr && (v->parent)->priority < v-> priority) {
                update_priority(v->parent);
            }

        }
        if (mode == "reciente") {
            v->priority = obtenerTimestamp();
            if (v->parent != nullptr && (v->parent)->priority < v-> priority) {
                update_priority(v->parent);
            }
            
        }
    }

}

Nodo * Trie :: autocomplete(Nodo *v){
    if (v == nullptr){
        return nullptr;
    }

    return v-> best_terminal;
}

long long Trie::get_nodos() const {
    return nodos;
}

Nodo* Trie::get_raiz() {
    return &raiz;
}

Nodo* Trie::find_terminal_node(const string& w) {
    Nodo *n = &raiz;
    
    // Descender por cada carácter
    for (char c : w) {
        n = descend(n, c);
        if (n == nullptr) {
            return nullptr;
        }
    }
    
    // Descender por '$' para llegar al terminal
    n = descend(n, '$');
    return n;
}