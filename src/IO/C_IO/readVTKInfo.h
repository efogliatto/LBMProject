#ifndef READVTKINFO_H
#define READVTKINFO_H

#include <vtkInfo.h>
#include <latticeInfo.h>
#include <mpiInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct vtkInfo readVTKInfo( const struct latticeInfo* lattice, const struct mpiInfo* parallel );
    
#ifdef __cplusplus
}
#endif
    

#endif // READVTKINFO_H
