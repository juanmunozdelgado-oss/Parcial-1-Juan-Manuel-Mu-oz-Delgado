#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include <vector>
#include "Process.h"

// ---------------------------------------------------------------------------
// FileParser: lee un archivo de entrada y construye la lista de procesos.
// Formato por linea:  etiqueta;BT;AT;Q;Prioridad
// Ignora lineas vacias y lineas que empiezan con '#'.
// ---------------------------------------------------------------------------
class FileParser {
public:
    // Lanza std::runtime_error si el archivo no se puede abrir.
    static std::vector<Process> parse(const std::string& path);
};

#endif // FILE_PARSER_H
