#ifndef WRITESCALARFIELD_H
#define WRITESCALARFIELD_H

#include <basicSolverInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    void writeScalarField( char* fname, c_scalar* field, struct solverInfo* info);
    
#ifdef __cplusplus
}
#endif
    

#endif // WRITESCALARFIELD_H
