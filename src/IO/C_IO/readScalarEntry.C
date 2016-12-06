// Read field for c-written solvers

#include <readScalarEntry.h>
#include <dictionary.h>

#ifdef __cplusplus
extern "C" {
#endif


    double readScalarEntry(const char* fname, const char* entry) {

	std::ostringstream fileName;
	fileName << fname;
	dictionary dict(fileName.str());

	std::ostringstream entryName;
	entryName << entry;
	
	return dict.lookUpEntry<double>( entryName.str() );

    }


#ifdef __cplusplus
}
#endif
