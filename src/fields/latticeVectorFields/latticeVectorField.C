#include <latticeVectorField.h>

using namespace std;


// Constructors and destructors

// Constructor with references
latticeVectorField::latticeVectorField( basicLBModel* lbm,
					mpi::environment& env,
					mpi::communicator& world,
					const string& name,
					const Time& time,
					const bool& read ) : latticeField<Vector3>( lbm, env, world, name, time, read ){

    // Read from VTK file
    if( read == false ) {

	ostringstream fileName;
	fileName << "processor" << _id << "/" << _time.currentTime() << "/fields.vtu";

	// Open file
	ifstream inFile;
	inFile.open( fileName.str().c_str() );
	if( !inFile.is_open() ) {
	    cout << "Unable to open file " << fileName << endl;
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
		for(vector<Vector3>::iterator it = _localValues.begin() ; it != _localValues.end() ; ++it) {
		    double x,y,z;
		    inFile >> x;
		    inFile >> y;
		    inFile >> z;
		    *it = Vector3(x,y,z);
		}
		    
		// Read ghost values
		for(vector<Vector3>::iterator it = _ghostValues.begin() ; it != _ghostValues.end() ; ++it) {
		    double x,y,z;
		    inFile >> x;
		    inFile >> y;
		    inFile >> z;
		    *it = Vector3(x,y,z);
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
latticeVectorField::~latticeVectorField() {}



// Read values from current time
void latticeVectorField::readAllValues() {

    
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

    double x,y,z;


    // Read values
    for(vector<Vector3>::iterator it = this->_localValues.begin() ; it != this->_localValues.end() ; it++) {
	inFile >> x;
	inFile >> y;
	inFile >> z;
	*it = Vector3(x,y,z);
    }

    
    // Read values
    for(vector<Vector3>::iterator it = this->_ghostValues.begin() ; it != this->_ghostValues.end() ; it++) {
	inFile >> x;
	inFile >> y;
	inFile >> z;
	*it = Vector3(x,y,z);
    }
        

}
