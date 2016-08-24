#include <liangTotalForce.h>

void liangTotalForce(struct twoPhasesFields* fields, const struct solverInfo* info, double* eq, const unsigned int id) {

    

}




/* vector<Vector3> lvel = _p->_lat.lbmodel()->latticeVel(); */
/* for(uint i = 0 ; i < lvel.size() ; i++) */
/*     lvel[i] = (lvel[i] * _p->_lat.lbmodel()->c()   -   u->value() )  /  cs2 ; */




/* // Surface tension force */
/* const Vector3 Fs = phi.gradient() * muPhi->value();	 */

/* // Interfacial force */
/* const Vector3 Fa = u->value() * _p->_M * muPhi.laplacian() * (_p->_rho_A - _p->_rho_B) / (_p->_phi_A - _p->_phi_B);	 */

/* // Body force */
/* /\* Vector3 Fb(0,0,0);  // _p->_G*rho->value(); *\/ */
/* /\* if( phi->value() < 0 ){ *\/ */
/* /\*     Fb = _p->_G * ( _p->_rho_A - _p->_rho_B ); *\/ */
/* /\* } *\/ */
/* Vector3 Fb; */
/* Fb = _p->_G*rho->value(); */
	
/* // Density gradient */
/* const Vector3 rhoGrad = rho.gradient() * cs2; */


/* // Gamma function */
/* const pdf Gamma = _p->_lat.lbmodel()->pdfOmega()  +  s_eq( u->value() ), */
/*     Gamma0 = _p->_lat.lbmodel()->pdfOmega(); */


/* pdf Force; */
/* Force.resize( lvel.size() ); */

/* for(uint i = 0 ; i < lvel.size() ; i++) */
/*     Force[i] = lvel[i] * (  rhoGrad * (Gamma[i] - Gamma0[i])   +  (Fs + Fa + Fb) * Gamma[i] ); */
