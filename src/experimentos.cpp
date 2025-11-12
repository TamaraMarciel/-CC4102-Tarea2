#include "trie.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cmath>

using namespace std;


/**
 * Lee palabras de un archivo
 */
vector<string> leer_archivo(const string& nombre) {
    vector<string> palabras;
    ifstream file(nombre);
    
    if (!file.is_open()) {
        cerr << "Advertencia: No se pudo abrir " << nombre << endl;
        return palabras;
    }
    
    string palabra;
    while (file >> palabra) {
        palabras.push_back(palabra);
    }
    
    file.close();
    cout << "Leídas " << palabras.size() << " palabras de " << nombre << endl;
    return palabras;
}

/**
 * Guarda resultados de memoria en CSV
 */
void guardar_memoria_csv(const vector<tuple<long long, long long, long long>>& datos, 
                         const string& archivo) {
    ofstream file(archivo);
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo crear " << archivo << endl;
        return;
    }
    
    file << "Palabras,Nodos,Caracteres,Nodos_por_Caracter\n";
    
    for (const auto& [palabras, nodos, caracteres] : datos) {
        double ratio = (double)nodos / caracteres;
        file << palabras << "," << nodos << "," << caracteres << "," 
             << fixed << setprecision(6) << ratio << "\n";
    }
    
    file.close();
    cout << "Resultados guardados en " << archivo << endl;
}

/**
 * Experimento 1: Consumo de Memoria
 */
void experimento_memoria(const vector<string>& palabras) {
    cout << "\n========== EXPERIMENTO 1: MEMORIA ==========" << endl;
    
    Trie trie("frecuente");
    vector<tuple<long long, long long, long long>> resultados;
    
    long long total_caracteres = 0;
    
    cout << setw(12) << "Palabras" << " | " 
         << setw(10) << "Nodos" << " | " 
         << setw(12) << "Caracteres" << " | " 
         << "Nodos/Char" << endl;
    cout << string(60, '-') << endl;
    
    for (size_t i = 0; i < palabras.size(); i++) {
        trie.insert(palabras[i]);
        total_caracteres += palabras[i].length();
        
        // Verificar si es potencia de 2 o última palabra
        bool reportar = (i + 1 == palabras.size()) || ((i + 1) & i) == 0;
        
        if (reportar) {
            long long nodos = trie.get_nodos();
            double ratio = (double)nodos / total_caracteres;
            
            cout << setw(12) << (i + 1) << " | " 
                 << setw(10) << nodos << " | " 
                 << setw(12) << total_caracteres << " | " 
                 << fixed << setprecision(6) << ratio << endl;
            
            resultados.push_back({i + 1, nodos, total_caracteres});
        }
    }
    
    guardar_memoria_csv(resultados, "output/resultados_memoria.csv");
}

/**
 * Guarda resultados de tiempo en CSV
 */
void guardar_tiempo_csv(const vector<tuple<int, long long, long long>>& datos,
                        const string& archivo) {
    ofstream file(archivo);
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo crear " << archivo << endl;
        return;
    }
    
    file << "Grupo,Tiempo_ms,Caracteres,ms_por_Caracter\n";
    
    for (const auto& [grupo, tiempo, caracteres] : datos) {
        double ratio = (double)tiempo / caracteres;
        file << grupo << "," << tiempo << "," << caracteres << "," 
             << fixed << setprecision(8) << ratio << "\n";
    }
    
    file.close();
    cout << "Resultados guardados en " << archivo << endl;
}

/**
 * Experimento 2: Tiempo de Inserción
 */
