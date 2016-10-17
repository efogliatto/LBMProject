#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <Vector3.h>
#include <dictionary.h>
#include <tuple>

class basicShape {


    /* ----------------------  Protected members ----------------------  */

protected:

    // Basic properties

    // Volume
    double _volume;

    // Area
    double _area;

    // Shape name
    std::string _name;

    // Bounding box vertices
    Vector3 _bbox_min,
	_bbox_max;

    // Flag used to detect points		
    bool _inside;
   

    
    /* ----------------------  Public member functions ----------------------  */

public:

    // Constructors and destructors

    // Default constructor
    basicShape();

    // Default destructor
    ~basicShape();



    // Access members

    // Shape volume
    virtual const double& vol() const = 0;

    // Shape area
    virtual const double& area() const = 0;

    // Shape name
    virtual const std::string& name() const = 0;

    // Bounding box limits
    virtual const std::tuple<Vector3, Vector3> boundingBox() const = 0;

    // Check if point is inside the shape
    virtual const bool locatePoint(const Vector3& v) const = 0;

    // Patch names
    virtual const std::vector<std::string> boundaryNames() const = 0;

    // Check the patch that contains a point
    virtual const std::string pointOverBoundary(const Vector3& v, const double& tol = 0) const = 0;




    // Member modification

    // Reading properties
    virtual void readProperties(const std::string& dictName) = 0;

    // Value
    virtual const double value(const Vector3& v) const;

    // Value
    virtual const double value(const Vector3& v, const double& val) const;

    // Value
    virtual const Vector3 value( const Vector3& v, const Vector3& in, const Vector3& out ) const;    
    
};


#endif // SHAPE_H
