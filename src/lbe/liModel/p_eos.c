#include <p_eos.h>

double p_eos( struct liModelInfo* info, double rho, double T ) {

    double alpha = info->fields._b * rho / 4;
    double beta  = 1 - alpha;

    return rho * info->fields._R * T * ( (1 + alpha + alpha*alpha - alpha*alpha*alpha) / ( beta*beta*beta )  ) - info->fields._a * rho * rho;
    
}
