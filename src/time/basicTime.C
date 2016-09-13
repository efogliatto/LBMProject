#include <iostream>
#include <basicTime.h>
#include <dictionary.h>


using namespace std;

/* ----------------------  Public member functions ----------------------  */

// Default constructor
basicTime::basicTime() :  _start(std::chrono::system_clock::now() )  {


    // Read simulation properties
    dictionary dict("properties/simulation");

    // Start time
    _startTime = (uint)dict.lookUpEntry<double>("startTime");
    _currentTime = _startTime;

    // End time
    _endTime = (uint)dict.lookUpEntry<double>("endTime");

    // Write interval
    _writeInterval = (uint)dict.lookUpEntry<double>("writeInterval");
    
    // Time step (dt)
    _timeStep = dict.lookUpEntry<scalar>("timeStep");

    // Flag to enable VTK writing
    string prop = dict.lookUpEntry<string>("writeVTK");
    _writeVTK = (prop.compare("true") == 0) ? true : false;

    _countTs = 0;
    _countVTK = 0;

}


// Default Destructor
basicTime::~basicTime() {}


// The copy-constructor
basicTime::basicTime(const basicTime& t) {
    _startTime = t._startTime;
    _endTime   = t._endTime;
    _writeInterval = t._writeInterval;
    _currentTime = t._currentTime;
    _timeStep = t._timeStep;
    _countTs = t._countTs;
    _countVTK = t._countVTK;
}





// Access members
    
// StartTime
const uint basicTime::startTime() const {
    return _startTime;
}

// End time
const uint basicTime::endTime() const {
    return _endTime;
}

// Write interval
const uint basicTime::writeInterval() const {
    return _writeInterval;
}


// Current time
const uint basicTime::currentTime() const {
    return _currentTime;
}

// Time step
const double basicTime::timeStep() const {
    return _timeStep;
}

// Move one time step
const bool basicTime::update() {

    // Update time indices
    _currentTime++;
    _countTs++;

    // Update write index
    if( _countTs > _writeInterval) {
	_countTs = 1;
    }    

    return ( _currentTime > _endTime ) ? false : true;
    // if(  _currentTime > _endTime  ) {
    // 	return false;
    // }
    // else{
    // 	return true;
    // }    

}

// Detect if time is at the end
const bool basicTime::end() const{

    return ( _currentTime > _endTime ) ? true : false;
    
    // if(_currentTime + _timeStep > _endTime) {
    // 	return true;
    // }
    // else{
    // 	return false;
    // }
}



// Number of time steps
const uint basicTime::countTs() const {
    return _countTs;
}



// Flag that enables writing
const bool basicTime::write() const {

    return( _countTs == _writeInterval) ? true : false;
    
    // if ( ((_countTs % _writeInterval) == 0 ) ) {
    // 	return true;
    // }
    // else {
    // 	return false;
    // }

}


// Elapsed time
const double basicTime::elapsedTime() const {

    chrono::time_point<std::chrono::system_clock> end;
    end = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-_start;

    return elapsed_seconds.count();
}




// Flag to enable VTK writing
const bool basicTime::writeVTK() const {
    return _writeVTK;
}


// Update vtk count
const void basicTime::updateVTK() {
    _countVTK++;
}

const uint basicTime::countVTK() const {
    return _countVTK;
}


// Write in ascii format
const bool basicTime::ascii() const {

    bool f = false;
    
    if ( _format.compare("ascii") == 0 )
	f = true;

    return f;
    
}
