#include <latticeScalarField.h>

using namespace std;


// Constructors and destructors

// Constructor with references
latticeScalarField::latticeScalarField( basicLBModel* lbm,
					mpi::environment& env,
					mpi::communicator& world,
					const string& name,
					const Time& time,
					const bool& read ) : latticeField<double>( lbm, env, world, name, time, read ){

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

    	    	// Read local values
    	    	for(vector<double>::iterator it = _localValues.begin() ; it != _localValues.end() ; ++it)
    	    	    inFile >> *it;

    	    	// Read ghost values
    	    	for(vector<double>::iterator it = _ghostValues.begin() ; it != _ghostValues.end() ; ++it)
    	    	    inFile >> *it;

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
latticeScalarField::~latticeScalarField() {}


// Read values from current time
void latticeScalarField::readAllValues() {

    
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
    for(vector<double>::iterator it = this->_localValues.begin() ; it != this->_localValues.end() ; it++) {
	inFile >> *it;
    }

    
    // Read values
    for(vector<double>::iterator it = this->_ghostValues.begin() ; it != this->_ghostValues.end() ; it++) {
	inFile >> *it;
    }

    inFile.close();
        

}



// Write values in binary format to current time
void latticeScalarField::writeBinary() {

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
    for(vector<double>::iterator it = this->_localValues.begin() ; it != this->_localValues.end() ; it++) {
    	double val = *it;
    	outFile.write( (char*)&val, sizeof(double) );
    }

    
    // Write ghost values
    for(vector<double>::iterator it = this->_ghostValues.begin() ; it != this->_ghostValues.end() ; it++) {
    	double val = *it;
    	outFile.write( (char*)&val, sizeof(double) );
    }    

    outFile.close();
    
}
