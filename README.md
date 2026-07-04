# Simulador MLQ (Multilevel Queue) — Parcial 1 Sistemas Operativos

Simulador de planificacion de procesos **MLQ** en C++ (paradigma orientado a objetos).

## Esquema implementado

| Cola | Politica    | Prioridad |
|------|-------------|-----------|
| Q1   | RR(1)       | Mas alta  |
| Q2   | RR(3)       | Media     |
| Q3   | SJF         | Mas baja  |

**Despacho entre colas:** prioridad estricta con **expropiacion**. La cola de
mayor prioridad (menor numero) siempre corre si tiene procesos listos. Si mientras
corre un proceso de una cola llega uno a una cola de mayor prioridad, el actual se
expropia y conserva su tiempo restante.

## Estructura

```
src/
  Process.h/.cpp          Datos del proceso + metricas (sin logica)
  SchedulingPolicy.h      Interfaz abstracta de politica
  RoundRobin.h/.cpp       Politica RR con quantum parametrizable
  SJF.h/.cpp              Politica Shortest Job First
  Queue.h/.cpp            Lista de listos + su politica
  MLQScheduler.h/.cpp     Bucle del reloj global + despacho entre colas
  FileParser.h/.cpp       Lee y parsea el archivo de entrada
  ReportWriter.h/.cpp     Escribe el archivo de salida + promedios
  main.cpp                Orquesta: parsear -> simular -> escribir
inputs/                   Archivos de entrada del profesor (Google Drive)
outputs/                  Archivos de salida generados
docs/
  informe.tex             Informe en LaTeX (compilar en Overleaf con pdfLaTeX)
```

## Archivos de entrada

Los archivos de `inputs/` son los casos de prueba oficiales publicados por el
profesor en la carpeta de Google Drive del parcial. Se ejecutaron los 13 casos y
sus resultados se documentan en `docs/informe.tex`.

## Formato de entrada

```
# etiqueta; BT; AT; Q; Prioridad(5>1)
A;6; 0; 1; 5
```
Las lineas que empiezan con `#` y las vacias se ignoran.

## Formato de salida

```
# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT
A;6;0;1;5;5;11;0;11
# WT=20.0; CT=29.6; RT=14.8; TAT=29.6;
```

Metricas: `TAT = CT - AT`, `WT = TAT - BT`, `RT = primer instante de ejecucion - AT`.

## Compilar y ejecutar

Con g++ (MinGW-w64 en Windows / gcc en Linux/Mac):

```bash
g++ -std=c++17 -Wall -Wextra -g src/*.cpp -o mlq

# uso: ./mlq <entrada> [salida]
./mlq inputs/mlq001.txt outputs/mlq001_out.txt
```

Si no se pasan argumentos usa `inputs/mlq001.txt` -> `outputs/mlq001_out.txt`.

Para correr todos los casos del profesor de una vez:

```bash
for f in inputs/mlq*.txt; do b=$(basename "$f" .txt); ./mlq "$f" "outputs/${b}_out.txt"; done
```

## Informe

El informe esta en `docs/informe.tex`, listo para **Overleaf**:
1. Crear proyecto nuevo en https://www.overleaf.com y subir `informe.tex`.
2. Compilador **pdfLaTeX** -> *Recompile*.
3. Rellenar portada (integrantes, repo, video). Incluye la seccion de **Uso de IA**.

### En VS Code (Ctrl+Shift+B)

`.vscode/tasks.json` ya configurado para compilar todos los `.cpp` de `src/`.

## Notas de diseno

- BT y AT se manejan como enteros (los casos de prueba usan valores enteros).
- La prioridad del proceso se conserva como dato; el orden de despacho lo determina
  el numero de cola (Q1 > Q2 > Q3), coherente con el esquema MLQ elegido.
