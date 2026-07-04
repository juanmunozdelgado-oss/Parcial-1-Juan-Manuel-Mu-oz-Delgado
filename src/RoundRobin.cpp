#include "RoundRobin.h"

RoundRobin::RoundRobin(int quantum) : quantum(quantum) {}

// RR es FIFO: siempre ejecuta el que esta al frente de la cola.
Process* RoundRobin::select(const std::deque<Process*>& ready) const {
    if (ready.empty()) return nullptr;
    return ready.front();
}

int RoundRobin::getQuantum() const { return quantum; }

// En RR, si el proceso agota el quantum sin terminar, va al final de la cola.
bool RoundRobin::rotatesOnQuantum() const { return true; }

std::string RoundRobin::name() const { return "RR(" + std::to_string(quantum) + ")"; }
