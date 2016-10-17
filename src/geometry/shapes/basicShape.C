#include <basicShape.h>

using namespace std;


/* ----------------------  Public member functions ----------------------  */


// Constructors and destructors

// Default constructor
basicShape::basicShape() : _inside(true) {}

// Default destructor
basicShape::~basicShape() {}



// Access members

// Shape volume
const double& basicShape::vol() const {
    return _volume;
}


// Shape area
const double& basicShape::area() const {
    return _area;
}


// Shape name
const std::string& basicShape::name() const {
    return _name;
}


// Bounding box limits
const tuple<Vector3, Vector3> basicShape::boundingBox() const {
    return std::make_tuple(_bbox_min, _bbox_max);
}


// Boundary names
const vector<string> basicShape::boundaryNames() const {
    vector<string> c;
    return c;
}


// Check the patch that contains a point
const string basicShape::pointOverBoundary(const Vector3& v, const double& tol) const {
    string s;
    return s;
}




// Check if point is inside the shape
const bool basicShape::locatePoint(const Vector3& v) const {
    return true;
}



// Reading properties
void basicShape::readProperties(const string& dictName) {}


// Value
const double basicShape::value(const Vector3& v) const {
    return 1.0;
}

// Value
const double basicShape::value(const Vector3& v, const double& val) const {
    return val;
}


// Value
const Vector3 basicShape::value( const Vector3& v, const Vector3& in, const Vector3& out ) const {
    
    Vector3 a;

    if( locatePoint(v) ) {
	a = in;
    }

    else {
	a = out;
    }

    return a;
    
}
