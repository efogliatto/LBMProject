#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. Test model
add_library(testmodel SHARED
  testSRTCollision.c
  testEquilibrium.c
  testVelocity_local.c
  # p_eos.c
  # potential.c
  # interactionForce.c
  # totalForce.c
  # liDensity.c
  # # liVelocity.c
  # liMRTForce.c
  # liEquilibrium.c
  # # liCollision.c
  # # pseudoPotCollision.c
  # liMRTCollision.c
  # temperatureCollision.c
  # pseudoPotVelocity.c
  # pseudoPotTemperature.c
  # guoSRTCollision.c  
  # liVelocity_local.c
  # liDensity_local.c
  # liTemperature_local.c
  # lbgkEquilibrium.c
  )