#ifndef DATA_H
#define DATA_H

struct Time {

    double start;
    double end;
    double tstep;
    double writeInterval;
    double current;
    
};

struct lattice {

    double size;
    double cs2;
    double c;
    double nlocal;
    
};

struct fields {

    double Sh[9];
    double Sg_a[9];
    double Sg_b[9];
    double sigma;
    double D;
    double phi_A;
    double phi_B;
    double M_phi;
    double gx;
    double gy;
    double gz;
    double rho_A;
    double rho_B;
    
};

#endif // DATA_H
