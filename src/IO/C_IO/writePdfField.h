#ifndef WRITEPDFFIELD_H
#define WRITEPDFFIELD_H

#include <latticeInfo.h>
#include <mpiInfo.h>
#include <timeInfo.h>


#ifdef __cplusplus
extern "C" {
#endif

    void writePdfField( char* fname,  c_scalar** field, const struct latticeInfo* lattice, const struct mpiInfo* parallel, const struct timeInfo* time);
    
#ifdef __cplusplus
}
#endif
    

#endif // WRITEPDFFIELD_H
