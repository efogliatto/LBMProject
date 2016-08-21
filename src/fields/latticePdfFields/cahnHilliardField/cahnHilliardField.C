#include <cahnHilliardField.h>

using namespace std;

// Constructors and destructors

// Constructor with references
cahnHilliardField::cahnHilliardField( basicLBModel* lbm,
				      mpi::environment& env,
				      mpi::communicator& world,
				      const string& name,
				      const Time& time,
				      const bool& read ) : latticePdfField( lbm, env, world, name, time, read ) {

    // Read relaxation parameters
    dictionary prop("properties/macroscopicProperties");

    _phi_A = prop.lookUpEntry<double>("Macro/phi_A");

    _phi_B = prop.lookUpEntry<double>("Macro/phi_B");

    _diag_S = prop.lookUpEntry<pdf>(name + "/S"); 

    _D = prop.lookUpEntry<double>(name + "/D");

    _sigma = prop.lookUpEntry<double>(name + "/sigma");

    // Compute parameters for chemical potential
    _kappa = 3 * _sigma * _D / (2 * (_phi_A - _phi_B) * (_phi_A - _phi_B));
    _beta  = 12 * _sigma / ( _D * pow(_phi_A - _phi_B, 4));

    // Mobility
    const double M = prop.lookUpEntry<double>("Macro/M_phi");
    _eta = M / (   _cs2 * time.timeStep() * (1/_diag_S[3] - 0.5)   );

}

// Default destructor
cahnHilliardField::~cahnHilliardField() {}


// Link zeroth field
const void cahnHilliardField::add( latticeScalarField* zerothField ) {

    _phi = zerothField;
    
}

// Link first field
const void cahnHilliardField::add( latticeVectorField* firstField ) {

    _U = firstField;

}

// Link chemical potential
const void cahnHilliardField::addChemical( latticeScalarField* chemical ) {

    _muPhi = chemical;
    
}



// MRT collision matrix
const Matrix cahnHilliardField::collisionMatrix() const {

    // Construct S using diagonal elements
    Matrix S( _diag_S.size() );
    for(uint i = 0 ; i < _diag_S.size() ; i++)
	S[i][i] = _diag_S[i];

    return _lbm->invM() * S * _lbm->M();

}


// Source term
const Matrix cahnHilliardField::sourceMatrix() const {

    // Construct S using diagonal elements
    Matrix S( _diag_S.size() );
    for(uint i = 0 ; i < _diag_S.size() ; i++)
	S[i][i] = 1.0 - (0.5 * _diag_S[i]);

    return _lbm->invM() * S * _lbm->M();

}



// Update zeroth and first moment fields
const void cahnHilliardField::update() {


    // Update external fields


    // Zeroth moment (order parameter)
    for(pair<cahnHilliardField::iterator, latticeScalarField::iterator> it(begin(), _phi->begin()) ; it.first != end() ; ++it.first, ++it.second) {

    	// Old values first
    	it.second.setOldValue( *it.second );
	
    	// Update
    	it.second.setSwapValue( *it.second );
    	*it.second = it.first.zerothMoment();
    }


    // Chemical potential
    for(pair<cahnHilliardField::iterator, latticeScalarField::iterator> it(begin(), _muPhi->begin()) ; it.first != end() ; ++it.first, ++it.second) {
    	it.second.setOldValue( *it.second );
    	*it.second = it.first.chemical();
    }


    // Synchronize
    syncGhostValues();
    _phi->syncGhostValues();
    _muPhi->syncGhostValues();

}
