#ifndef LBSTREAM_H
#define LBSTREAM_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>
#include <syncPdfField.h>

void lbstream( struct twoPhasesFields* fields, const struct solverInfo* info, double** fld );

#endif // LBSTREAM_H
