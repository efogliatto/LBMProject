#include <bubble.h>
#include <cmath>

using namespace std;



/* ----------------------  Public member functions ----------------------  */


// Constructors and destructors

// Default constructor
bubble::bubble() : sphere() {}

// Default constructor
bubble::bubble(const string& name) : sphere() {
    _name = name;
}



// Default destructor
bubble::~bubble() {}


// Read properties
void bubble::readProperties(const std::string& dictName) {

    // Call base class method
    sphere::readProperties( dictName );

    
    // Extra properties
        
    dictionary dict(dictName);

    _width = dict.lookUpEntry<double>( _name + "/width" );    
    
}



// Value
const double bubble::value(const Vector3& v) const {
    return tanh(2 * ( sqrt((v-_origin).sqMag()) - _radius) / _width);
}
