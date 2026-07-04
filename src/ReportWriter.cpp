#include "ReportWriter.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

// Formatea un promedio con 1 decimal (ej. 23.5).
static std::string avg1(double sum, int n) {
    std::ostringstream os;
    os << std::fixed << std::setprecision(1) << (n > 0 ? sum / n : 0.0);
    return os.str();
}

void ReportWriter::write(const std::string& outputPath,
                         const std::string& inputName,
                         const std::vector<Process>& processes) {
    std::ofstream out(outputPath);
    if (!out.is_open()) {
        throw std::runtime_error("No se pudo crear el archivo de salida: " + outputPath);
    }

    out << "# archivo: " << inputName << "\n";
    out << "# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT\n";

    double sumWT = 0, sumCT = 0, sumRT = 0, sumTAT = 0;

    for (const Process& p : processes) {
        out << p.getLabel() << ";"
            << p.getBurstTime() << ";"
            << p.getArrivalTime() << ";"
            << p.getQueueId() << ";"
            << p.getPriority() << ";"
            << p.getWaitTime() << ";"
            << p.getCompletionTime() << ";"
            << p.getResponseTime() << ";"
            << p.getTurnaroundTime() << "\n";

        sumWT  += p.getWaitTime();
        sumCT  += p.getCompletionTime();
        sumRT  += p.getResponseTime();
        sumTAT += p.getTurnaroundTime();
    }

    const int n = static_cast<int>(processes.size());
    out << "# WT=" << avg1(sumWT, n)
        << "; CT="  << avg1(sumCT, n)
        << "; RT="  << avg1(sumRT, n)
        << "; TAT=" << avg1(sumTAT, n) << ";\n";
}
