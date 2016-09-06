#include <iostream>
#include <basicTime.h>
#include <dictionary.h>


using namespace std;

/* ----------------------  Public member functions ----------------------  */

// Default constructor
basicTime::basicTime() :  _start(std::chrono::system_clock::now() )  {


    // // Read simulation properties
    // cout << endl;
    // cout << "Reading time properties" << endl;
    // cout << endl;
    
    dictionary dict("properties/simulation");

    _startTime = dict.lookUpEntry<scalar>("startTime");
    _currentTime = _startTime;

    _endTime = dict.lookUpEntry<scalar>("endTime");

    _writeInterval = dict.lookUpEntry<scalar>("writeInterval");

    _timeStep = dict.lookUpEntry<scalar>("timeStep");

    string prop = dict.lookUpEntry<string>("writeVTK");
    _writeVTK = (prop.compare("true") == 0) ? true : false;

    // _format = dict.lookUpEntry<string>("format");

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
const double basicTime::startTime() const {
    return _startTime;
}

// End time
const double basicTime::endTime() const {
    return _endTime;
}

// Write interval
const int basicTime::writeInterval() const {
    return _writeInterval;
}


// Current time
const double basicTime::currentTime() const {
    return _currentTime;
}

// Time step
const double basicTime::timeStep() const {
    return _timeStep;
}

// Move one time step
const bool basicTime::update() {

    _currentTime += _timeStep;
    _countTs++;

    if(  _currentTime >= (_endTime + _timeStep)  ) {
	return false;
    }
    else{
	return true;
    }

}

// Detect if time is at the end
const bool basicTime::end() const{
    if(_currentTime + _timeStep > _endTime) {
	return true;
    }
    else{
	return false;
    }
}



// Number of time steps
const int basicTime::countTs() const {
    return _countTs;
}



// Flag that enables writing
const bool basicTime::write() const {

    // if ( ((_countTs % _writeInterval) == 0 )  &&  (_currentTime != _startTime) ) {
    if ( ((_countTs % _writeInterval) == 0 ) ) {
	return true;
    }
    else {
	return false;
    }

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

const int basicTime::countVTK() const {
    return _countVTK;
}


// Write in ascii format
const bool basicTime::ascii() const {

    bool f = false;
    
    if ( _format.compare("ascii") == 0 )
	f = true;

    return f;
    
}
