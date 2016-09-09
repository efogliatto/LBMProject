#ifndef SHAPESCREATOR_H
#define SHAPESCREATOR_H

#include <box.h>
#include <cylinder.h>
#include <bubble.h>
#include <semiPeriodicBox.h>
#include <periodicBox.h>
#include <profileBox.h>

class shapesCreator {


    /* ----------------------  Public member functions ----------------------  */

public:

    basicShape* create(const std::string& stype, const std::string& sname);

};


#endif // SHAPESCREATOR_H
