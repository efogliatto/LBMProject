#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library
add_library(lbe SHARED
  matVecMult.c
  cahnHilliardSource.c
  cahnHilliardEquilibrium.c
  cahnHilliardCollision.c
  liangEquilibrium.c
  liangTotalForce.c
  liangCollision.c  
  )