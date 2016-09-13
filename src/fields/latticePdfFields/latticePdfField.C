#include <latticePdfField.h>

using namespace std;


// Constructors and destructors

// Constructor with references
latticePdfField::latticePdfField( basicLBModel* lbm,
				  mpi::environment& env,
				  mpi::communicator& world,
				  const string& name,
				  const Time& time,
				  const bool& read) : latticeField<pdf>( lbm, env, world, name, time, read ){

    // Read from VTK file
    if( read == false ) {

	ostringstream fileName;
	fileName << "processor" << _id << "/" << _time.currentTime() << "/fields.vtu";

	// Open file
	ifstream inFile;
	inFile.open( fileName.str().c_str() );
	if( !inFile.is_open() ) {
	    cout << "Unable to open file " << fileName.str() << endl;
	    exit(1);
	}

	// Read file by word
	string word;
	while( !inFile.eof() ) {

	    inFile >> word;
	    if( word.compare("Name=\"" + name + "\"") == 0 ) {

		inFile >> word;
		inFile >> word;

		// Read local values
		for(vector<pdf>::iterator it = _localValues.begin() ; it != _localValues.end() ; ++it) {
		    
		    pdf val;
		    double el;
		    
		    for(uint i = 0 ; i < _lbm->Q() ; i++) {
		    	inFile >> el;
			val.push_back(el);
		    }
			
		    *it = val;
		    
		}
		    
		// Read ghost values
		for(vector<pdf>::iterator it = _ghostValues.begin() ; it != _ghostValues.end() ; ++it) {
		    
		    pdf val;
		    double el;
		    
		    for(uint i = 0 ; i < _lbm->Q() ; i++) {
		    	inFile >> el;
			val.push_back(el);
		    }
			
		    *it = val;
		    
		}

	    }
	    
	}
	

    }



    // Add swap and old values
    for(uint i = 0 ; i < _localValues.size() ; i++) {
	_swapValues[i] = _localValues[i];
	_oldValues[i] = _localValues[i];
    }    
    
}

// Default destructor
latticePdfField::~latticePdfField() {}




// Member modification

// Basic streamming
const void latticePdfField::stream() {

    // Sync values
    syncGhostValues();
    
    const uint nel = _neighbours.size(),
	nvel = _lbm->Q();
    
    // Move over neighbours
    for( uint i = 0 ; i < nel ; i++ ) {

	// Move over velocities
	for( uint j = 0 ; j < nvel ; j++ ) {
	
	    int neighId = _neighbours[i][j];

	    if( neighId != -1 ) {

		// Neighbour is local
		if( neighId < (int)nel ) {

		    _swapValues[i][j] = _localValues[neighId][j];

		}

		// Neighbour is ghost
		else {

		    _swapValues[i][j] = _ghostValues[neighId - nel][j];

		}

	    }

	}

    }


    // Swap values
    for( uint i = 0 ; i < nel ; i++ )
	_localValues[i] = _swapValues[i];


}



// Read values from current time
void latticePdfField::readAllValues() {

    
    std::ostringstream fldName;
    fldName << "processor" << this->_id << "/" << _time.currentTime() << "/" << _name;

    // Open file
    std::ifstream inFile;
    inFile.open( fldName.str().c_str() );
    if( !inFile.is_open() ) {
    	std::cout << "Unable to open file " << fldName.str() << std::endl;
    	exit(1);
    }

    // Read total number of elements and resize
    uint ntotal;
    inFile >> ntotal;


    // Read values
    for(vector<pdf>::iterator it = this->_localValues.begin() ; it != this->_localValues.end() ; it++) {

	for(uint i = 0 ; i < _lbm->Q() ; i++) {
	    inFile >> (*it)[i];
	}
	
    }

    
    // Read values
    for(vector<pdf>::iterator it = this->_ghostValues.begin() ; it != this->_ghostValues.end() ; it++) {

	for(uint i = 0 ; i < _lbm->Q() ; i++) {
	    inFile >> (*it)[i];
	}
	
    }
        

}



// Write values in binary format to current time
void latticePdfField::writeBinary() {

    std::ostringstream fldName;
    fldName << "processor" << this->_id << "/" << _time.currentTime() << "/" << _name << ".bin";

    // Open file
    ofstream outFile;
    outFile.open( fldName.str().c_str(), ios::out | ios::binary );
    if( !outFile.is_open() ) {
    	cout << "Unable to open file " << fldName.str() << endl;
    	exit(1);
    }


    // Write local  values
    for(vector<pdf>::iterator it = this->_localValues.begin() ; it != this->_localValues.end() ; it++) {
	
    	pdf val = *it;
	
	for(uint j = 0 ; j < val.size() ; j++)
	    outFile.write( (char*)&val[j], sizeof(double) );
	
    }

    
    // Write ghost values
    for(vector<pdf>::iterator it = this->_ghostValues.begin() ; it != this->_ghostValues.end() ; it++) {
	
    	pdf val = *it;
	
	for(uint j = 0 ; j < val.size() ; j++)
	    outFile.write( (char*)&val[j], sizeof(double) );
	
    }    

    outFile.close();
    
}
