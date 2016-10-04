#ifndef READSCALARFIELD_H
#define READSCALARFIELD_H

#include <latticeInfo.h>
#include <mpiInfo.h>
#include <timeInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    c_scalar* readScalarField(const char* fname, const struct latticeInfo* lattice, const struct mpiInfo* parallel, const struct timeInfo* time);
    
#ifdef __cplusplus
}
#endif
    

#endif // READSCALARFIELD_H
