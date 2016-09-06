#ifndef READPDFFIELD_H
#define READPDFFIELD_H

#include <basicSolverInfo.h>


#ifdef __cplusplus
extern "C" {
#endif

    c_scalar** readPdfField(const char* fname, const struct solverInfo* info);
    
#ifdef __cplusplus
}
#endif
    

#endif // READPDFFIELD_H
