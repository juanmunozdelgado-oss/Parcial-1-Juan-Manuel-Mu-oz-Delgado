#ifndef SCHEDULING_POLICY_H
#define SCHEDULING_POLICY_H

#include <deque>
#include <string>
#include "Process.h"

// ---------------------------------------------------------------------------
// SchedulingPolicy: clase abstracta (interfaz) que define COMO una cola elige
// el siguiente proceso a ejecutar. RoundRobin y SJF la implementan.
//
// Contrato:
//   - select(): dado el conjunto de procesos listos, devuelve cual ejecutar
//               (NO lo saca de la cola; solo decide).
//   - getQuantum(): rebanada de tiempo. <= 0 significa "correr hasta terminar".
//   - rotatesOnQuantum(): true si al agotar el quantum el proceso va al final
//               (comportamiento de Round Robin).
// ---------------------------------------------------------------------------
class SchedulingPolicy {
public:
    virtual ~SchedulingPolicy() {}

    virtual Process* select(const std::deque<Process*>& ready) const = 0;
    virtual int getQuantum() const = 0;
    virtual bool rotatesOnQuantum() const = 0;
    virtual std::string name() const = 0;
};

#endif // SCHEDULING_POLICY_H
