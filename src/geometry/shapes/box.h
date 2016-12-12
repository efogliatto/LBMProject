#ifndef BOX_H
#define BOX_H

#include <basicShape.h>
#include <map>

class box : public basicShape {


    /* ----------------------  Public member functions ----------------------  */

protected:

    // Boundary weight
    std::map<std::string, int> _bdw;

    

    /* ----------------------  Public member functions ----------------------  */

public:

    // Constructors and destructors

    // Default constructor
    box();

    // Constructor with name
    box(const std::string& name);

    // Default destructor
    ~box();


    // Access members

    // Shape volume
    virtual const double& vol() const;

    // Shape area
    virtual const double& area() const;

    // Shape name
    virtual const std::string& name() const;

    // Bounding box limits
    virtual const std::tuple<Vector3, Vector3> boundingBox() const;

    // Check if point is inside the shape
    virtual const bool locatePoint(const Vector3& v) const;

    // Boundary names
    virtual const std::vector<std::string> boundaryNames() const;

    // Check the boundary that contains a point
    virtual const std::string pointOverBoundary(const Vector3& v, const double& tol = 0) const;



    // Value
    virtual const double value(const Vector3& v) const;

    // Value
    virtual const double value(const Vector3& v, const double& val) const;

    

    // Member modification

    // Reading properties
    virtual void readProperties(const std::string& dictName);


};


#endif // BOX_H
