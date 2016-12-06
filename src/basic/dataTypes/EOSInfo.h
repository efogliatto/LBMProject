#ifndef EOSINFO_H
#define EOSINFO_H

#include <scalars_C.h>

struct EOSInfo {

    // EOS index
    // 0 : ideal gas
    // 1 : Carnahan-Starling
    // 2 : Peng-Robinson
    unsigned int _eosIdx;


    // Coefficients
    c_scalar _a;
    c_scalar _b;
    c_scalar _R;
    c_scalar _G;
    c_scalar _omega;

    // Constant specific heat
    c_scalar _Cv;

    // Gravity vector
    c_scalar _g[3];

    // Reference density
    c_scalar rho_0;    
    
};

#endif // EOSINFO_H
