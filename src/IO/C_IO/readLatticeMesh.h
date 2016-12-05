#ifndef READLATTICEMESH_H
#define READLATTICEMESH_H

#include <latticeMesh.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct latticeMesh readLatticeMesh( int pid, int sz );
    
#ifdef __cplusplus
}
#endif


#endif // READLATTICEMESH_H
