#ifndef BASICTIME_H
#define BASICTIME_H

#include <string>
#include <vector>
#include <dictionary.h>
#include <chrono>

class basicTime {


    /* ----------------------  Private members ----------------------  */

protected:
    
    // Simulation start
    double _startTime;

    // Simulation end
    double _endTime;

    // Write interval;
    int _writeInterval;

    // Current time
    double _currentTime;

    // Time step
    double _timeStep;

    // Number of time steps
    int _countTs;

    // Number of VTK files written
    int _countVTK;

    // Flag. Write also into VTK format
    bool _writeVTK;

    // Start time for elapsed time
    std::chrono::time_point<std::chrono::system_clock> _start;

    // Format. ascii or binary
    std::string _format;



public:

    /* ----------------------  Public member functions ----------------------  */

    // Default constructor
    basicTime();

    // Default Destructor
    ~basicTime();

    // The copy-constructor
    basicTime(const basicTime& t);



    // Access members
    
    // StartTime
    const double startTime() const;

    // End time
    const double endTime() const;

    // Write interval
    const int writeInterval() const;

    // Current time
    const double currentTime() const;

    // Time step
    const double timeStep() const;

    // Move one time step
    const bool update();

    // Detect if time is at the end
    const bool end() const;

    // Number of time steps
    const int countTs() const;

    // Flag that enables writing
    const bool write() const;

    // Elapsed time
    const double elapsedTime() const;

    // Flag to enable VTK writing
    const bool writeVTK() const;

    // Update vtk count
    const void updateVTK();

    const int countVTK() const;

    // Write in ascii format
    const bool ascii() const;

};

#endif // BASICTIME_H
