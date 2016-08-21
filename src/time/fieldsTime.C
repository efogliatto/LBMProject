#include <fieldsTime.h>


using namespace std;

/* ----------------------  Public member functions ----------------------  */

// Default constructor
fieldsTime::fieldsTime() : basicTime()  {}


// Default Destructor
fieldsTime::~fieldsTime() {}


// The copy-constructor
fieldsTime::fieldsTime(const fieldsTime& t) {
    _startTime = t._startTime;
    _endTime   = t._endTime;
    _writeInterval = t._writeInterval;
    _currentTime = t._currentTime;
    _timeStep = t._timeStep;
    _countTs = t._countTs;
    _countVTK = t._countVTK;
}






// Add field to map
const void fieldsTime::addExternalField(latticeScalarField* f) {

    if( _externalScalarFields.find( f->name() ) == _externalScalarFields.end() ) {
    	_externalScalarFields[ f->name() ] = f;
    }
    else {
    	cout << endl << "Unable to link field " << f->name() << endl;
    	cout << "Field allready exists" << endl;
    	exit(1);
    }
    
}



// Add field to map
const void fieldsTime::addExternalField(latticeVectorField* f) {

    if( _externalVectorFields.find( f->name() ) == _externalVectorFields.end() ) {
    	_externalVectorFields[ f->name() ] = f;
    }
    else {
    	cout << endl << "Unable to link field " << f->name() << endl;
    	cout << "Field allready exists" << endl;
    	exit(1);
    }
    
}



// Add field to map
const void fieldsTime::addExternalField(LBfield* f) {

    if( _externalLBfields.find( f->name() ) != _externalLBfields.end() ) {
    	_externalLBfields[ f->name() ] = f;
    }
    else {
    	cout << endl << "Unable to link field " << f->name() << endl;
    	cout << "Field allready exists" << endl;
    	exit(1);
    }
    
}






// Get reference to external latticeScalarField
const latticeScalarField* fieldsTime::getExternalScalarField(const std::string& fieldName) const{

    if( _externalScalarFields.find( fieldName ) != _externalScalarFields.end() ) {
    	return _externalScalarFields.at( fieldName );
    }
    else {
    	cout << endl << "Unable to find " << fieldName << endl;
    	exit(1);
    }

}


// Get reference to external latticeScalarField
latticeVectorField* fieldsTime::getExternalVectorField(const std::string& fieldName) {
    if( _externalVectorFields.find( fieldName ) != _externalVectorFields.end() ) {
    	return _externalVectorFields[ fieldName ];
    }
    else {
	cout << endl << "Unable to find " << fieldName << endl;
    	exit(1);
    }
    
}


// Get reference to external latticeScalarField
LBfield* fieldsTime::getExternalLBfield(const std::string& fieldName) {
    if( _externalLBfields.find( fieldName ) != _externalLBfields.end() ) {
    	return _externalLBfields[ fieldName ];
    }
    else {
	cout << endl << "Unable to find " << fieldName << endl;
    	exit(1);	
    }
}
