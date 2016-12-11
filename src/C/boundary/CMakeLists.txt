# Boundary conditions

add_library(boundary SHARED
  bounceBack.c
  fixedT.c
  fixedU.c
  adiabatic.c
  randomT.c
  tSpot.c
  )