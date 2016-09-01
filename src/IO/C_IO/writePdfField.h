#ifndef WRITEPDFFIELD_H
#define WRITEPDFFIELD_H

#include <basicSolverInfo.h>

#ifdef __cplusplus
extern "C" {
#endif

    void writePdfField( char* fname,  double** field,  struct solverInfo* info);
    
#ifdef __cplusplus
}
#endif
    

#endif // WRITEPDFFIELD_H
