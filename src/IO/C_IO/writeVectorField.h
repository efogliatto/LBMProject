#ifndef WRITEVECTORFIELD_H
#define WRITEVECTORFIELD_H

#include <latticeInfo.h>
#include <mpiInfo.h>
#include <timeInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    void writeVectorField( char* fname, c_scalar** field, const struct latticeInfo* lattice, const struct mpiInfo* parallel, const struct timeInfo* time);
    
#ifdef __cplusplus
}
#endif
    

#endif // WRITEVECTORFIELD_H
