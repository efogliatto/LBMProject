#ifndef READNEIGHBOURS_H
#define READNEIGHBOURS_H

#include <latticeInfo.h>
#include <mpiInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    int** readNeighbours( const struct latticeInfo* lattice, const struct mpiInfo* parallel );
    
#ifdef __cplusplus
}
#endif
    

#endif // READNEIGHBOURS_H
