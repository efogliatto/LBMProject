#ifndef WRITESCALARFIELD_H
#define WRITESCALARFIELD_H

#include <basicSolverInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    void writeScalarField(const char* fname, const double* field, const struct solverInfo* info);
    
#ifdef __cplusplus
}
#endif
    

#endif // WRITESCALARFIELD_H
