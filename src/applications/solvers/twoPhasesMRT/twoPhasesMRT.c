#include <stdio.h>
#include "data.h"

struct Time readTime();
struct lattice readLatticeProperties();
struct fields readFieldsProperties();

int main() {

    struct Time t;
    t = readTime();

    struct lattice lat;
    lat = readLatticeProperties();

    struct fields fld;
    fld = readFieldsProperties();
    
    return 0;
    
}
