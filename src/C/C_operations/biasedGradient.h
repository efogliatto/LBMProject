#ifndef BIASEDGRADIENT_H
#define BIASEDGRADIENT_H

#include <scalars_C.h>

c_scalar* biasedGradient( c_scalar* fld, int** nb, c_scalar** vel, int pdir[3][2], double lsize, int id );

#endif // BIASEDGRADIENT_H
