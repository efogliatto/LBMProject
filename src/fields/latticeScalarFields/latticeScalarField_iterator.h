#ifndef LATTICESCALARFIELD_ITERATOR_H
#define LATTICESCALARFIELD_ITERATOR_H

#include <lbPatch_iterator.h>

typedef vector< std::pair<uint, double*> >::iterator neigh_iterator;


class iterator : public lbPatch_iterator<double> {


    /* ----------------------  Protected members ----------------------  */

protected:

    // Reference to latticeScalarField
    const latticeScalarField* _field;
    
    
    
    /* ----------------------  Public members ----------------------  */
    
public:


    // Constructors and destructors

    // Constructor with references
    iterator( const lbPatch_iterator<double>& it, const latticeScalarField* field ) : lbPatch_iterator<double>(it) {  _field = field;  }

    // Default destructor
    ~iterator() {}



    // Differential isotropic operators

    // Laplacian at node
    const double laplacian() {

	double lap(0);

	// Model weights
	vector<double> omega = _field->_lbm->omega();

	// time square
	double t2 = _field->_time.timeStep() * _field->_time.timeStep();
	
	
	// Move over neighbours
	for(neigh_iterator neigh = lbPatch_iterator<double>::neighBegin() ; neigh != lbPatch_iterator<double>::neighEnd() ; ++neigh) {

	    int id = neigh->first;

	    int revId = _field->_lbm->reverse( id );

	    if(  id != 0  ) {

	    	lap += 2 * omega[revId] * ( *(neigh->second) - (*(*this)) );
		
	    }
	    	
	}

	return lap / ( _field->_cs2 * t2 );

    }



    // Gradient at node
    const Vector3 gradient() {

	Vector3 grad;
    
	// Model weights
	vector<double> omega = _field->_lbm->omega();


	// Move over neighbours
	for(neigh_iterator neigh = lbPatch_iterator<double>::neighBegin() ; neigh != lbPatch_iterator<double>::neighEnd() ; ++neigh) {	    

	    int revId = _field->_lbm->reverse( neigh->first );

	    if(  neigh->first != 0  ) {

		grad += _field->_lbm->at(revId ) * (*neigh->second) * omega[revId] * _field->_c;
		
	    }
	    	
	}


	return grad / ( _field->_cs2 * _field->_time.timeStep() );
	
    }

    
    
};

#endif // LATTICESCALARFIELD_ITERATOR_H
