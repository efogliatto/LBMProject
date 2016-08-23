#ifndef TIMEOPTIONS_H
#define TIMEOPTIONS_H

#include <basicSolverInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    // Elapsed time
    const double elapsed (const struct solverInfo* info);

    // Flag to enable writing
    const bool write(const struct solverInfo* info);

    // Update time structure
    const bool updateTime(struct solverInfo* info);
    
    
#ifdef __cplusplus
}
#endif
    

#endif // TIMEOPTIONS_H
