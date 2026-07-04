#include <iostream>
#include <string>
#include <vector>
#include "Process.h"
#include "FileParser.h"
#include "MLQScheduler.h"
#include "ReportWriter.h"

// Extrae el nombre de archivo de una ruta (para el encabezado de salida).
static std::string baseName(const std::string& path) {
    size_t slash = path.find_last_of("/\\");
    return (slash == std::string::npos) ? path : path.substr(slash + 1);
}

int main(int argc, char* argv[]) {
    // Uso:  mlq <entrada> [salida]
    // Por defecto: inputs/mlq001.txt -> outputs/mlq001_out.txt
    std::string inputPath  = (argc > 1) ? argv[1] : "inputs/mlq001.txt";
    std::string outputPath = (argc > 2) ? argv[2] : "outputs/mlq001_out.txt";

    try {
        // 1) Parsear
        std::vector<Process> processes = FileParser::parse(inputPath);
        std::cout << "Procesos leidos: " << processes.size()
                  << " desde " << inputPath << "\n";

        // 2) Simular
        MLQScheduler scheduler(processes);
        scheduler.run();

        // 3) Escribir salida
        ReportWriter::write(outputPath, baseName(inputPath), processes);
        std::cout << "Salida escrita en: " << outputPath << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
