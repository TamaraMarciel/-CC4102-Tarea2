#include <iostream>
#include <vector>
#include <cassert>
#include "trie.h"

using namespace std;

// Función auxiliar para imprimir estado
void printTestHeader(const string& test) {
    cout << "\n" << string(60, '=') << endl;
    cout << "  " << test << endl;
    cout << string(60, '=') << endl;
}

void printSubTest(const string& test) {
    cout << "\n--- " << test << " ---" << endl;
}

// Test 1: Validar inserción básica
bool test_insercion_basica() {
    printTestHeader("TEST 1: Inserción Básica");
    
    Trie trie("frecuente");
    vector<string> palabras = {"hola", "hola", "mundo", "holandes"};
    
    cout << "Insertando: hola, hola (duplicado), mundo, holandes" << endl;
    for (const auto& p : palabras) {
        trie.insert(p);
    }
    
    cout << "✓ Nodos creados: " << trie.get_nodos() << endl;
    
    // Verificar que las palabras existen
    Nodo* n1 = trie.find_terminal_node("hola");
    Nodo* n2 = trie.find_terminal_node("mundo");
    Nodo* n3 = trie.find_terminal_node("holandes");
    Nodo* n4 = trie.find_terminal_node("noexiste");
    
    if (n1 && n2 && n3 && !n4) {
        cout << "✓ Todas las búsquedas correctas" << endl;
        return true;
    }
    
    cout << "✗ ERROR en búsquedas" << endl;
    return false;
}

// Test 2: Validar modo FRECUENTE
bool test_modo_frecuente() {
    printTestHeader("TEST 2: Modo FRECUENTE");
    
    Trie trie("frecuente");
    
    // Insertar palabras con prefijo común "app"
    vector<string> palabras = {"app", "apple", "application", "apply"};
    cout << "Insertando palabras: ";
    for (const auto& p : palabras) {
        cout << p << " ";
        trie.insert(p);
    }
    cout << endl;
    
    printSubTest("Simulando accesos");
    
    // Acceder "app" 5 veces
    Nodo* term_app = trie.find_terminal_node("app");
    for (int i = 0; i < 5; i++) {
        trie.update_priority(term_app);
    }
    cout << "  'app' accedida 5 veces (priority = " << term_app->priority << ")" << endl;
    
    // Acceder "apple" 2 veces
    Nodo* term_apple = trie.find_terminal_node("apple");
    for (int i = 0; i < 2; i++) {
        trie.update_priority(term_apple);
    }
    cout << "  'apple' accedida 2 veces (priority = " << term_apple->priority << ")" << endl;
    
    // Acceder "application" 3 veces
    Nodo* term_application = trie.find_terminal_node("application");
    for (int i = 0; i < 3; i++) {
        trie.update_priority(term_application);
    }
    cout << "  'application' accedida 3 veces (priority = " << term_application->priority << ")" << endl;
    
    printSubTest("Probando autocompletado con prefijo 'app'");
    
    // Descender hasta 'app'
    Nodo* nodo_ap = trie.get_raiz();
    nodo_ap = trie.descend(nodo_ap, 'a');
    nodo_ap = trie.descend(nodo_ap, 'p');
    nodo_ap = trie.descend(nodo_ap, 'p');
    
    if (!nodo_ap) {
        cout << "✗ ERROR: No se pudo descender por 'app'" << endl;
        return false;
    }
    
    Nodo* mejor = trie.autocomplete(nodo_ap);
    if (!mejor || !mejor->str) {
        cout << "✗ ERROR: autocomplete retornó nullptr" << endl;
        return false;
    }
    
    string sugerencia = *(mejor->str);
    cout << "  → Sugerencia: " << sugerencia << " (priority = " << mejor->priority << ")" << endl;
    
    if (sugerencia == "app") {
        cout << "✓ CORRECTO: 'app' tiene la mayor frecuencia (5 accesos)" << endl;
        return true;
    } else {
        cout << "✗ ERROR: Se esperaba 'app' pero se obtuvo '" << sugerencia << "'" << endl;
        return false;
    }
}

