#ifndef MLQ_SCHEDULER_H
#define MLQ_SCHEDULER_H

#include <vector>
#include "Process.h"
#include "Queue.h"
#include "SchedulingPolicy.h"

// ---------------------------------------------------------------------------
// MLQScheduler: orquesta la simulacion del reloj global.
//
// Esquema fijo:  Q1 = RR(1),  Q2 = RR(3),  Q3 = SJF
// Despacho entre colas: PRIORIDAD ESTRICTA con EXPROPIACION.
//   - Siempre corre la cola de mayor prioridad (menor Q) que tenga listos.
//   - Si mientras corre un proceso de una cola llega uno a una cola de MAYOR
//     prioridad, el actual se expropia y conserva su tiempo restante.
//
// Nota: la referencia a los Process vive en el vector<Process> del llamador.
// Ese vector NO debe modificarse (ni redimensionarse) mientras se simula,
// para que los punteros que guardan las colas sigan siendo validos.
// ---------------------------------------------------------------------------
class MLQScheduler {
private:
    std::vector<Process>& processes;         // referencia a los procesos reales
    std::vector<Queue> queues;               // colas ordenadas por prioridad
    std::vector<SchedulingPolicy*> policies; // punteros propios (se liberan aqui)

    void addArrivals(int time, std::vector<bool>& enqueued);
    Queue* highestPriorityReady();
    bool higherPriorityHasReady(int currentQueueId);

public:
    explicit MLQScheduler(std::vector<Process>& processes);
    ~MLQScheduler();

    void run(); // ejecuta la simulacion y llena las metricas de cada proceso
};

#endif // MLQ_SCHEDULER_H
