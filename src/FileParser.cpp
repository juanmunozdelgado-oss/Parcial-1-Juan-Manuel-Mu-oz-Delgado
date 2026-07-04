#include "FileParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

// Quita espacios en blanco al inicio y al final de una cadena.
static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

std::vector<Process> FileParser::parse(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo de entrada: " + path);
    }

    std::vector<Process> processes;
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;
        std::string clean = trim(line);

        // Ignorar lineas vacias y comentarios (#).
        if (clean.empty() || clean[0] == '#') continue;

        // Separar por ';'
        std::stringstream ss(clean);
        std::string token;
        std::vector<std::string> fields;
        while (std::getline(ss, token, ';')) {
            fields.push_back(trim(token));
        }

        if (fields.size() < 5) {
            throw std::runtime_error(
                "Linea " + std::to_string(lineNumber) +
                " con formato invalido (se esperaban 5 campos): " + line);
        }

        std::string label = fields[0];
        int bt  = std::stoi(fields[1]);
        int at  = std::stoi(fields[2]);
        int q   = std::stoi(fields[3]);
        int pr  = std::stoi(fields[4]);

        processes.emplace_back(label, bt, at, q, pr);
    }

    return processes;
}
