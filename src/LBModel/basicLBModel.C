#include <basicLBModel.h>

using namespace std;



/* ----------------------  Public member functions ----------------------  */



// Constructors and destructors

// Default constructor
basicLBModel::basicLBModel() {}

// Default destructor
basicLBModel::~basicLBModel() {}

// // The copy-constructor
// LBMmodel(const LBMmodel& lbm)




// Access members

// Discrete lattice velocities
const vector<Vector3>& basicLBModel::latticeVel() const {
    return _latticeVel;
}

// Dimension
const uint& basicLBModel::D() const {
    return _D;
}

// Number of lattice velocities
const uint basicLBModel::Q() const {
    return _latticeVel.size();
}

// Square of sound speed (normaliced by lattice velocity)
const scalar& basicLBModel::cs2() const {
    return _cs2;
}

// Lattice size
const scalar& basicLBModel::c() const {
    return _c;
}

// PDF weights
const scalar& basicLBModel::omega(const uint& id) const {
    return _omega[id];
}

// PDF weights
const vector<scalar>& basicLBModel::omega() const {
    return _omega;
}

// Reverse index
const uint& basicLBModel::reverse(const uint& id) const {
    return _reverse.at(id);
}

// Reverse index
const vector<uint>& basicLBModel::reverse() const {
    return _reverse;
}


// Specular index
const uint& basicLBModel::specular(const uint& id) const {
    return _specular.at(id);
}

const vector<uint>& basicLBModel::specular() const {
    return _specular;
}


// Model name
const string& basicLBModel::name() const {
    return _name;
}

// Velocity with id
const Vector3& basicLBModel::at(const uint& id) const {
    return _latticeVel[id]; 
}


// Velocity index
const int basicLBModel::velId( const Vector3& v ) const {

    int id(-1);
    
    for(uint i = 0 ; i < _latticeVel.size() ; i++) {

	// Scalar product
	if(   (v*_latticeVel[i])   ==   ( v.sqMag() * _latticeVel[i].sqMag() )   ) {
	    id = i;
	}
	
    }

    return id;
    
}









// Member modification

// Set lattice size
const void basicLBModel::setSpeed() {

    dictionary lat("properties/latticeProperties");
    _lsize = lat.lookUpEntry<double>("latticeSize");

    dictionary tfile("properties/simulation");
    double dt = tfile.lookUpEntry<double>("timeStep");
    
    _c = _lsize / dt;
    
}




// Main index
const bool basicLBModel::is_principal(const uint& id) const {
    return false;
}


// Lattice Size
const double& basicLBModel::lsize() const {
    return _lsize;
}




// PDF weights
const pdf& basicLBModel::pdfOmega() const {
    return _pdfomega;
}


// MRT matrices
const Matrix& basicLBModel::M() const {  return _M;  }

const Matrix& basicLBModel::invM() const {  return _invM;  }



// Principal indices
const vector< vector<uint> >& basicLBModel::principal() const {
    return _principal;
}
