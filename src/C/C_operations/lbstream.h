#ifndef LBSTREAM_H
#define LBSTREAM_H

#include <latticeInfo.h>
#include <syncPdfField.h>

void lbstream( c_scalar** fld, c_scalar** swp, int** nb, struct latticeInfo* info, struct mpiInfo* parallel );

#endif // LBSTREAM_H
