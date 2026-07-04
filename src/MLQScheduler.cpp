#include "MLQScheduler.h"
#include "RoundRobin.h"
#include "SJF.h"

MLQScheduler::MLQScheduler(std::vector<Process>& processes)
    : processes(processes) {
    // Politicas del esquema elegido: RR(1), RR(3), SJF.
    policies.push_back(new RoundRobin(1)); // Q1
    policies.push_back(new RoundRobin(3)); // Q2
    policies.push_back(new SJF());         // Q3

    // Las colas se guardan en orden de prioridad: Q1 (indice 0) es la mas alta.
    queues.emplace_back(1, policies[0]);
    queues.emplace_back(2, policies[1]);
    queues.emplace_back(3, policies[2]);
}

MLQScheduler::~MLQScheduler() {
    for (SchedulingPolicy* p : policies) delete p;
}

// Devuelve la cola correspondiente a un queueId, o nullptr si no existe.
static Queue* findQueue(std::vector<Queue>& queues, int queueId) {
    for (Queue& q : queues) {
        if (q.getId() == queueId) return &q;
    }
    return nullptr;
}

// Encola todos los procesos cuyo AT <= time y que aun no han sido encolados.
void MLQScheduler::addArrivals(int time, std::vector<bool>& enqueued) {
    for (size_t i = 0; i < processes.size(); ++i) {
        if (!enqueued[i] && processes[i].getArrivalTime() <= time) {
            Queue* q = findQueue(queues, processes[i].getQueueId());
            if (q != nullptr) {
                q->addProcess(&processes[i]);
                enqueued[i] = true;
            }
        }
    }
}

// La cola de mayor prioridad (menor indice) que tenga procesos listos.
Queue* MLQScheduler::highestPriorityReady() {
    for (Queue& q : queues) {
        if (q.hasReady()) return &q;
    }
    return nullptr;
}

// Hay alguna cola de MAYOR prioridad que la actual con procesos listos?
bool MLQScheduler::higherPriorityHasReady(int currentQueueId) {
    for (Queue& q : queues) {
        if (q.getId() < currentQueueId && q.hasReady()) return true;
    }
    return false;
}

void MLQScheduler::run() {
    const int total = static_cast<int>(processes.size());
    std::vector<bool> enqueued(total, false);
    int completed = 0;
    int time = 0;

    while (completed < total) {
        addArrivals(time, enqueued);

        Queue* q = highestPriorityReady();
        if (q == nullptr) {
            // CPU ociosa: no hay listos todavia, avanza el reloj.
            ++time;
            continue;
        }

        Process* p = q->selectNext();
        const int quantum = q->getQuantum(); // <=0 => correr hasta terminar
        int slice = 0;

        // Ejecuta el proceso unidad por unidad para poder detectar expropiacion.
        while (!p->isFinished() && (quantum <= 0 || slice < quantum)) {
            // Registrar RT la primera vez que toma CPU.
            if (!p->hasStarted()) {
                p->markStarted();
                p->setResponseTime(time - p->getArrivalTime());
            }

            // Ejecutar una unidad de tiempo.
            p->setRemainingTime(p->getRemainingTime() - 1);
            ++time;
            ++slice;

            // Nuevas llegadas en el nuevo instante.
            addArrivals(time, enqueued);

            // Expropiacion: si llego algo a una cola de mayor prioridad, cortar.
            if (higherPriorityHasReady(q->getId())) break;
        }

        if (p->isFinished()) {
            // Completo: calcular metricas.
            p->setCompletionTime(time);
            p->setTurnaroundTime(p->getCompletionTime() - p->getArrivalTime());
            p->setWaitTime(p->getTurnaroundTime() - p->getBurstTime());
            q->remove(p);
            ++completed;
        } else if (q->rotatesOnQuantum() && slice == quantum) {
            // RR agoto su quantum sin terminar: al final de la cola.
            q->rotate(p);
        }
        // Si fue expropiado (slice < quantum) queda al frente para reanudar.
    }
}
