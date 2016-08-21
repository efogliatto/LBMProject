#include <Vector3.h>

using namespace std;


/* ----------------------  Public member functions ----------------------  */


// Constructors and destructors
    
// Default constructor. Vector at origin
Vector3::Vector3() {
    _x = 0;
    _y = 0;
    _z = 0;
}

// Constructor with position
Vector3::Vector3(const scalar& x, const scalar& y, const scalar& z) {
    _x = x;
    _y = y;
    _z = z;
}

// Default destructor
Vector3::~Vector3() {}



// Access members

// Coordinate x
const scalar& Vector3::x() const {
    return _x;
}

// Coordinate y
const scalar& Vector3::y() const {
    return _y;
}

// Coordinate z
const scalar& Vector3::z() const {
    return _z;
}



// Member modification

// Coordinate x
const void Vector3::setX(const scalar& x) {
    _x = x;
}

// Coordinate y
const void Vector3::setY(const scalar&  y) {
    _y = y;
}

// Coordinate z
const void Vector3::setZ(const scalar& z) {
    _z = z;
}




// Operation on vectors

// Squared length
const scalar Vector3::sqMag() const {
    return _x*_x + _y*_y + _z*_z;
}

// Dot product
const scalar Vector3::operator* (const Vector3& rv) const {
    return _x * rv._x  +  _y * rv._y  +  _z * rv._z; 
}

// Product by scalar
const Vector3 Vector3::operator* (const scalar& sc) const {
    return Vector3(_x*sc, _y*sc, _z*sc);
}

// Division by scalar
const Vector3 Vector3::operator/ (const scalar& sc) const {
    return (*this)*(1/sc);
}

// Addition
const Vector3 Vector3::operator+ (const Vector3& rv) const {
    return Vector3( _x+rv._x, _y+rv._y, _z+rv._z);
}

// Addition
Vector3& Vector3::operator+= (const Vector3& rv) {
    _x += rv._x; 
    _y += rv._y; 
    _z += rv._z; 
    return (*this);
}

// Substraction
const Vector3 Vector3::operator- (const Vector3& rv) const {
    return Vector3( _x-rv._x, _y-rv._y, _z-rv._z);
}


// Comparison
const bool Vector3::operator== (const Vector3& rv) const {
    return ( rv._x == _x )   &&   ( rv._y == _y )   &&   ( rv._z == _z );
}


// Overloaded operator <<
ostream& operator<< (ostream& os, const Vector3& v) {
    os << "( " << v._x << " " << v._y << " " << v._z << " )"; 
    return os;
}



// Overloaded operator <<
istream& operator >> (istream& is, Vector3& v) {

    string aux,
	x,
	y,
	z;

    // Read "("
    is >> aux;

    // Read x component
    is >> x;

    // Read y component
    is >> y;

    // Read z component
    is >> z;

    // Read ")"
    is >> aux;

    v.setX( stod(x) );
    v.setY( stod(y) );
    v.setZ( stod(z) );

    return is;
    
    
}
