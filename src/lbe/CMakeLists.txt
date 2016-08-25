#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library
add_library(lbe SHARED
  matVecMult.c
  scalarFieldLaplacian.c
  gradient.c
  density.c
  chemicalPotential.c
  cahnHilliardSource.c
  cahnHilliardEquilibrium.c
  cahnHilliardCollision.c
  liangEquilibrium.c
  liangTotalForce.c
  liangCollision.c  
  )