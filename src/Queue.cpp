#include "Queue.h"
#include <algorithm>

Queue::Queue(int queueId, SchedulingPolicy* policy)
    : queueId(queueId), policy(policy) {}

int Queue::getId() const { return queueId; }

const std::string Queue::name() const { return policy->name(); }

void Queue::addProcess(Process* p) { ready.push_back(p); }

bool Queue::hasReady() const { return !ready.empty(); }

Process* Queue::selectNext() const { return policy->select(ready); }

void Queue::remove(Process* p) {
    auto it = std::find(ready.begin(), ready.end(), p);
    if (it != ready.end()) ready.erase(it);
}

// Mueve el proceso al final de la cola (rotacion de Round Robin).
void Queue::rotate(Process* p) {
    remove(p);
    ready.push_back(p);
}

int Queue::getQuantum() const { return policy->getQuantum(); }

bool Queue::rotatesOnQuantum() const { return policy->rotatesOnQuantum(); }
