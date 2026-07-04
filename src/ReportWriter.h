#ifndef REPORT_WRITER_H
#define REPORT_WRITER_H

#include <string>
#include <vector>
#include "Process.h"

// ---------------------------------------------------------------------------
// ReportWriter: escribe el archivo de salida con el formato exacto:
//   # etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT
//   A;6;0;1;5;3;9;0;9
//   ...
//   # WT=..; CT=..; RT=..; TAT=..;
// ---------------------------------------------------------------------------
class ReportWriter {
public:
    // 'inputName' se usa solo para el encabezado del archivo.
    static void write(const std::string& outputPath,
                      const std::string& inputName,
                      const std::vector<Process>& processes);
};

#endif // REPORT_WRITER_H
