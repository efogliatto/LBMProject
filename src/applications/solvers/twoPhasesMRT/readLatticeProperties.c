#include "data.h"

struct lattice readLatticeProperties() {

    struct lattice lat;
    lat.size = 0;
    lat.cs2 = 1 / 3;
    lat.c = 1;
    lat.nlocal = 36;
    lat.d = 2;
    lat.Q = 9;
    
    return lat;
    
};
