#ifndef WRITEVECTORFIELD_H
#define WRITEVECTORFIELD_H

#include <basicSolverInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    void writeVectorField(const char* fname, const double** field, const struct solverInfo* info);
    
#ifdef __cplusplus
}
#endif
    

#endif // WRITEVECTORFIELD_H
