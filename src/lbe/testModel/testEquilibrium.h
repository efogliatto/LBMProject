#ifndef TESTEQUILIBRIUM_H
#define TESTEQUILIBRIUM_H

#include <latticeInfo.h>
#include <EOSInfo.h>

void testEquilibrium( struct latticeInfo* lattice, struct EOSInfo* info, double rho, double v[3], double T, double* f );

#endif // TESTEQUILIBRIUM_H
