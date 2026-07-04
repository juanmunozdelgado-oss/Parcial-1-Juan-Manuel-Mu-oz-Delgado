#include "Process.h"

Process::Process(const std::string& label, int burstTime, int arrivalTime,
                 int queueId, int priority)
    : label(label),
      burstTime(burstTime),
      arrivalTime(arrivalTime),
      queueId(queueId),
      priority(priority),
      remainingTime(burstTime), // al inicio le falta ejecutar todo el BT
      started(false),
      waitTime(0),
      completionTime(0),
      responseTime(-1),         // -1 = aun no ha respondido
      turnaroundTime(0) {}

// --- Datos de entrada ---
std::string Process::getLabel() const { return label; }
int Process::getBurstTime() const     { return burstTime; }
int Process::getArrivalTime() const   { return arrivalTime; }
int Process::getQueueId() const       { return queueId; }
int Process::getPriority() const      { return priority; }

// --- Estado ---
int Process::getRemainingTime() const  { return remainingTime; }
void Process::setRemainingTime(int rt) { remainingTime = rt; }
bool Process::hasStarted() const       { return started; }
void Process::markStarted()            { started = true; }
bool Process::isFinished() const       { return remainingTime <= 0; }

// --- Metricas ---
int Process::getWaitTime() const         { return waitTime; }
void Process::setWaitTime(int wt)        { waitTime = wt; }
int Process::getCompletionTime() const   { return completionTime; }
void Process::setCompletionTime(int ct)  { completionTime = ct; }
int Process::getResponseTime() const     { return responseTime; }
void Process::setResponseTime(int rt)    { responseTime = rt; }
int Process::getTurnaroundTime() const   { return turnaroundTime; }
void Process::setTurnaroundTime(int tat) { turnaroundTime = tat; }
