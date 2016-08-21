#include <D2Q5.h>

using namespace std;


/* ----------------------  Public member functions ----------------------  */


// Constructors and destructors

// Default constructor
D2Q5::D2Q5() {
    
    // Model name
    _name = "D2Q5";

    // Dimension
    _D = 2;

    // Sound speed
    _cs2 = 1.0 / 3.0;


    // Discrete velocities
    _latticeVel.push_back(  Vector3(  0.0,  0.0, 0.0)  );
    _latticeVel.push_back(  Vector3(  1.0,  0.0, 0.0)  );
    _latticeVel.push_back(  Vector3(  0.0,  1.0, 0.0)  );
    _latticeVel.push_back(  Vector3( -1.0,  0.0, 0.0)  );
    _latticeVel.push_back(  Vector3(  0.0, -1.0, 0.0)  );


    // PDF weights
    _omega.push_back( 4.0 / 9.0 );
    _omega.push_back( 1.0 / 2.0);
    _omega.push_back( 1.0 / 2.0 );
    _omega.push_back( 1.0 / 2.0 );
    _omega.push_back( 1.0 / 2.0 );

    _pdfomega.push_back( 4.0 / 9.0 );
    _pdfomega.push_back( 1.0 / 2.0);
    _pdfomega.push_back( 1.0 / 2.0 );
    _pdfomega.push_back( 1.0 / 2.0 );
    _pdfomega.push_back( 1.0 / 2.0 );

 


    // Reverse directions
    _reverse.push_back(0);
    _reverse.push_back(3);
    _reverse.push_back(4);
    _reverse.push_back(1);
    _reverse.push_back(2);

    
    // Specular directions
    _specular.push_back(0);
    _specular.push_back(1);
    _specular.push_back(2);
    _specular.push_back(3);
    _specular.push_back(4);
    
}

// Default destructor
D2Q5::~D2Q5() {}



// Access members
const uint& D2Q5::D() const {
    return _D;
}


// Main index
const bool D2Q5::is_principal(const uint& id) const {
    return ( (id <= 4)  &&  (id > 0) ) ? true : false;    
}
