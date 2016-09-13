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
    uint _startTime;

    // Simulation end
    uint _endTime;

    // Write interval;
    uint _writeInterval;

    // Current time
    uint _currentTime;

    // Time step
    double _timeStep;

    // Number of time steps (in write interval)
    uint _countTs;

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
    
    // Start Time
    const uint startTime() const;

    // End time
    const uint endTime() const;

    // Write interval
    const uint writeInterval() const;

    // Current time
    const uint currentTime() const;

    // Time step
    const double timeStep() const;

    // Move one time step
    const bool update();

    // Detect if time is at the end
    const bool end() const;

    // Number of time steps
    const uint countTs() const;

    // Flag that enables writing
    const bool write() const;

    // Elapsed time
    const double elapsedTime() const;

    // Flag to enable VTK writing
    const bool writeVTK() const;

    // Update vtk count
    const void updateVTK();

    const uint countVTK() const;

    // Write in ascii format
    const bool ascii() const;

};

#endif // BASICTIME_H
