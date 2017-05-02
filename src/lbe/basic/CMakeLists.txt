#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library.
add_library(basiclbe SHARED
  equilibrium.c
  collision.c
  basicDensity.c
  macroDensity.c
  macroVelocity.c
  macroTemperature.c
  updateBoundaries.c
  updateBoundaryElements.c
  lbgkEquilibrium_id.c
  lbgkTEquilibrium.c
  basicVelocity.c
  updateLambda.c
  updateTau.c
  )