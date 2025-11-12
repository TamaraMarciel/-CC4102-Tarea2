#include <iostream>
#include <vector>
#include "trie.h"

using namespace std;

/**
 * VALIDACIÓN: Pruebas simples para verificar que el trie funciona correctamente
 */
void validarTrie() {
    cout << "\n============================================" << endl;
    cout << "    VALIDACIÓN DEL TRIE" << endl;
    cout << "============================================\n" << endl;
    
    // ========== PRUEBA 1: MODO FRECUENTE ==========
    cout << "--- Prueba 1: Modo Frecuente ---" << endl;
    Trie trie_frec("frecuente");
    
    // Insertar palabras de prueba
    vector<string> palabras_test = {"apple", "app", "application", "apply", "banana", "band"};
    cout << "Insertando palabras: ";
    for (const auto& p : palabras_test) {
        cout << p << " ";
        trie_frec.insert(p);
    }
    cout << "\n" << endl;
    
    // Simular accesos
    cout << "Simulando accesos..." << endl;
    Nodo* terminal_app = trie_frec.find_terminal_node("app");
    if (terminal_app) {
        trie_frec.update_priority(terminal_app);
        trie_frec.update_priority(terminal_app);
        trie_frec.update_priority(terminal_app);
        cout << "  'app' accedida 3 veces (prioridad: 3)" << endl;
    }
    
    Nodo* terminal_apple = trie_frec.find_terminal_node("apple");
    if (terminal_apple) {
        trie_frec.update_priority(terminal_apple);
        cout << "  'apple' accedida 1 vez (prioridad: 1)" << endl;
    }
    
    Nodo* terminal_application = trie_frec.find_terminal_node("application");
    if (terminal_application) {
        trie_frec.update_priority(terminal_application);
        trie_frec.update_priority(terminal_application);
        cout << "  'application' accedida 2 veces (prioridad: 2)" << endl;
    }
    
    // Probar autocompletado con prefijo 'ap'
    cout << "\nAutocompletado con prefijo 'ap':" << endl;
    Nodo* nodo_ap = trie_frec.get_raiz();
    nodo_ap = trie_frec.descend(nodo_ap, 'a');
    nodo_ap = trie_frec.descend(nodo_ap, 'p');
    
    if (nodo_ap) {
        Nodo* mejor = trie_frec.autocomplete(nodo_ap);
        if (mejor && mejor->str) {
            cout << "  → Sugerencia: " << *(mejor->str) << endl;
            if (*(mejor->str) == "app") {
                cout << "  ✓ CORRECTO: 'app' tiene la mayor frecuencia (3 accesos)" << endl;
            } else {
                cout << "  ✗ ERROR: Se esperaba 'app'" << endl;
            }
        } else {
            cout << "  ✗ ERROR: No se encontró sugerencia" << endl;
        }
    } else {
        cout << "  ✗ ERROR: No se pudo descender por 'ap'" << endl;
    }
    
    // Probar con prefijo 'b'
    cout << "\nAutocompletado con prefijo 'b':" << endl;
    Nodo* nodo_b = trie_frec.get_raiz();
    nodo_b = trie_frec.descend(nodo_b, 'b');
    
    if (nodo_b) {
        Nodo* mejor = trie_frec.autocomplete(nodo_b);
        if (mejor && mejor->str) {
            cout << "  → Sugerencia: " << *(mejor->str) << endl;
            cout << "  ✓ Encontró una palabra con prefijo 'b'" << endl;
        }
    }
    
    // ========== PRUEBA 2: MODO RECIENTE ==========
    cout << "\n--- Prueba 2: Modo Reciente ---" << endl;
    Trie trie_rec("reciente");
    
    cout << "Insertando palabras: ";
    for (const auto& p : palabras_test) {
        cout << p << " ";
        trie_rec.insert(p);
    }
    cout << "\n" << endl;
    
    // Simular accesos en orden temporal
    cout << "Simulando accesos en orden temporal..." << endl;
    Nodo* term1 = trie_rec.find_terminal_node("apple");
    if (term1) {
        trie_rec.update_priority(term1);
        cout << "  1. 'apple' accedida (timestamp: 1)" << endl;
    }
    
    Nodo* term2 = trie_rec.find_terminal_node("app");
    if (term2) {
        trie_rec.update_priority(term2);
        cout << "  2. 'app' accedida (timestamp: 2)" << endl;
    }
    
    Nodo* term3 = trie_rec.find_terminal_node("application");
    if (term3) {
        trie_rec.update_priority(term3);
        cout << "  3. 'application' accedida (timestamp: 3, más reciente)" << endl;
    }
    
    // Probar autocompletado con prefijo 'ap'
    cout << "\nAutocompletado con prefijo 'ap':" << endl;
    Nodo* nodo_ap2 = trie_rec.get_raiz();
    nodo_ap2 = trie_rec.descend(nodo_ap2, 'a');
    nodo_ap2 = trie_rec.descend(nodo_ap2, 'p');
    
    if (nodo_ap2) {
        Nodo* mejor = trie_rec.autocomplete(nodo_ap2);
        if (mejor && mejor->str) {
            cout << "  → Sugerencia: " << *(mejor->str) << endl;
            if (*(mejor->str) == "application") {
                cout << "  ✓ CORRECTO: 'application' es la más reciente (timestamp: 3)" << endl;
            } else {
                cout << "  ✗ ERROR: Se esperaba 'application'" << endl;
            }
        } else {
            cout << "  ✗ ERROR: No se encontró sugerencia" << endl;
        }
    } else {
        cout << "  ✗ ERROR: No se pudo descender por 'ap'" << endl;
    }
    
    // ========== PRUEBA 3: PALABRA NO EXISTENTE ==========
    cout << "\n--- Prueba 3: Palabra no existente ---" << endl;
    Nodo* no_existe = trie_frec.find_terminal_node("xyz");
    if (no_existe == nullptr) {
        cout << "  ✓ CORRECTO: 'xyz' no existe en el trie" << endl;
    } else {
        cout << "  ✗ ERROR: Se encontró 'xyz' cuando no debería existir" << endl;
    }
    
    // ========== PRUEBA 4: PREFIJO SIN PALABRAS ==========
    cout << "\n--- Prueba 4: Prefijo sin palabras ---" << endl;
    Nodo* nodo_z = trie_frec.get_raiz();
    nodo_z = trie_frec.descend(nodo_z, 'z');
    if (nodo_z == nullptr) {
        cout << "  ✓ CORRECTO: No hay palabras con prefijo 'z'" << endl;
    } else {
        cout << "  ✗ ERROR: Se encontró nodo con prefijo 'z'" << endl;
    }
    
    // ========== ESTADÍSTICAS ==========
    cout << "\n--- Estadísticas ---" << endl;
    cout << "Palabras insertadas: " << palabras_test.size() << endl;
    cout << "Nodos en trie_frec: " << trie_frec.get_nodos() << endl;
    cout << "Nodos en trie_rec: " << trie_rec.get_nodos() << endl;
    
    cout << "\n✓ Todas las pruebas completadas" << endl;
}

int main() {
    cout << "============================================" << endl;
    cout << "  TAREA 2: TRIES PARA AUTOCOMPLETADO" << endl;
    cout << "  CASOS DE VALIDACIÓN" << endl;
    cout << "============================================" << endl;
    
    validarTrie();
    
    cout << "\n============================================" << endl;
    cout << "  VALIDACIÓN COMPLETADA EXITOSAMENTE" << endl;
    cout << "============================================" << endl;
    
    return 0;
}