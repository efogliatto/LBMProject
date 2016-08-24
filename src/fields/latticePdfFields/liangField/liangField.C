#include <liangField.h>

using namespace std;



// Constructors and destructors

// Constructor with references
liangField::liangField( basicLBModel* lbm,
				      mpi::environment& env,
				      mpi::communicator& world,
				      const string& name,
				      const Time& time,
				      const bool& read ) : latticePdfField( lbm, env, world, name, time, read ) {
    

    // Read relaxation parameters
    dictionary prop("properties/macroscopicProperties");

    _phi_A = prop.lookUpEntry<double>("Macro/phi_A");

    _phi_B = prop.lookUpEntry<double>("Macro/phi_B");

    _rho_A = prop.lookUpEntry<double>("Macro/rho_A");

    _rho_B = prop.lookUpEntry<double>("Macro/rho_B");

    _diag_S_a = prop.lookUpEntry<pdf>(name + "/S_a");

    _diag_S_b = prop.lookUpEntry<pdf>(name + "/S_b");

    _M = prop.lookUpEntry<double>("Macro/M_phi");

    _G = prop.lookUpEntry<Vector3>(name + "/G");
    
}

// Default destructor
liangField::~liangField() {}





// Link scalars field
const void liangField::add( latticeScalarField* scfield ) {

    // Order parameter
    if( scfield->name().compare("phi") == 0 ) { _phi = scfield; }
    
    else {
	
	// Pressure
	if( scfield->name().compare("p") == 0 ) { _p = scfield; }

	else {
	
	    // Chemical potential
	    if( scfield->name().compare("muPhi") == 0 ) { _muPhi = scfield; }

	    else {

		// Density
		if( scfield->name().compare("rho") == 0 ) { _rho = scfield; }

		else {

		    cout << "Unable to link field " << scfield->name() << endl << endl;
		    exit(1);

		}
	    }
	
	}	
	
    }

}



// Link vector field
const void liangField::add( latticeVectorField* vfield ) {

    // Velocity
    if( vfield->name().compare("U") == 0 ) { _U = vfield; }

    else {

	cout << "Unable to link field " << vfield->name() << endl << endl;
	exit(1);
    }    

}




// MRT collision matrix
const Matrix liangField::collisionMatrixA() const {

    // Construct S using diagonal elements
    Matrix S( _diag_S_a.size() );
    for(uint i = 0 ; i < _diag_S_a.size() ; i++)
	S[i][i] = _diag_S_a[i];

    return _lbm->invM() * S * _lbm->M();

}
const Matrix liangField::collisionMatrixB() const {

    // Construct S using diagonal elements
    Matrix S( _diag_S_b.size() );
    for(uint i = 0 ; i < _diag_S_b.size() ; i++)
	S[i][i] = _diag_S_b[i];

    return _lbm->invM() * S * _lbm->M();

}


// Source term
const Matrix liangField::sourceMatrixA() const {

    // Construct S using diagonal elements
    Matrix S( _diag_S_a.size() );
    for(uint i = 0 ; i < _diag_S_a.size() ; i++)
	S[i][i] = 1.0 - (0.5 * _diag_S_a[i]);

    return _lbm->invM() * S * _lbm->M();    

}

const Matrix liangField::sourceMatrixB() const {

    // Construct S using diagonal elements
    Matrix S( _diag_S_b.size() );
    for(uint i = 0 ; i < _diag_S_b.size() ; i++)
	S[i][i] = 1.0 - (0.5 * _diag_S_b[i]);

    return _lbm->invM() * S * _lbm->M();    

}



// Update zeroth and first moment fields
const void liangField::update() {


    // First moment velocity and pressure)

    latticeVectorField::iterator _U_iter = _U->begin();
    latticeScalarField::iterator _p_iter = _p->begin();
    
    // for(liangField::iterator it = begin() ; it != end() ; ++it) {
	
    	// // Update
    	// *_U_iter = it.firstMoment();
    	// *_p_iter = it.zerothMoment( *_U_iter );
	
    	++_U_iter;
    	++_p_iter;
    // }


    // // Density
    // for(std::pair<LiangField::iterator, latticeScalarField::iterator> it(begin(), rho->begin()) ; it.first != end() ; ++it.first, ++it.second) {
    // 	it.second->setOldValue( it.second->value() );
    // 	it.second->setNodeValue( it.first.density() );
    // }



    // // Synchronize
    // syncGhostValues();
    // rho->syncGhostValues();
    // pField->syncGhostValues();
    // UField->syncGhostValues();

}
