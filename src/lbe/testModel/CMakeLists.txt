#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. Test model
add_library(testmodel SHARED
  testSRTCollision.c
  testEquilibrium.c
  testVelocity_local.c
  )