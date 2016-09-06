#ifndef LBSTREAM_H
#define LBSTREAM_H

#include <basicSolverInfo.h>
#include <twoPhasesFields.h>
#include <syncPdfField.h>

void lbstream( struct twoPhasesFields* fields,  struct solverInfo* info, c_scalar** fld );

#endif // LBSTREAM_H