void experimento_tiempo(const vector<string>& palabras) {
    cout << "\n========== EXPERIMENTO 2: TIEMPO ==========" << endl;
    
    const int M = 16;
    int grupo_size = palabras.size() / M;
    
    Trie trie("frecuente");
    vector<tuple<int, long long, long long>> resultados;
    
    cout << setw(6) << "Grupo" << " | " 
         << setw(10) << "Tiempo(ms)" << " | " 
         << setw(12) << "Caracteres" << " | " 
         << "ms/Char" << endl;
    cout << string(55, '-') << endl;
    
    for (int grupo = 0; grupo < M; grupo++) {
        int inicio = grupo * grupo_size;
        int fin = (grupo == M - 1) ? palabras.size() : (grupo + 1) * grupo_size;
        
        long long caracteres_grupo = 0;
        for (int i = inicio; i < fin; i++) {
            caracteres_grupo += palabras[i].length();
        }
        
        auto start = chrono::high_resolution_clock::now();
        
        for (int i = inicio; i < fin; i++) {
            trie.insert(palabras[i]);
        }
        
        auto end = chrono::high_resolution_clock::now();
        auto tiempo_ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        
        double ratio = (double)tiempo_ms / caracteres_grupo;
        
        cout << setw(6) << (grupo + 1) << " | " 
             << setw(10) << tiempo_ms << " | " 
             << setw(12) << caracteres_grupo << " | " 
             << fixed << setprecision(8) << ratio << endl;
        
        resultados.push_back({grupo + 1, tiempo_ms, caracteres_grupo});
    }
    
    guardar_tiempo_csv(resultados, "output/resultados_tiempo.csv");
}

/**
 * Resultados de autocompletado
 */
struct ResultadoAutocompletado {
    string dataset;
    string modo;
    long long palabras_total;
    long long palabras_encontradas;
    long long palabras_no_encontradas;
    long long caracteres_total;
    long long caracteres_escritos;
    double porcentaje_escrito;
    long long tiempo_ms;
};

/**
 * Guarda resultados de autocompletado en CSV (resumen)
 */
void guardar_autocompletado_csv(const vector<ResultadoAutocompletado>& resultados,
                                const string& archivo) {
    ofstream file(archivo);
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo crear " << archivo << endl;
        return;
    }
    
    file << "Dataset,Modo,Palabras_Total,Encontradas,No_Encontradas,"
         << "Caracteres_Total,Caracteres_Escritos,Porcentaje,Tiempo_ms\n";
    
    for (const auto& r : resultados) {
        file << r.dataset << "," << r.modo << "," 
             << r.palabras_total << "," << r.palabras_encontradas << ","
             << r.palabras_no_encontradas << "," << r.caracteres_total << ","
             << r.caracteres_escritos << "," << fixed << setprecision(2) 
             << r.porcentaje_escrito << "," << r.tiempo_ms << "\n";
    }
    
    file.close();
    cout << "Resultados guardados en " << archivo << endl;
}

/**
 * Guarda muestras detalladas (en potencias de 2) para graficar evolución
 */
void guardar_muestras_csv(const string& dataset, const string& modo,
                          const vector<tuple<long long, long long, long long, double>>& muestras,
                          const string& archivo) {
    ofstream file(archivo, ios::app);  // Append mode
    
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir " << archivo << endl;
        return;
    }
    
    for (const auto& [palabras, chars_total, chars_escritos, porcentaje] : muestras) {
        file << dataset << "," << modo << "," 
             << palabras << "," << chars_total << "," 
             << chars_escritos << "," << fixed << setprecision(2) 
             << porcentaje << "\n";
    }
    
    file.close();
}

/**
 * Experimento 3: Análisis de Autocompletado
 * Porcentaje respecto a caracteres acumulados hasta el momento (más intuitivo)
 */
