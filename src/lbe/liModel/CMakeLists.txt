#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. Li model
add_library(limodel SHARED
  p_eos.c
  potential.c
  interactionForce.c
  totalForce.c
  liDensity.c
  # liVelocity.c
  liMRTForce.c
  liEquilibrium.c
  # liCollision.c
  pseudoPotCollision.c
  temperatureCollision.c
  pseudoPotVelocity.c
  pseudoPotTemperature.c
  liSRTCollision.c
  )