// Read field for c-written solvers

#include <readLbeField.h>
#include <readPdfField.h>
#include <dictionary.h>

#ifdef __cplusplus
extern "C" {
#endif


    struct lbeField readLbeField( char* fname, const struct latticeInfo* lattice, const struct mpiInfo* parallel, const struct timeInfo* time ) {


	if(parallel->pid == 0) { printf("\nReading field %s\n", fname);  }

	
	struct lbeField field;


	// Read distribution values
	field.value = readPdfField(fname, lattice, parallel, time);
	field.swap  = readPdfField(fname, lattice, parallel, time);

	// Assign field name
	string name = fname;
	field.name = new char[ name.length() + 1];
	strcpy(field.name, name.c_str());

	

	// Read collision model
	dictionary macroDict("properties/macroscopicProperties");

	string model = macroDict.lookUpEntry<string>(name + "/Collision");

	
	// Assign model index
	if( model.compare("liMRT") == 0 ) {
	    
	    field.colId = 0;

	    // Read MRTs
	    pdf mrt = macroDict.lookUpEntry<pdf>(name + "/Lambda");

	    field.Lambda = new double[ mrt.size() ];
	    
	    for( uint i = 0 ; i < mrt.size() ; i++) {
		field.Lambda[i] = mrt[i];
	    }

	    field.sigma = macroDict.lookUpEntry<double>(name + "/sigma");


	    mrt = macroDict.lookUpEntry<pdf>(name + "/Lambda_A");
	    field.Lambda_A = new double[ mrt.size() ];
	    for( uint i = 0 ; i < mrt.size() ; i++) {	field.Lambda_A[i] = mrt[i];    }

	    mrt = macroDict.lookUpEntry<pdf>(name + "/Lambda_B");
	    field.Lambda_B = new double[ mrt.size() ];
	    for( uint i = 0 ; i < mrt.size() ; i++) {	field.Lambda_B[i] = mrt[i];    }	    
	    
	    field.kappa_A = macroDict.lookUpEntry<double>(name + "/kappa_A");
	    field.kappa_B = macroDict.lookUpEntry<double>(name + "/kappa_B");
	    
	}

	
	else {
	    
	    if( model.compare("liSRT") == 0 ) {
		
		field.colId = 1;

		// Read srt
		field.tau = macroDict.lookUpEntry<double>(name + "/tau");
		field.tau_A = macroDict.lookUpEntry<double>(name + "/tau_A");
		field.tau_B = macroDict.lookUpEntry<double>(name + "/tau_B");

		field.kappa_A = macroDict.lookUpEntry<double>(name + "/kappa_A");
		field.kappa_B = macroDict.lookUpEntry<double>(name + "/kappa_B");	
		
	    }
	    
	    else {
		
		if( model.compare("liTemp") == 0 ) {
		    
		    field.colId = 2;

		    // Read srt
		    field.tau = macroDict.lookUpEntry<double>(name + "/tau");
		    field.tau_A = macroDict.lookUpEntry<double>(name + "/tau_A");
		    field.tau_B = macroDict.lookUpEntry<double>(name + "/tau_B");

		    field.kappa_A = macroDict.lookUpEntry<double>(name + "/kappa_A");
		    field.kappa_B = macroDict.lookUpEntry<double>(name + "/kappa_B");		    
		    
		}
		
	    }
	    
	}

	


	

	return field;

    }


#ifdef __cplusplus
}
#endif
