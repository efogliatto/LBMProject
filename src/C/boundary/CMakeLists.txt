# Boundary conditions

add_library(boundary SHARED
  updateBC.c
  bounceBack.c
  fixedT.c
  adiabatic.c
  updateBoundaryT.c
  updateBoundaryDens.c
  updateBoundaryVel.c
  )