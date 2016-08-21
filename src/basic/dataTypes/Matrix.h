#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <istream>
#include <pdf.h>

class Matrix : public std::vector< std::vector<double> > {

    
public:


    // Constructors and destructors

    // Default constructor
    Matrix();

    // Constructor with size
    Matrix(const uint& sz);

    // Constructor with size
    Matrix(const uint& rs, const uint& cs);

    // Default destructor
    ~Matrix();

    
    // Overloaded operator <<
    friend std::ostream& operator<<(std::ostream& os, const Matrix& c);
    
    // Overloaded operator <<
    friend std::istream& operator >> (std::istream& is, Matrix& c);


    
    // Overloaded operators

    // Addition
    const Matrix operator+ (const Matrix& rv) const;

    // Substraction
    const Matrix operator- (const Matrix& rv) const;

    // Product by scalar
    const Matrix operator* (const double& sc) const;

    // Product by pdf
    const pdf operator* (const pdf& rv) const;

    // Matrix product
    const Matrix operator* (const Matrix& rv) const;
    
    
};

#endif // MATRIX_H
