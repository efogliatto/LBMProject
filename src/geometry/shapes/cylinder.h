#ifndef CYLINDER_H
#define CYLINDER_H

#include <basicShape.h>

class cylinder : public basicShape {


    /* ----------------------  Private members ----------------------  */

    // Origin
    Vector3 _origin;

    // Axis orientation
    Vector3 _axis;

    // Radius
    double _radius;

    // Height
    double _height;
    

    
    /* ----------------------  Public member functions ----------------------  */

public:

    // Constructors and destructors

    // Default constructor
    cylinder();

    // Constructor with name
    cylinder(const std::string& name);

    // Default destructor
    ~cylinder();


    // Access members

    // Shape volume
    const double& vol() const;

    // Shape area
    const double& area() const;

    // Shape name
    const std::string& name() const;

    // Bounding box limits
    const std::tuple<Vector3, Vector3> boundingBox() const;

    // Check if point is inside the shape
    const bool locatePoint(const Vector3& v) const;

    // Boundary names
    const std::vector<std::string> boundaryNames() const;

    // Check the boundary that contains a point
    const std::string pointOverBoundary(const Vector3& v, const double& tol = 0) const;




    // Member modification

    // Reading properties
    void readProperties(const std::string& dictName);


};


#endif // CYLINDER_H
