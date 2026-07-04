#ifndef SJF_H
#define SJF_H

#include "SchedulingPolicy.h"

// Shortest Job First (no expropiativo dentro de la cola).
// Elige, entre los procesos listos, el de menor Burst Time.
class SJF : public SchedulingPolicy {
public:
    Process* select(const std::deque<Process*>& ready) const override;
    int getQuantum() const override;        // -1 => corre hasta terminar
    bool rotatesOnQuantum() const override;  // no rota
    std::string name() const override;
};

#endif // SJF_H
