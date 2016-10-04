#ifndef TIMEINFO_H
#define TIMEINFO_H

#include <scalars_C.h>
#include <time.h>
#include <sys/time.h>
#include <scalars_C.h>

struct timeInfo {

    // Simulation parameters

    // Start time
    unsigned int start;

    // End time
    unsigned int end;

    // Current time
    unsigned int current;

    
    // Time step
    c_scalar tstep;

    // Write interval (write every writeInterval steps)
    unsigned int writeInterval;

    // Start time (time measurement)
    time_t st;
    struct timeval stt;

    // Time step (inside write intrval)
    unsigned int stp;
    
    
};


#endif // TIMEINFO_H
