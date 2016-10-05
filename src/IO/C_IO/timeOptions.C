#include <timeOptions.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

    // Elapsed time
    const double elapsed (const struct timeInfo* info) {

	struct timeval _end;
	gettimeofday( &_end, NULL );
	
	return (((double)_end.tv_sec + (double)_end.tv_usec / 1000000)  - ((double)info->stt.tv_sec + (double)info->stt.tv_usec / 1000000));
	
	// return (double (time(NULL) - info->time.st));

    }


    
    // Flag to enable writing
    const int writeFlag(const struct timeInfo* info) {

	int wrt = 0;
	
	if (info->stp == info->writeInterval) {
	    wrt = 1;
	}

	return wrt;
	
    }


    
    // Update time structure
    const int updateTime(struct timeInfo* info) {

	int upd = 1;
	
    	// Update time
    	++info->current;
	++info->stp;


	if ( info->current > info->end ) {
	    upd = 0;
	}

	if( info->stp > info->writeInterval) {
	    info->stp = 1;
	}

	

	return upd;

    }

#ifdef __cplusplus
}
#endif    
