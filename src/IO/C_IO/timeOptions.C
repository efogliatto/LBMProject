#include <timeOptions.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

    // Elapsed time
    const double elapsed (const struct solverInfo* info) {

	return (double (time(NULL) - info->time.st));

    }


    
    // Flag to enable writing
    const bool writeFlag(const struct solverInfo* info) {

	bool wrt = false;
	
	if (info->time.stp == info->time.writeInterval) {
	    wrt = true;
	}

	return wrt;
	
    }


    
    // Update time structure
    const bool updateTime(struct solverInfo* info) {

	bool upd = true;
	
    	// Update time
    	info->time.current += info->time.tstep;
	++info->time.stp;

	if ( info->time.current > info->time.end ) {
	    upd = false;
	}

	if( info->time.stp > info->time.writeInterval) {
	    info->time.stp = 0;
	}

	

	return upd;

    }

#ifdef __cplusplus
}
#endif    