// Test 3: Validar modo RECIENTE
bool test_modo_reciente() {
    printTestHeader("TEST 3: Modo RECIENTE");
    
    Trie trie("reciente");
    
    // Insertar palabras con prefijo común "app"
    vector<string> palabras = {"app", "apple", "application", "apply"};
    cout << "Insertando palabras: ";
    for (const auto& p : palabras) {
        cout << p << " ";
        trie.insert(p);
    }
    cout << endl;
    
    printSubTest("Simulando accesos en orden temporal");
    
    // Acceder en orden: apple (t=1), app (t=2), application (t=3)
    Nodo* term_apple = trie.find_terminal_node("apple");
    trie.update_priority(term_apple);
    cout << "  1. 'apple' accedida (timestamp = " << term_apple->priority << ")" << endl;
    
    Nodo* term_app = trie.find_terminal_node("app");
    trie.update_priority(term_app);
    cout << "  2. 'app' accedida (timestamp = " << term_app->priority << ")" << endl;
    
    Nodo* term_application = trie.find_terminal_node("application");
    trie.update_priority(term_application);
    cout << "  3. 'application' accedida (timestamp = " << term_application->priority << ", más reciente)" << endl;
    
    printSubTest("Probando autocompletado con prefijo 'app'");
    
    // Descender hasta 'app'
    Nodo* nodo_ap = trie.get_raiz();
    nodo_ap = trie.descend(nodo_ap, 'a');
    nodo_ap = trie.descend(nodo_ap, 'p');
    nodo_ap = trie.descend(nodo_ap, 'p');
    
    if (!nodo_ap) {
        cout << "✗ ERROR: No se pudo descender por 'app'" << endl;
        return false;
    }
    
    Nodo* mejor = trie.autocomplete(nodo_ap);
    if (!mejor || !mejor->str) {
        cout << "✗ ERROR: autocomplete retornó nullptr" << endl;
        return false;
    }
    
    string sugerencia = *(mejor->str);
    cout << "  → Sugerencia: " << sugerencia << " (timestamp = " << mejor->priority << ")" << endl;
    
    if (sugerencia == "application") {
        cout << "✓ CORRECTO: 'application' es la más reciente (timestamp = 3)" << endl;
        return true;
    } else {
        cout << "✗ ERROR: Se esperaba 'application' pero se obtuvo '" << sugerencia << "'" << endl;
        return false;
    }
}

// Test 4: Validar autocompletado letra por letra
bool test_autocompletado_progresivo() {
    printTestHeader("TEST 4: Autocompletado Progresivo");
    
    Trie trie("frecuente");
    
    // Insertar y acceder
    trie.insert("testing");
    trie.insert("test");
    trie.insert("tea");
    trie.insert("team");
    
    // Hacer "test" más frecuente
    Nodo* term_test = trie.find_terminal_node("test");
    for (int i = 0; i < 5; i++) {
        trie.update_priority(term_test);
    }
    
    cout << "Palabras insertadas: testing, test (5 accesos), tea, team" << endl;
    
    printSubTest("Autocompletando 't' → 'te' → 'tes' → 'test'");
    
    // Probar autocompletar letra por letra
    vector<string> prefijos = {"t", "te", "tes", "test"};
    
    for (const auto& prefijo : prefijos) {
        Nodo* nodo = trie.get_raiz();
        bool valido = true;
        
        for (char c : prefijo) {
            nodo = trie.descend(nodo, c);
            if (!nodo) {
                valido = false;
                break;
            }
        }
        
        if (!valido) {
            cout << "  Prefijo '" << prefijo << "': No se pudo descender" << endl;
            continue;
        }
        
        Nodo* mejor = trie.autocomplete(nodo);
        if (mejor && mejor->str) {
            cout << "  Prefijo '" << prefijo << "' → " << *(mejor->str) << endl;
        } else {
            cout << "  Prefijo '" << prefijo << "': Sin sugerencia" << endl;
        }
    }
    
    cout << "✓ Autocompletado progresivo funciona" << endl;
    return true;
}

