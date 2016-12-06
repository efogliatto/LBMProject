#ifndef LBSTREAM_H
#define LBSTREAM_H

#include <latticeMesh.h>
#include <lbeField.h>
#include <syncPdfField.h>

void lbstream( struct latticeMesh* mesh, struct lbeField* field );

#endif // LBSTREAM_H
