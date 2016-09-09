#include <profileBox.h>
#include <cmath>

using namespace std;



/* ----------------------  Public member functions ----------------------  */


// Constructors and destructors

// Default constructor
profileBox::profileBox() : box() {}

// Default constructor
profileBox::profileBox(const string& name) : box() {
    _name = name;
}



// Default destructor
profileBox::~profileBox() {}


// Read properties
void profileBox::readProperties(const std::string& dictName) {

    // Call base class method
    box::readProperties( dictName );

    
    // Extra properties
        
    dictionary dict(dictName);

    _width = dict.lookUpEntry<double>( _name + "/width" );
    
}



// Value
const double profileBox::value(const Vector3& v) const {
    return tanh(2 * (  sqrt( v.y() - 0.5*_bbox_max.y() + 0.5*_bbox_min.y()  )  - _bbox_max.y()) / _width);
}


// Value
const double profileBox::value(const Vector3& v, const double& val) const {
    return -val * tanh(   ( 2 * (v.y() - _bbox_max.y()) ) / _width   ) ;
}



// Check if point is inside(outside) the shape
const bool profileBox::locatePoint(const Vector3& v) const {


    bool is_inside = ( v.x() >= (_bbox_min.x()-_width) ) && ( v.x() <= (_bbox_max.x()+_width) )  &&  ( v.y() >= (_bbox_min.y()-_width) ) && ( v.y() <= (_bbox_max.y()+_width) ) && ( v.z() >= (_bbox_min.z()-_width) ) && ( v.z() <= (_bbox_max.z()+_width) );
    
    return is_inside == _inside;
    
}
