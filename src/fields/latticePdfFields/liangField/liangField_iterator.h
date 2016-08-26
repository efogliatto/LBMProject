#ifndef LIANGFIELD_ITERATOR_H
#define LIANGFIELD_ITERATOR_H

#include <lbPatch_iterator.h>
#include <latticeScalarField.h>
#include <latticeVectorField.h>

typedef vector< std::pair<uint, pdf*> >::iterator neigh_iterator;


// Iterator
class iterator : public lbPatch_iterator<pdf> {
    
protected:


    // Reference to field
    const liangField* _field;

    // Reference to external zeroth field iterator
    latticeScalarField::iterator _phi;

    // Reference to external first field iterator
    latticeVectorField::iterator _U;

    // Reference to external chemical potential
    latticeScalarField::iterator _muPhi;

    // Reference to external pressure
    latticeScalarField::iterator _p;

    // Reference to external density
    latticeScalarField::iterator _rho;     
    


    

    // Source term for equilibrium distributions
    const double s_eq(const uint& id, const Vector3& U) {

	const double w = _field->_lbm->omega(id),
	    cs2 = 1  /  _field->_cs2;

	const Vector3 ci = _field->_lbm->at(id) * _field->_c;

	return w  *  (  ci * U * cs2   +   (ci * U) * (ci * U) * 0.5 * cs2 * cs2   -  U.sqMag() * 0.5 * cs2 );
	
    }


    // Source term for equilibrium distributions
    const pdf s_eq(const Vector3& U) const {

	const vector<double> omega = _field->_lbm->omega();

	const double cs2 = 1  /  _field->_cs2;

	vector<Vector3> lvel = _field->_lbm->latticeVel();
	for(uint i = 0 ; i < lvel.size() ; i++)
	    lvel[i] = lvel[i] * _field->_c;

	pdf s;
	s.resize( lvel.size() );

	for(uint i = 0 ; i < lvel.size() ; i++) {
	    s[i] = omega[i]  *  (  lvel[i] * U * cs2   +   (lvel[i] * U) * (lvel[i] * U) * 0.5 * cs2 * cs2   -  U.sqMag() * 0.5 * cs2 );

	}
       
	
	return s;
	
    }



	
public :

    // Constructors and destructors

    // Constructor with references
    iterator( const lbPatch_iterator<pdf>& it,
	      const liangField* field,
	      latticeScalarField::iterator phiit,	      
	      latticeVectorField::iterator uit,
	      latticeScalarField::iterator muphiit,
	      latticeScalarField::iterator pit,	      
	      latticeScalarField::iterator rhoit) : lbPatch_iterator<pdf>(it), _phi(phiit), _U(uit), _muPhi(muphiit), _p(pit), _rho(rhoit) {  _field = field;  }

    // Default destructor
    ~iterator() {}

    
    // Forward operator
    void operator++() {
	lbPatch_iterator<pdf>::operator++();
	++_phi;
	++_U;
	++_muPhi;
	++_p;
	++_rho;
    }
    


    // Local density
    const double density() {

    	return (*_phi - _field->_phi_B) * (_field->_rho_A - _field->_rho_B) / (_field->_phi_A - _field->_phi_B) + _field->_rho_B;
	
    }


    // Compute zeroth Moment (pressure)
    const double zerothMoment() {

    	Vector3 U = firstMoment();

    	// Pdf reduction (except first value)
    	pdf val = (*this).value();
    	const double red = val.reduce() - val[0];

    	// Extra constants
    	const double w0 = _field->_lbm->omega(0);
	
    	return ( _field->_cs2 / (1 - w0) )  *  ( red   +   ((*_U) * _rho.gradient()) * 0.5 * _field->_time.timeStep()   +   (*_rho) * s_eq(0,U) );

    }


    
    // Compute zeroth Moment (pressure)
    const double zerothMoment(const Vector3& U) {

	// Pdf reduction (except first value)
    	pdf val = (*this).value();
    	const double red = val.reduce() - val[0];
	
	// Extra constants
	const double w0 = _field->_lbm->omega(0);
	
	return ( _field->_cs2 / (1 - w0) )  *  ( red   +   (  (*_U) * _rho.gradient() ) * 0.5 * _field->_time.timeStep()   +   (*_rho) * s_eq(0,U) );

    }


