#ifndef BUBBLE_H
#define BUBBLE_H

#include <sphere.h>

class bubble : public sphere {


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
    bubble();

    // Constructor with name
    bubble(const std::string& name);

    // Default destructor
    ~bubble();


    
    // Read properties
    void readProperties(const std::string& dictName);

    // Value
    const double value(const Vector3& v) const;

    // Value
    const Vector3 value( const Vector3& v, const Vector3& in, const Vector3& out ) const;

    // Value
    const double value(const Vector3& v, const double& val) const;

    
    // Check if point is inside the shape
    const bool locatePoint(const Vector3& v) const;    

};


#endif // BUBBLE_H
