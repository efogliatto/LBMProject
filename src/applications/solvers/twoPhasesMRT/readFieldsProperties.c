#include "data.h"

struct fields readFieldsProperties() {

    struct fields fld;

    fld.Sh[0] = 1;
    fld.Sh[1] = 1.3;
    fld.Sh[2] = 1.3;
    fld.Sh[3] = 1.25;
    fld.Sh[4] = 1.3;
    fld.Sh[5] = 1.25;
    fld.Sh[6] = 1.3;
    fld.Sh[7] = 1;
    fld.Sh[8] = 1;
    
    fld.Sg_a[0] = 1;
    fld.Sg_a[1] = 1;
    fld.Sg_a[2] = 1;
    fld.Sg_a[3] = 1;
    fld.Sg_a[4] = 1.7;
    fld.Sg_a[5] = 1;
    fld.Sg_a[6] = 1.7;
    fld.Sg_a[7] = 1.13979;
    fld.Sg_a[8] = 1.13979;
    
    fld.Sg_b[0] = 1;
    fld.Sg_b[1] = 1;
    fld.Sg_b[2] = 1;
    fld.Sg_b[3] = 1;
    fld.Sg_b[4] = 1.7;
    fld.Sg_b[5] = 1;
    fld.Sg_b[6] = 1.7;
    fld.Sg_b[7] = 1.23648;
    fld.Sg_b[8] = 1.23648;
    
    fld.sigma = 5e-05;
    fld.D = 4;
    fld.phi_A = -1;
    fld.phi_B = -1;
    fld.M_phi = 106.7;
    fld.gx = 0;
    fld.gy = -6.25e-06;
    fld.gz = 0;

    fld.rho_A = 1;
    fld.rho_B = 1.222222;

    fld.eta = fld.M_phi / (   (1/3) * 1 * (1/fld.Sh[3] - 0.5)   );
    
    return fld;   

}
