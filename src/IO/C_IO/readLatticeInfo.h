#ifndef READLATTICEINFO_H
#define READLATTICEINFO_H

#include <latticeInfo.h>
#include <timeInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct latticeInfo readLatticeInfo( struct timeInfo* t_info, int pid );
    
#ifdef __cplusplus
}
#endif


#endif // READLATTICEINFO_H
