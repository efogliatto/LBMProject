#ifndef READLBEFIELD_H
#define READLBEFIELD_H

#include <latticeInfo.h>
#include <mpiInfo.h>
#include <timeInfo.h>
#include <lbeField.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct lbeField readLbeField( char* fname, const struct latticeInfo* lattice, const struct mpiInfo* parallel, const struct timeInfo* time );
    
#ifdef __cplusplus
}
#endif
    

#endif // READLBEFIELD_H
