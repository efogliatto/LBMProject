#ifndef PROFILEBOX_H
#define PROFILEBOX_H

#include <box.h>

class profileBox : public box {


protected:

    // Interface width
    double _width;

    // Inside value
    double _in;
    
    // Outside value
    double _out;
    

    /* ----------------------  Public member functions ----------------------  */

public:

    // Constructors and destructors

    // Default constructor
    profileBox();

    // Constructor with name
    profileBox(const std::string& name);

    // Default destructor
    ~profileBox();


    
    // Read properties
    void readProperties(const std::string& dictName);

    // Value
    const double value(const Vector3& v) const;

    // Value
    const double value(const Vector3& v, const double& val) const;

    
    // Check if point is inside the shape
    const bool locatePoint(const Vector3& v) const;  

};


#endif // PROFILEBOX_H
