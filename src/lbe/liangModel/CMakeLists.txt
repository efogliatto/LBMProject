#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. Liang model
add_library(liangmodel SHARED
  scalarFieldLaplacian.c
  scalarFieldGradient.c
  density.c
  chemicalPotential.c
  pressureWithU.c
  orderParameter.c
  velocity.c
  cahnHilliardSource.c
  cahnHilliardEquilibrium.c
  cahnHilliardCollision.c
  liangEquilibrium.c
  liangCollision.c
  liangSource.c
  )