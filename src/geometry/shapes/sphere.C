#include <sphere.h>
#include <cmath>

using namespace std;



/* ----------------------  Public member functions ----------------------  */


// Constructors and destructors

// Default constructor
sphere::sphere() : basicShape() {}

// Default constructor
sphere::sphere(const string& name) : basicShape() {
    _name = name;
}



// Default destructor
sphere::~sphere() {}



// Access members

// Shape volume
const double& sphere::vol() const{
    return basicShape::vol();
}

// Shape area
const double& sphere::area() const {
    return basicShape::area();
}

// Shape name
const string& sphere::name() const {
    return basicShape::name();
}

// Bounding box limits
const tuple<Vector3, Vector3> sphere::boundingBox() const {
    return basicShape::boundingBox();
}





// Check if point is inside(outside) the shape
const bool sphere::locatePoint(const Vector3& v) const {

    bool is_inside = ( (v - _origin).sqMag()  <= (_radius * _radius) );
    
    return is_inside == _inside;
}




// Boundary names
const vector<string> sphere::boundaryNames() const {

    vector<string> names;

    names.push_back(_name);

    return names;

}





// Member modification

// Reading properties
void sphere::readProperties(const string& dictName) {

    dictionary dict(dictName);

    // Radius
    _radius = dict.lookUpEntry<double>( _name + "/radius" );

    // Centre
    _origin = dict.lookUpEntry<Vector3>( _name + "/origin" );


    // Inside
    string inside = dict.lookUpEntry<string>( _name + "/inside" );
    if(inside.find("true") != string::npos) { _inside = true;  }
    else{ _inside = false; }


    // Min bounding box
    _bbox_min = Vector3( _origin.x() - _radius,  _origin.y() - _radius,  _origin.z() - _radius  );

    // Min bounding box
    _bbox_max = Vector3( _origin.x() + _radius,  _origin.y() + _radius,  _origin.z() + _radius  );


    // Set properties
    _volume = 4 * 3.14159 * _radius * _radius * _radius / 3;
    _area = 4 * 3.14159 * _radius * _radius;

}






// Check the patch that contains a point
const string sphere::pointOverBoundary(const Vector3& v, const double& tol) const {

    string patch;

    Vector3 u( v.x() - _origin.x(), v.y() - _origin.y(), v.z() - _origin.z());

    if( u.sqMag() <= (_radius*_radius + tol) ) {
	patch = _name;
    }


    // if(!_inside && !patch.empty()) {patch = _name;}


    return patch;
    
}




