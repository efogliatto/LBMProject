#include "data.h"

struct Time readTime() {

    struct Time t;
    t.start = 0;
    t.end = 1000;
    t.tstep = 1;
    t.writeInterval = 1;
    t.current = 0;

    return t;
    
};