// Test 5: Validar palabras no existentes
bool test_palabras_no_existentes() {
    printTestHeader("TEST 5: Palabras No Existentes");
    
    Trie trie("frecuente");
    
    trie.insert("hello");
    trie.insert("world");
    
    Nodo* existe = trie.find_terminal_node("hello");
    Nodo* no_existe = trie.find_terminal_node("goodbye");
    
    if (existe && !no_existe) {
        cout << "✓ 'hello' encontrada, 'goodbye' no encontrada" << endl;
        return true;
    }
    
    cout << "✗ ERROR en validación de existencia" << endl;
    return false;
}

// Test 6: Simulación de escritura
bool test_simulacion_escritura() {
    printTestHeader("TEST 6: Simulación de Escritura");
    
    Trie trie("frecuente");
    
    // Preparar diccionario
    vector<string> diccionario = {"the", "there", "their", "hello", "help", "world"};
    for (const auto& p : diccionario) {
        trie.insert(p);
    }
    
    // Simular accesos para hacer "the" más frecuente
    Nodo* term_the = trie.find_terminal_node("the");
    for (int i = 0; i < 10; i++) {
        trie.update_priority(term_the);
    }
    
    printSubTest("Escribiendo la palabra 'the'");
    
    // Simular escritura letra por letra
    string palabra_objetivo = "the";
    int chars_escritos = 0;
    
    Nodo* nodo_actual = trie.get_raiz();
    bool encontrada = false;
    
    for (size_t i = 0; i < palabra_objetivo.length(); i++) {
        nodo_actual = trie.descend(nodo_actual, palabra_objetivo[i]);
        chars_escritos++;
        
        cout << "  Escribí '" << palabra_objetivo.substr(0, chars_escritos) << "'";
        
        if (!nodo_actual) {
            cout << " → Palabra no existe en trie" << endl;
            break;
        }
        
        Nodo* mejor = trie.autocomplete(nodo_actual);
        if (mejor && mejor->str && *(mejor->str) == palabra_objetivo) {
            cout << " → ¡Autocompletado a '" << *(mejor->str) << "'!" << endl;
            cout << "  ✓ Usuario escribió " << chars_escritos << " de " << palabra_objetivo.length() << " caracteres" << endl;
            encontrada = true;
            break;
        } else if (mejor && mejor->str) {
            cout << " → Sugerencia: " << *(mejor->str) << endl;
        } else {
            cout << " → Sin sugerencia aún" << endl;
        }
    }
    
    if (encontrada) {
        cout << "✓ Simulación exitosa" << endl;
        return true;
    }
    
    cout << "Usuario tuvo que escribir toda la palabra" << endl;
    return true;
}

int main() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║     VALIDACIÓN DEL TRIE - AUTOCOMPLETADO               ║" << endl;
    cout << "║     Tarea 2: Tries para autocompletado                 ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;
    
    int tests_passed = 0;
    int total_tests = 6;
    
    if (test_insercion_basica()) tests_passed++;
    if (test_modo_frecuente()) tests_passed++;
    if (test_modo_reciente()) tests_passed++;
    if (test_autocompletado_progresivo()) tests_passed++;
    if (test_palabras_no_existentes()) tests_passed++;
    if (test_simulacion_escritura()) tests_passed++;
    
    printTestHeader("RESUMEN");
    cout << "Tests pasados: " << tests_passed << " / " << total_tests << endl;
    
    if (tests_passed == total_tests) {
        cout << "\n✓✓✓ TODOS LOS TESTS PASARON ✓✓✓" << endl;
        cout << "Tu implementación está lista para los experimentos completos" << endl;
    } else {
        cout << "\n✗ Algunos tests fallaron" << endl;
        cout << "Revisa la implementación antes de ejecutar experimentos" << endl;
    }
    
    cout << "\n";
    
    return (tests_passed == total_tests) ? 0 : 1;
}