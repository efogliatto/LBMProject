#ifndef TIMEOPTIONS_H
#define TIMEOPTIONS_H

#include <timeInfo.h>
#include <readNeighbours.h>
#include <basicSolverInfo.h>
#include <readBasicInfo.h>
#include <readScalarField.h>
#include <readVectorField.h>
#include <readPdfField.h>


#ifdef __cplusplus
extern "C" {
#endif

    // Elapsed time
    const double elapsed (const struct timeInfo* info);

    // Flag to enable writing
    const int writeFlag(const struct timeInfo* info);

    // Update time structure
    const int updateTime(struct timeInfo* info);
    
    
#ifdef __cplusplus
}
#endif
    

#endif // TIMEOPTIONS_H
