#ifndef QUEUE_H
#define QUEUE_H

#include <deque>
#include "Process.h"
#include "SchedulingPolicy.h"

// ---------------------------------------------------------------------------
// Queue: agrupa una lista de procesos listos + la politica que la gobierna.
// No decide entre colas (eso lo hace MLQScheduler); solo administra SU cola.
// ---------------------------------------------------------------------------
class Queue {
private:
    int queueId;                 // numero de cola (1, 2, 3)
    SchedulingPolicy* policy;    // RR o SJF (la cola NO es duenia del puntero)
    std::deque<Process*> ready;  // procesos listos, en orden de llegada

public:
    Queue(int queueId, SchedulingPolicy* policy);

    int getId() const;
    const std::string name() const;

    void addProcess(Process* p);   // agrega al final (orden de llegada)
    bool hasReady() const;         // hay procesos listos?

    Process* selectNext() const;   // delega en la politica (no lo remueve)
    void remove(Process* p);       // saca un proceso (cuando termina)
    void rotate(Process* p);       // lo manda al final (RR tras agotar quantum)

    int getQuantum() const;
    bool rotatesOnQuantum() const;
};

#endif // QUEUE_H
