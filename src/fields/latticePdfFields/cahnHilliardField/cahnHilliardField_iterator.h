#ifndef CAHNHILLIARDFIELD_ITERATOR_H
#define CAHNHILLIARDFIELD_ITERATOR_H

#include <lbPatch_iterator.h>
#include <latticeScalarField.h>

typedef vector< std::pair<uint, pdf*> >::iterator neigh_iterator;


class iterator : public lbPatch_iterator<pdf> {


    /* ----------------------  Protected members ----------------------  */

protected:

    // Reference to latticeScalarField
    const cahnHilliardField* _field;

    // Reference to external zeroth field iterator
    latticeScalarField::iterator _phi;

    // Reference to external first field iterator
    latticeVectorField::iterator _U;

    // Reference to external chemical potential
    latticeScalarField::iterator _muPhi;    
    
    
    
    /* ----------------------  Public members ----------------------  */
    
public:


    // Constructors and destructors

    // Constructor with references
    iterator( const lbPatch_iterator<pdf>& it,
	      const cahnHilliardField* field,
	      latticeScalarField::iterator zm,
	      latticeVectorField::iterator fm,
	      latticeScalarField::iterator ch) : lbPatch_iterator<pdf>(it), _phi(zm), _U(fm), _muPhi(ch) {  _field = field;  }

    // Default destructor
    ~iterator() {}

    
    // Forward operator
    void operator++() {
	lbPatch_iterator<pdf>::operator++();
	++_phi;
	++_U;
	++_muPhi;
    }


    // Compute zeroth Moment
    const double zerothMoment() const {  
	pdf val = (*this).value();
	return val.reduce();
    }


    // Compute equilibrium
    const pdf equilibrium() {

    	// Model weights
    	const vector<double> omega = _field->_lbm->omega();

    	// Lattice velocities
    	const vector<Vector3> lvel = _field->_lbm->latticeVel();

    	// Equilibrium
    	pdf eq;
    	eq.resize( lvel.size() );
    	eq[0] = (*_phi) + (omega[0] - 1) * _field->_eta * (*_muPhi);
    	for(uint i = 1 ; i < lvel.size() ; i++) {
    	    eq[i] = omega[i] * _field->_eta * (*_muPhi)   +   _field->_c * ( lvel[i]*(*_U) ) * omega[i] * (*_phi) / _field->_cs2;
    	}


    	return eq;

    }



    // Residual term
    const pdf source() {

    	// Model weights
    	const vector<double> omega = _field->_lbm->omega();

    	// Lattice velocities
    	const vector<Vector3> lvel = _field->_lbm->latticeVel();


    	// Source term
    	pdf st;
    	st.resize( lvel.size() );
    	for(uint i = 1 ; i < lvel.size() ; i++) {
    	    const Vector3 ddt = ( (*_U) * (*_phi)     -    _U.oldValue()  * _phi.oldValue()  ) / _field->_time.timeStep();
    	    st[i] = omega[i] * _field->_c * (lvel[i] * ddt) / _field->_cs2;
    	}


    	return st;

    }





    // Residual term
    const double chemical() {

    	return 4 * _field->_beta * ( (*_phi) - _field->_phi_A) * ( (*_phi) - _field->_phi_B) * ( (*_phi) - ( (_field->_phi_A + _field->_phi_B) / 2) )   -  _field->_kappa * _phi.laplacian();

    }    

    
    
};

#endif // CAHNHILLIARDFIELD_ITERATOR_H
