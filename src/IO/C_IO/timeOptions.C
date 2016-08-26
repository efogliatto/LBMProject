#include <timeOptions.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

    // Elapsed time
    const double elapsed (const struct solverInfo* info) {

	struct timeval _end;
	gettimeofday( &_end, NULL );
	
	return (((double)_end.tv_sec + (double)_end.tv_usec / 1000000)  - ((double)info->time.stt.tv_sec + (double)info->time.stt.tv_usec / 1000000));
	
	// return (double (time(NULL) - info->time.st));

    }


    
    // Flag to enable writing
    const int writeFlag(const struct solverInfo* info) {

	int wrt = 0;
	
	if (info->time.stp == info->time.writeInterval) {
	    wrt = 1;
	}

	return wrt;
	
    }


    
    // Update time structure
    const int updateTime(struct solverInfo* info) {

	int upd = 1;
	
    	// Update time
    	info->time.current += info->time.tstep;
	++info->time.stp;

	if ( info->time.current > info->time.end ) {
	    upd = 0;
	}

	if( info->time.stp > info->time.writeInterval) {
	    info->time.stp = 0;
	}

	

	return upd;

    }

#ifdef __cplusplus
}
#endif    
