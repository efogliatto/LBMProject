#ifndef VECTOR3_H
#define VECTOR3_H

#include <scalars.h>
#include <iostream>
#include <istream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Vector3 {


    /* ----------------------  Private members ----------------------  */


    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & _x;
        ar & _y;
        ar & _z;
    }
    
    // Cartesian coordinates
    scalar _x,
	_y,
	_z;



    /* ----------------------  Public member functions ----------------------  */


    public:

    // Constructors and destructors
    
    // Default constructor. Vector at origin
    Vector3();

    // Constructor with position
    Vector3(const scalar& x, const scalar& y, const scalar& z);

    // Default destructor
    ~Vector3();



    // Access members

    // Coordinate x
    const scalar& x() const;

    // Coordinate y
    const scalar& y() const;

    // Coordinate z
    const scalar& z() const;



    // Member modification

    // Coordinate x
    const void setX(const scalar& x);

    // Coordinate y
    const void setY(const scalar&  y);

    // Coordinate z
    const void setZ(const scalar& z);



    // Operation on vectors

    // Squared length
    const scalar sqMag() const;

    // Dot product
    const double operator* (const Vector3& rv) const;

    // Product by scalar
    const Vector3 operator* (const scalar& sc) const;

    // Division by scalar
    const Vector3 operator/ (const scalar& sc) const;

    // Addition
    const Vector3 operator+ (const Vector3& rv) const;

    // Addition
    Vector3& operator+= (const Vector3& rv);

    // Substraction
    const Vector3 operator- (const Vector3& rv) const;

    // Comparison
    const bool operator== (const Vector3& rv) const;

    // Overloaded operator <<
    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);

    // Overloaded operator <<
    friend std::istream& operator >> (std::istream& is, Vector3& v);
    
};

#endif // VECTOR3_H
