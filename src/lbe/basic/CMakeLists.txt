#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library.
add_library(basiclbe SHARED
  equilibrium.c
  collision.c
  )