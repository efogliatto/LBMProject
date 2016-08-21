#include <D3Q7.h>

using namespace std;


/* ----------------------  Public member functions ----------------------  */


// Constructors and destructors

// Default constructor
D3Q7::D3Q7() {
    
    // Model name
    _name = "D3Q7";

    // Dimension
    _D = 3;

    // Sound speed
    _cs2 = 1.0 / 3.0;


    // Discrete velocities
    _latticeVel.push_back(  Vector3(  0.0,  0.0,  0.0)  );
    _latticeVel.push_back(  Vector3(  1.0,  0.0,  0.0)  );
    _latticeVel.push_back(  Vector3(  0.0,  1.0,  0.0)  );
    _latticeVel.push_back(  Vector3(  0.0,  0.0,  1.0)  );
    _latticeVel.push_back(  Vector3( -1.0,  0.0,  0.0)  );
    _latticeVel.push_back(  Vector3(  0.0, -1.0,  0.0)  );
    _latticeVel.push_back(  Vector3(  0.0,  0.0, -1.0)  );    


    // PDF weights
    _omega.push_back( 4.0 / 9.0 );
    _omega.push_back( 1.0 / 2.0);
    _omega.push_back( 1.0 / 2.0 );
    _omega.push_back( 1.0 / 2.0 );
    _omega.push_back( 1.0 / 2.0 );
    _omega.push_back( 1.0 / 2.0 );    
    _omega.push_back( 1.0 / 2.0 );

    _pdfomega.push_back( 4.0 / 9.0 );
    _pdfomega.push_back( 1.0 / 2.0);
    _pdfomega.push_back( 1.0 / 2.0 );
    _pdfomega.push_back( 1.0 / 2.0 );
    _pdfomega.push_back( 1.0 / 2.0 );
    _pdfomega.push_back( 1.0 / 2.0 );    
    _pdfomega.push_back( 1.0 / 2.0 );

    // Reverse directions
    _reverse.push_back(0);
    _reverse.push_back(4);
    _reverse.push_back(5);
    _reverse.push_back(3);
    _reverse.push_back(1);
    _reverse.push_back(2); 
    _reverse.push_back(3);   
    
    // Specular directions
    _specular.push_back(0);
    _specular.push_back(1);
    _specular.push_back(2);
    _specular.push_back(3);
    _specular.push_back(4);
    _specular.push_back(5);
    _specular.push_back(6);    
    
}

// Default destructor
D3Q7::~D3Q7() {}



// Access members
const uint& D3Q7::D() const {
    return _D;
}


// Main index
const bool D3Q7::is_principal(const uint& id) const {
    return ( (id <= 6)  &&  (id > 0) ) ? true : false;    
}
