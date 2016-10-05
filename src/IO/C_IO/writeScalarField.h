#ifndef WRITESCALARFIELD_H
#define WRITESCALARFIELD_H

#include <latticeInfo.h>
#include <mpiInfo.h>
#include <timeInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    void writeScalarField( char* fname, c_scalar* field, const struct latticeInfo* lattice, const struct mpiInfo* parallel, const struct timeInfo* time);
    
#ifdef __cplusplus
}
#endif
    

#endif // WRITESCALARFIELD_H
