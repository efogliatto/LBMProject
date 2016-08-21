#include <Matrix.h>
#include <iostream>

using namespace std;



// Constructors and destructors

// Default constructor
Matrix::Matrix() : vector< vector<double> >() {}

// Constructor with size
Matrix::Matrix(const uint& sz) {  
    this->resize(sz);  
    for(uint i = 0 ; i < sz ; i++)
	(*this)[i].resize(sz, 0.0);
}

// Constructor with size
Matrix::Matrix(const uint& rs, const uint& cs) {
    this->resize(rs);
    for(uint i = 0 ; i < rs ; i++)
	(*this)[i].resize(cs);
}

// Default destructor
Matrix::~Matrix() {}





// Overloaded operator <<
ostream& operator<<(ostream& os, const Matrix& c) {

    // os << "( ";
    for(uint i = 0 ; i < c.size() ; i++) {
	for(uint j = 0 ; j < c[i].size() ; j++) {
	    os << c[i][j] << " ";
	}
	// os << ";" << endl;
	if(i != (c.size()-1))
	    os << endl;
    }
    // os << ")";

    return os;

}

// // Overloaded operator <<
// istream& operator >> (istream& is, pdf& c) {

//     string aux;

//     // Read "("
//     is >> aux;
    
//     is >> aux;
//     while ( aux.find(")") == string::npos ) {
//     	c.push_back( stod(aux) );
//     	is >> aux;
//     }

//     return is;
    
// }






// Overloaded operators

// Addition
const Matrix Matrix::operator+ (const Matrix& rv) const {

    Matrix a(size());
    
    if(rv.size() == size()) {
    	for(uint i = 0 ; i < rv.size() ; i++) {
	    for(uint j = 0 ; j < rv[i].size() ; j++) {
		a[i][j] = rv[i][j] + (*this)[i][j];
	    }
    	}
    }
    else {
    	cout << endl << "******ERROR******" << endl << "Unable to add matrices. Size mismatch" << endl << endl;
    	exit(1);
    }

    return a;
    
}



// Substraction
const Matrix Matrix::operator- (const Matrix& rv) const {

    Matrix a(size());

    if(rv.size() == size()) {
    	for(uint i = 0 ; i < rv.size() ; i++) {
	    for(uint j = 0 ; j < rv[i].size() ; j++) {
		a[i][j] = (*this)[i][j] - rv[i][j];
	    }
    	}
    }
    else {
    	cout << endl << "******ERROR******" << endl << "Unable to add matrices. Size mismatch" << endl << endl;
    	exit(1);
    }


    return a;
    
}


// Product by scalar
const Matrix Matrix::operator* (const scalar& sc) const {
    Matrix a = (*this);
    for(uint i = 0 ; i < a.size() ; i++) {
	for(uint j = 0 ; j < a[i].size() ; j++) {
	    a[i][j] = sc * a[i][j];
	}
    }
    return a;
}



// Product by pdf
const pdf Matrix::operator* (const pdf& rv) const {

    pdf a;
    a.resize(size(), 0.0);

    for(uint i = 0 ; i < size() ; i++) {
    	for(uint j = 0 ; j < rv.size() ; j++) {
    	    a[i] += rv[j] * (*this)[i][j];
    	}
    }

    return a;
}


// Matrix product
const Matrix Matrix::operator* (const Matrix& rv) const {

    Matrix a( size(), rv[0].size() );

    for(uint i = 0 ; i < a.size() ; i++) {
	for(uint j = 0 ; j < a[i].size() ; j++) {
	    for(uint k = 0 ; k < (*this)[i].size() ; k++) {
		a[i][j] += (*this)[i][k] * rv[k][j];
	    }
	}
    }

    return a;

}
