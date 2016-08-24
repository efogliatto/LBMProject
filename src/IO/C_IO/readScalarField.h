#ifndef READSCALARFIELD_H
#define READSCALARFIELD_H

#include <basicSolverInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    double* readScalarField(const char* fname, const struct solverInfo* info);
    
#ifdef __cplusplus
}
#endif
    

#endif // READSCALARFIELD_H
