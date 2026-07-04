#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "SchedulingPolicy.h"

// Round Robin: FIFO con rebanada de tiempo (quantum) configurable.
class RoundRobin : public SchedulingPolicy {
private:
    int quantum;

public:
    explicit RoundRobin(int quantum);

    Process* select(const std::deque<Process*>& ready) const override;
    int getQuantum() const override;
    bool rotatesOnQuantum() const override;
    std::string name() const override;
};

#endif // ROUND_ROBIN_H
