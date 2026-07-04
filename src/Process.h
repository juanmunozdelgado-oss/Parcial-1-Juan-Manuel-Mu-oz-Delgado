#ifndef PROCESS_H
#define PROCESS_H

#include <string>

// ---------------------------------------------------------------------------
// Process: contenedor de datos. NO tiene logica de planificacion.
// Guarda los datos de entrada (BT, AT, Q, Pr) y las metricas de salida.
// ---------------------------------------------------------------------------
class Process {
private:
    // --- Datos de entrada (vienen del archivo .txt) ---
    std::string label;    // etiqueta del proceso (ej. "A")
    int burstTime;        // BT: tiempo total de CPU que necesita
    int arrivalTime;      // AT: instante en que llega al sistema
    int queueId;          // Q: numero de cola asignada (1, 2, 3)
    int priority;         // Pr: nivel de prioridad (5 alta, 1 baja)

    // --- Estado interno de la simulacion ---
    int remainingTime;    // CPU que le falta por ejecutar
    bool started;         // ya se ejecuto al menos una vez? (para RT)

    // --- Metricas calculadas (salida) ---
    int waitTime;         // WT = TAT - BT
    int completionTime;   // CT: instante en que termina
    int responseTime;     // RT: primer instante de ejecucion - AT
    int turnaroundTime;   // TAT = CT - AT

public:
    Process(const std::string& label, int burstTime, int arrivalTime,
            int queueId, int priority);

    // --- Getters de datos de entrada ---
    std::string getLabel() const;
    int getBurstTime() const;
    int getArrivalTime() const;
    int getQueueId() const;
    int getPriority() const;

    // --- Getters/setters de estado ---
    int getRemainingTime() const;
    void setRemainingTime(int rt);
    bool hasStarted() const;
    void markStarted();
    bool isFinished() const;

    // --- Getters/setters de metricas ---
    int getWaitTime() const;
    void setWaitTime(int wt);
    int getCompletionTime() const;
    void setCompletionTime(int ct);
    int getResponseTime() const;
    void setResponseTime(int rt);
    int getTurnaroundTime() const;
    void setTurnaroundTime(int tat);
};

#endif // PROCESS_H
