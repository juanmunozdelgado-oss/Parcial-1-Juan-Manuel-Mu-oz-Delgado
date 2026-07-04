#include "SJF.h"

// Elige el proceso con menor Burst Time. En empate, el que llego primero
// (los procesos se insertan en la cola en orden de llegada, asi que el
// primero encontrado en el recorrido gana el desempate).
Process* SJF::select(const std::deque<Process*>& ready) const {
    if (ready.empty()) return nullptr;

    Process* shortest = ready.front();
    for (Process* p : ready) {
        if (p->getBurstTime() < shortest->getBurstTime()) {
            shortest = p;
        }
    }
    return shortest;
}

// -1: sin rebanada de tiempo, el proceso corre hasta completarse
// (salvo que una cola de mayor prioridad lo expropie, lo maneja el scheduler).
int SJF::getQuantum() const { return -1; }

bool SJF::rotatesOnQuantum() const { return false; }

std::string SJF::name() const { return "SJF"; }
