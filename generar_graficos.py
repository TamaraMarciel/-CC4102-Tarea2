#!/usr/bin/env python3
"""
Script para generar gráficos de los resultados experimentales
Requiere: matplotlib, pandas
Instalar: pip install matplotlib pandas

Lee CSVs desde output/ y guarda gráficos en output/
"""

import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def grafico_memoria():
    """Genera gráfico de consumo de memoria normalizado"""
    try:
        df = pd.read_csv('output/resultados_memoria.csv')
        
        plt.figure(figsize=(10, 6))
        plt.plot(df['Palabras'], df['Nodos_por_Caracter'], marker='o', linewidth=2)
        plt.xscale('log', base=2)
        plt.xlabel('Número de Palabras Insertadas', fontsize=12)
        plt.ylabel('Nodos / Carácter', fontsize=12)
        plt.title('Consumo de Memoria Normalizado del Trie', fontsize=14, fontweight='bold')
        plt.grid(True, alpha=0.3)
        plt.tight_layout()
        plt.savefig('output/grafico_memoria.png', dpi=300)
        print("✓ Gráfico guardado: output/grafico_memoria.png")
        plt.close()
    except FileNotFoundError:
        print("✗ No se encontró output/resultados_memoria.csv")
    except Exception as e:
        print(f"✗ Error generando gráfico de memoria: {e}")

def grafico_tiempo():
    """Genera gráfico de tiempo de inserción normalizado"""
    try:
        df = pd.read_csv('output/resultados_tiempo.csv')
        
        plt.figure(figsize=(10, 6))
        plt.plot(df['Grupo'], df['ms_por_Caracter'], marker='s', linewidth=2, color='orange')
        plt.xlabel('Grupo de Inserción', fontsize=12)
        plt.ylabel('Tiempo (ms) / Carácter', fontsize=12)
        plt.title('Tiempo de Inserción Normalizado por Grupo', fontsize=14, fontweight='bold')
        plt.grid(True, alpha=0.3)
        plt.tight_layout()
        plt.savefig('output/grafico_tiempo.png', dpi=300)
        print("✓ Gráfico guardado: output/grafico_tiempo.png")
        plt.close()
    except FileNotFoundError:
        print("✗ No se encontró output/resultados_tiempo.csv")
    except Exception as e:
        print(f"✗ Error generando gráfico de tiempo: {e}")

def grafico_autocompletado():
    """Genera gráficos de análisis de autocompletado"""
    try:
        df = pd.read_csv('output/resultados_autocompletado.csv')
        
        if df.empty:
            print("✗ output/resultados_autocompletado.csv está vacío")
            return
        
        # Gráfico de porcentaje escrito por dataset y modo
        datasets = df['Dataset'].unique()
        modos = df['Modo'].unique()
        
        fig, ax = plt.subplots(figsize=(12, 6))
        
        x = range(len(datasets))
        width = 0.35
        
        for i, modo in enumerate(modos):
            valores = [df[(df['Dataset'] == d) & (df['Modo'] == modo)]['Porcentaje'].values[0] 
                      if not df[(df['Dataset'] == d) & (df['Modo'] == modo)].empty else 0
                      for d in datasets]
            ax.bar([p + i * width for p in x], valores, width, label=modo.capitalize())
        
        ax.set_xlabel('Dataset', fontsize=12)
        ax.set_ylabel('Porcentaje de Caracteres Escritos (%)', fontsize=12)
        ax.set_title('Eficiencia del Autocompletado por Dataset y Modo', 
                    fontsize=14, fontweight='bold')
        ax.set_xticks([p + width/2 for p in x])
        ax.set_xticklabels(datasets)
        ax.legend()
        ax.grid(True, alpha=0.3, axis='y')
        
        plt.tight_layout()
        plt.savefig('output/grafico_autocompletado_porcentaje.png', dpi=300)
        print("✓ Gráfico guardado: output/grafico_autocompletado_porcentaje.png")
        plt.close()
        
        # Gráfico de tiempo de ejecución
        fig, ax = plt.subplots(figsize=(12, 6))
        
        for i, modo in enumerate(modos):
            valores = [df[(df['Dataset'] == d) & (df['Modo'] == modo)]['Tiempo_ms'].values[0]
                      if not df[(df['Dataset'] == d) & (df['Modo'] == modo)].empty else 0
                      for d in datasets]
            ax.bar([p + i * width for p in x], valores, width, label=modo.capitalize())
        
        ax.set_xlabel('Dataset', fontsize=12)
        ax.set_ylabel('Tiempo de Ejecución (ms)', fontsize=12)
        ax.set_title('Tiempo de Ejecución del Autocompletado', 
                    fontsize=14, fontweight='bold')
        ax.set_xticks([p + width/2 for p in x])
        ax.set_xticklabels(datasets)
        ax.legend()
        ax.grid(True, alpha=0.3, axis='y')
        
        plt.tight_layout()
        plt.savefig('output/grafico_autocompletado_tiempo.png', dpi=300)
        print("✓ Gráfico guardado: output/grafico_autocompletado_tiempo.png")
        plt.close()
        
    except FileNotFoundError:
        print("✗ No se encontró output/resultados_autocompletado.csv")
    except Exception as e:
        print(f"✗ Error generando gráficos de autocompletado: {e}")

def main():
    print("=" * 50)
    print("  GENERADOR DE GRÁFICOS - TAREA 2")
    print("=" * 50)
    print()
    
    # Verificar que existe el directorio output/
    if not os.path.exists('output'):
        print("✗ No existe el directorio output/")
        print("  Ejecuta primero: make run")
        sys.exit(1)
    
    # Verificar archivos CSV
    archivos_requeridos = [
        'output/resultados_memoria.csv',
        'output/resultados_tiempo.csv',
        'output/resultados_autocompletado.csv'
    ]
    
    archivos_disponibles = [f for f in archivos_requeridos if os.path.exists(f)]
    
    if not archivos_disponibles:
        print("✗ No se encontraron archivos CSV de resultados en output/")
        print("  Ejecuta primero: make run")
        sys.exit(1)
    
    print(f"Archivos CSV encontrados: {len(archivos_disponibles)}/3")
    print()
    
    # Generar gráficos
    print("Generando gráficos...")
    print()
    
    grafico_memoria()
    grafico_tiempo()
    grafico_autocompletado()
    
    print()
    print("=" * 50)
    print("  GRÁFICOS GENERADOS EXITOSAMENTE")
    print("=" * 50)
    print()
    print("Archivos generados en output/:")
    print("  - grafico_memoria.png")
    print("  - grafico_tiempo.png")
    print("  - grafico_autocompletado_porcentaje.png")
    print("  - grafico_autocompletado_tiempo.png")

if __name__ == "__main__":
    try:
        import pandas
        import matplotlib
    except ImportError:
        print("Error: Se requieren pandas y matplotlib")
        print("Instalar con: pip install pandas matplotlib")
        sys.exit(1)
    
    main()