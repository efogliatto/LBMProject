#ifndef MACROVELOCITY_H
#define MACROVELOCITY_H

#include <liModelInfo.h>
#include <macroFields.h>
#include <lbeField.h>

void macroVelocity( struct liModelInfo* info, struct macroFields* mfields, struct lbeField* field, int** nb );

#endif // MACROVELOCITY_H
