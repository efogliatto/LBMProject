// Read time information for c-written solvers

#include <readTimeInfo.h>
#include <dictionary.h>

#ifdef __cplusplus
extern "C" {
#endif


    struct timeInfo readTimeInfo() {

	struct timeInfo info;

	// Read time properties
	dictionary tp("properties/simulation");

	info.start = (unsigned int)tp.lookUpEntry<double>("startTime");
	info.end = (unsigned int)tp.lookUpEntry<double>("endTime");
	info.tstep = (double)tp.lookUpEntry<double>("timeStep");
	info.writeInterval = (unsigned int)tp.lookUpEntry<double>("writeInterval");
	info.current = info.start;
	info.stp = 0;



	info.st = time( NULL );
    
	gettimeofday( &info.stt, NULL );
    
    
	return info;
    
    }


#ifdef __cplusplus
}
#endif
