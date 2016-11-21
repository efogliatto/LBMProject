#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. Liang model
add_library(limodel SHARED
  p_eos.c
  potential.c
  interactionForce.c
  liDensity.c
  liVelocity.c
  liMRTForce.c
  liEquilibrium.c
  liCollision.c
  pseudoPotCollision.c
  temperatureCollision.c
  pseudoPotVelocity.c
  pseudoPotTemperature.c
  )