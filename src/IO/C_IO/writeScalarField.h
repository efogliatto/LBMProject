#ifndef WRITESCALARFIELD_H
#define WRITESCALARFIELD_H

#include <basicSolverInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    void writeScalarField( char* fname, double* field, struct solverInfo* info);
    
#ifdef __cplusplus
}
#endif
    

#endif // WRITESCALARFIELD_H
