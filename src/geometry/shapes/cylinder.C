#include <cylinder.h>
#include <cmath>

using namespace std;



/* ----------------------  Public member functions ----------------------  */


// Constructors and destructors

// Default constructor
cylinder::cylinder() : basicShape() {}

// Default constructor
cylinder::cylinder(const string& name) : basicShape() {
    _name = name;
}



// Default destructor
cylinder::~cylinder() {}



// Access members

// Shape volume
const double& cylinder::vol() const{
    return basicShape::vol();
}

// Shape area
const double& cylinder::area() const {
    return basicShape::area();
}

// Shape name
const string& cylinder::name() const {
    return basicShape::name();
}

// Bounding box limits
const tuple<Vector3, Vector3> cylinder::boundingBox() const {
    return basicShape::boundingBox();
}



// Check if point is inside(outside) the shape
const bool cylinder::locatePoint(const Vector3& v) const {

    Vector3 u( v.x() - _origin.x(), v.y() - _origin.y(), 0);    
    
    bool is_inside = ( u.sqMag() <= _radius*_radius );
    
    return is_inside == _inside;
}




// Boundary names
const vector<string> cylinder::boundaryNames() const {

    vector<string> names;
    names.push_back(_name);
    
    // if(!_inside) {
    // 	names.push_back(_name);
    // }
    // else {

    // 	if ( _bbox_min.x() != _bbox_max.x() ){
    // 	    names.push_back(_name + "_X0");
    // 	    names.push_back(_name + "_X1");
    // 	}
    // 	if ( _bbox_min.y() != _bbox_max.y() ){
    // 	    names.push_back(_name + "_Y0");
    // 	    names.push_back(_name + "_Y1");
    // 	}
    // 	if ( _bbox_min.z() != _bbox_max.z() ){
    // 	    names.push_back(_name + "_Z0");
    // 	    names.push_back(_name + "_Z1");
    // 	}

    // }

    return names;

}





// Member modification

// Reading properties
void cylinder::readProperties(const string& dictName) {

    dictionary dict(dictName);

    // Origin
    _origin = dict.lookUpEntry<Vector3>( _name + "/origin" );

    // Axis
    _axis = dict.lookUpEntry<Vector3>( _name + "/axis" );

    // Radius
    _radius = dict.lookUpEntry<double>( _name + "/radius" );

    // Height
    _height = dict.lookUpEntry<double>( _name + "/height" );

    
    // Bounding box
    _bbox_min = Vector3( _origin.x() - _radius, _origin.y() - _radius, _origin.z()  );
    _bbox_max = Vector3( _origin.x() + _radius, _origin.y() + _radius, _origin.z() + _height  );    

    // Inside
    string inside = dict.lookUpEntry<string>( _name + "/inside" );
    if(inside.find("true") != string::npos) { _inside = true;  }
    else{ _inside = false; }

    
    // Set properties
    _volume = 3.141592654 * _radius * _radius ;

}






// Check the patch that contains a point
const string cylinder::pointOverBoundary(const Vector3& v, const double& tol) const {

    string patch;

    Vector3 u( v.x() - _origin.x(), v.y() - _origin.y(), 0);

    if( u.sqMag() <= (_radius*_radius + tol) ) {
	patch = _name;
    }


    // if(!_inside && !patch.empty()) {patch = _name;}


    return patch;
}
