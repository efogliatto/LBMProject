// Read information for c-written solvers


#include <dictionary.h>
#include <readBoundaryConditions.h>


#ifdef __cplusplus
extern "C" {
#endif


    void readBoundaryConditions( struct bdInfo* info ) {

	
	// BC dictionary
	dictionary dict("start/boundaryConditions");

	
	// Fields list
	vector<string> fields = dict.lookUpEntryList<string>("fields");

	
	// Resize struct
	info->_nf     = fields.size();
	info->_fields = (char**)malloc( info->_nf * sizeof(char*) );
	
	info->_bc     = (uint**)malloc( info->_nf * sizeof(uint*) );
	for( uint i = 0 ; i < info->_nf ; i++ )
	    info->_bc[i] = (uint*)malloc( info->_nb * sizeof(uint) );

	
	info->_value = (double***)malloc( info->_nf * sizeof(double**) );
	
	for( uint i = 0 ; i < info->_nf ; i++ ) {

	    info->_value[i] = (double**)malloc( info->_nb * sizeof(double*) );

	    for( uint j = 0 ; j < info->_nb ; j++ ) {

		info->_value[i][j] = (double*)malloc( 3 * sizeof(double) );

	    }
	    
	}

	
	// Read info for each field
	
	/*
	  Boundary conditions
	     0: none
	     0: periodic
	     1: bounceBack
	     2: fixedU
	     3: fixedP
	     4: fixedT
	     5: adiabatic
	 */
	
	for( uint fieldId = 0 ; fieldId < fields.size() ; fieldId++ ) {


	    // Copy field name
	    info->_fields[fieldId] = new char[fields[fieldId].length() + 1];
	    strcpy(info->_fields[fieldId], fields[fieldId].c_str());

	    
	    // Read each boundary
	    for( uint bcId = 0 ; bcId < info->_nb ; bcId++ ) {

		std::ostringstream entrytype; 
		entrytype << fields[fieldId] << "/boundaryConditions/" << info->_bdNames[bcId] << "/type";
		
		string bctype = dict.lookUpEntry<string>( entrytype.str() );

		
		if( bctype.compare("none") == 0 )          { info->_bc[fieldId][bcId] = 0; }

		
		if( bctype.compare("periodic") == 0 )      { info->_bc[fieldId][bcId] = 0; }

		
		if( bctype.compare("bounceBack") == 0 )    { info->_bc[fieldId][bcId] = 1; }

		
		if( bctype.compare("fixedU") == 0 ) {
		    
		    info->_bc[fieldId][bcId] = 2;

		    std::ostringstream entryval; 
		    entryval << fields[fieldId] << "/boundaryConditions/" << info->_bdNames[bcId] << "/value";		    

		    Vector3 val = dict.lookUpEntry<Vector3>( entryval.str() );

		    info->_value[fieldId][bcId][0] = val.x();
		    info->_value[fieldId][bcId][1] = val.y();
		    info->_value[fieldId][bcId][2] = val.z();
		    
		}

		
		if( bctype.compare("fixedP") == 0 ) {

		    info->_bc[fieldId][bcId] = 3;

		    std::ostringstream entryval; 
		    entryval << fields[fieldId] << "/boundaryConditions/" << info->_bdNames[bcId] << "/value";		    
		    
		    double val = dict.lookUpEntry<double>( entryval.str() );

		    info->_value[fieldId][bcId][0] = val;
		    info->_value[fieldId][bcId][1] = val;
		    info->_value[fieldId][bcId][2] = val;		    

		}

		
		if( bctype.compare("fixedT") == 0 )  {

		    info->_bc[fieldId][bcId] = 4;

		    std::ostringstream entryval; 
		    entryval << fields[fieldId] << "/boundaryConditions/" << info->_bdNames[bcId] << "/value";		    
		    
		    double val = dict.lookUpEntry<double>( entryval.str() );

		    info->_value[fieldId][bcId][0] = val;
		    info->_value[fieldId][bcId][1] = val;
		    info->_value[fieldId][bcId][2] = val;		    
		    
		}

		
		if( bctype.compare("adiabatic") == 0 ) {

		    info->_bc[fieldId][bcId] = 5;

		    std::ostringstream entryval; 
		    entryval << fields[fieldId] << "/boundaryConditions/" << info->_bdNames[bcId] << "/normal"; 
		    
		    double val = dict.lookUpEntry<double>( entryval.str() );

		    info->_value[fieldId][bcId][0] = val;
		    info->_value[fieldId][bcId][1] = val;
		    info->_value[fieldId][bcId][2] = val;		    

		}


		
	    }	    

	    
	}


	
    }



#ifdef __cplusplus
}
#endif
