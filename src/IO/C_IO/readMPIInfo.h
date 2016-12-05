#ifndef READMPIINFO_H
#define READMPIINFO_H

#include <mpiInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct mpiInfo readMPIInfo( int pid, int sz, int nlocal );
    
#ifdef __cplusplus
}
#endif


#endif // READMPIINFO_H