ResultadoAutocompletado experimento_autocompletado_detallado(
    Trie& trie, 
    const vector<string>& texto,
    const string& nombre_dataset,
    const string& modo) {
    
    ResultadoAutocompletado resultado;
    resultado.dataset = nombre_dataset;
    resultado.modo = modo;
    resultado.palabras_total = texto.size();
    resultado.palabras_encontradas = 0;
    resultado.palabras_no_encontradas = 0;
    resultado.caracteres_total = 0;
    resultado.caracteres_escritos = 0;
    
    // Vector para guardar muestras en potencias de 2
    vector<tuple<long long, long long, long long, double>> muestras;
    
    auto start = chrono::high_resolution_clock::now();
    
    for (size_t idx = 0; idx < texto.size(); idx++) {
        const string& palabra = texto[idx];
        resultado.caracteres_total += palabra.length();  // Suma acumulativa
        
        Nodo* nodo_actual = trie.get_raiz();
        bool encontrada = false;
        int chars_necesarios = 0;
        
        // Descender letra por letra
        for (size_t i = 0; i < palabra.length(); i++) {
            nodo_actual = trie.descend(nodo_actual, palabra[i]);
            chars_necesarios++;
            
            if (nodo_actual == nullptr) {
                // Palabra no existe
                resultado.caracteres_escritos += palabra.length();
                resultado.palabras_no_encontradas++;
                encontrada = false;
                break;
            }
            
            // Intentar autocompletar
            Nodo* mejor = trie.autocomplete(nodo_actual);
            if (mejor != nullptr && mejor->str != nullptr && *(mejor->str) == palabra) {
                // ¡Autocompletado exitoso!
                resultado.caracteres_escritos += chars_necesarios;
                resultado.palabras_encontradas++;
                encontrada = true;
                
                // Actualizar prioridad
                trie.update_priority(mejor);
                break;
            }
        }
        
        // Si terminamos la palabra sin autocompletar
        if (!encontrada && nodo_actual != nullptr) {
            Nodo* terminal = trie.descend(nodo_actual, '$');
            if (terminal != nullptr) {
                resultado.caracteres_escritos += palabra.length();
                resultado.palabras_encontradas++;
                trie.update_priority(terminal);
            } else {
                resultado.caracteres_escritos += palabra.length();
                resultado.palabras_no_encontradas++;
            }
        }
        
        // NUEVO: Muestrear en potencias de 2 y al final
        size_t i = idx + 1;  // Palabras procesadas hasta ahora
        bool reportar = (i == texto.size()) || ((i & (i - 1)) == 0);
        
        if (reportar && resultado.caracteres_total > 0) {
            // Porcentaje respecto a caracteres ACUMULADOS hasta este momento
            double porcentaje_actual = 
                (double)resultado.caracteres_escritos / resultado.caracteres_total * 100.0;
            
            muestras.push_back({i, resultado.caracteres_total, 
                               resultado.caracteres_escritos, porcentaje_actual});
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    resultado.tiempo_ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    resultado.porcentaje_escrito = 
        (double)resultado.caracteres_escritos / resultado.caracteres_total * 100.0;
    
    // Guardar muestras detalladas para graficar
    guardar_muestras_csv(nombre_dataset, modo, muestras, 
                        "output/resultados_autocompletado_detallado.csv");
    
    return resultado;
}

/**
 * Ejecuta todos los experimentos de autocompletado
 */
void experimentos_autocompletado(const vector<string>& palabras_dict,
                                 const vector<string>& wikipedia,
                                 const vector<string>& random,
                                 const vector<string>& random_dist) {
    
    cout << "\n========== EXPERIMENTO 3: AUTOCOMPLETADO ==========" << endl;
    
    vector<ResultadoAutocompletado> todos_resultados;
    
    // Crear header del CSV detallado
    ofstream detallado("output/resultados_autocompletado_detallado.csv");
    detallado << "Dataset,Modo,Palabras,Caracteres_Total,Caracteres_Escritos,Porcentaje\n";
    detallado.close();
    
    // Crear tries para ambos modos
    cout << "\nCreando Trie (modo frecuente)..." << endl;
    Trie trie_frec("frecuente");
    for (const auto& p : palabras_dict) {
        trie_frec.insert(p);
    }
    
    cout << "Creando Trie (modo reciente)..." << endl;
    Trie trie_rec("reciente");
    for (const auto& p : palabras_dict) {
        trie_rec.insert(p);
    }
    
    // Probar con cada dataset
    vector<pair<string, const vector<string>*>> datasets = {
        {"wikipedia", &wikipedia},
        {"random", &random},
        {"random_dist", &random_dist}
    };
    
    for (const auto& [nombre, datos] : datasets) {
        if (datos->empty()) {
            cout << "\nSaltando " << nombre << " (no disponible)" << endl;
            continue;
        }
        
        cout << "\n--- Procesando " << nombre << " ---" << endl;
        
        // Modo frecuente
        cout << "Ejecutando modo frecuente..." << endl;
        auto res_frec = experimento_autocompletado_detallado(
            trie_frec, *datos, nombre, "frecuente");
        todos_resultados.push_back(res_frec);
        
        cout << "  Palabras: " << res_frec.palabras_total << endl;
        cout << "  Encontradas: " << res_frec.palabras_encontradas << endl;
        cout << "  Porcentaje escrito: " << fixed << setprecision(2) 
             << res_frec.porcentaje_escrito << "%" << endl;
        cout << "  Tiempo: " << res_frec.tiempo_ms << " ms" << endl;
        
        // Modo reciente
        cout << "Ejecutando modo reciente..." << endl;
        auto res_rec = experimento_autocompletado_detallado(
            trie_rec, *datos, nombre, "reciente");
        todos_resultados.push_back(res_rec);
        
        cout << "  Palabras: " << res_rec.palabras_total << endl;
        cout << "  Encontradas: " << res_rec.palabras_encontradas << endl;
        cout << "  Porcentaje escrito: " << fixed << setprecision(2) 
             << res_rec.porcentaje_escrito << "%" << endl;
        cout << "  Tiempo: " << res_rec.tiempo_ms << " ms" << endl;
    }
    
    if (!todos_resultados.empty()) {
        guardar_autocompletado_csv(todos_resultados, "output/resultados_autocompletado.csv");
    }
    
    cout << "\nSe generaron 2 archivos CSV:" << endl;
    cout << "  - resultados_autocompletado.csv (resumen final)" << endl;
    cout << "  - resultados_autocompletado_detallado.csv (evolución en potencias de 2)" << endl;
}

int main() {
    cout << "============================================" << endl;
    cout << "  TAREA 2: TRIES PARA AUTOCOMPLETADO" << endl;
    cout << "============================================" << endl;
    
    // Leer diccionario principal
    cout << "\nLeyendo diccionario (data/words.txt)..." << endl;
    vector<string> palabras = leer_archivo("data/words.txt");
    
    if (palabras.empty()) {
        cerr << "\nERROR: No se pudo leer data/words.txt" << endl;
        cerr << "Este archivo es necesario para los experimentos." << endl;
        return 1;
    }
    
    // Experimento 1: Memoria
    experimento_memoria(palabras);
    
    // Experimento 2: Tiempo
    experimento_tiempo(palabras);
    
    // Experimento 3: Autocompletado
    cout << "\nLeyendo datasets de prueba..." << endl;
    vector<string> wikipedia = leer_archivo("data/wikipedia.txt");
    vector<string> random = leer_archivo("data/random.txt");
    vector<string> random_dist = leer_archivo("data/random_with_distribution.txt");
    
    experimentos_autocompletado(palabras, wikipedia, random, random_dist);
    
    cout << "\n============================================" << endl;
    cout << "  EXPERIMENTOS COMPLETADOS" << endl;
    cout << "============================================" << endl;
    cout << "\nArchivos generados:" << endl;
    cout << "  - resultados_memoria.csv" << endl;
    cout << "  - resultados_tiempo.csv" << endl;
    cout << "  - resultados_autocompletado.csv (resumen)" << endl;
    cout << "  - resultados_autocompletado_detallado.csv (evolución)" << endl;
    
    return 0;
}