    // Compute first moment normalized (velocity)
    const Vector3 firstMoment() {

	// External forces
	const Vector3 Fs = _phi.gradient() * (*_muPhi);

	// Body force
	Vector3 Fb;
	Fb = _field->_G * (*_rho);

	
	// Pdf reduction
	pdf val = (*this).value();
	const Vector3 red = val.reduce( _field->_lbm->latticeVel(), _field->_c);

	
	return ( red  +  (Fs + Fb) * 0.5 * _field->_time.timeStep() )    /    ( (*_rho)  -  0.5 * _field->_time.timeStep() * (_field->_rho_A - _field->_rho_B) * _field->_M * _muPhi.laplacian() / (_field->_phi_A - _field->_phi_B) );

    }



    // Compute equilibrium
    const pdf equilibrium() {

    	// Model weights
    	const vector<double> omega = _field->_lbm->omega();

    	// Sound speed
    	double cs2 = _field->_cs2;

	pdf s = s_eq( *_U );

    	// Equilibrium
    	pdf eq;
    	eq.resize( omega.size() );

    	eq[0] = ( (*_p) * (omega[0] - 1) / cs2)   +   (*_rho) * s[0];

    	for(uint i = 1 ; i < omega.size() ; i++) {
    	    eq[i] = ( (*_p) * omega[i] / cs2 )   +   (*_rho) * s[i];
	}

    	return eq;

    }



/*     // Total force */
/*     const pdf totalForce() const { */

/*     	// Order parameter */
/* 	latticeScalarField::iterator phi  =  _p->_externalScalarFields.at("phi")->at(  (*(*this)).localId()  );	 */

/*     	// Chemical potential */
/*     	latticeScalarField::iterator muPhi  =  _p->_externalScalarFields.at("muPhi")->at(  (*(*this)).localId()  );	 */

/*     	// Velocity */
/*     	latticeVectorField::iterator u  =  _p->_externalVectorFields.at("U")->at(  (*(*this)).localId()  ); */

/*     	// Local density */
/*     	latticeScalarField::iterator rho  =  _p->_externalScalarFields.at("rho")->at(  (*(*this)).localId()  );	 */




/* 	// Model constants */
/* 	const double cs2 = _p->_lat.lbmodel()->c() * _p->_lat.lbmodel()->c() * _p->_lat.lbmodel()->cs2(); */

/* 	vector<Vector3> lvel = _p->_lat.lbmodel()->latticeVel(); */
/* 	for(uint i = 0 ; i < lvel.size() ; i++) */
/* 	    lvel[i] = (lvel[i] * _p->_lat.lbmodel()->c()   -   u->value() )  /  cs2 ; */




/* 	// Surface tension force */
/* 	const Vector3 Fs = phi.gradient() * muPhi->value();	 */

/* 	// Interfacial force */
/* 	const Vector3 Fa = u->value() * _p->_M * muPhi.laplacian() * (_p->_rho_A - _p->_rho_B) / (_p->_phi_A - _p->_phi_B);	 */

/* 	// Body force */
/* 	/\* Vector3 Fb(0,0,0);  // _p->_G*rho->value(); *\/ */
/* 	/\* if( phi->value() < 0 ){ *\/ */
/* 	/\*     Fb = _p->_G * ( _p->_rho_A - _p->_rho_B ); *\/ */
/* 	/\* } *\/ */
/* 	Vector3 Fb; */
/* 	Fb = _p->_G*rho->value(); */
	
/* 	// Density gradient */
/* 	const Vector3 rhoGrad = rho.gradient() * cs2; */


/* 	// Gamma function */
/* 	const pdf Gamma = _p->_lat.lbmodel()->pdfOmega()  +  s_eq( u->value() ), */
/* 	    Gamma0 = _p->_lat.lbmodel()->pdfOmega(); */


/* 	pdf Force; */
/* 	Force.resize( lvel.size() ); */

/* 	for(uint i = 0 ; i < lvel.size() ; i++) */
/* 	    Force[i] = lvel[i] * (  rhoGrad * (Gamma[i] - Gamma0[i])   +  (Fs + Fa + Fb) * Gamma[i] ); */

	

/* 	return Force; */

/*     } */
	
};


#endif // LIANGFIELD_ITERATOR_H
