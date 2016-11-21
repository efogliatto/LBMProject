# Boundary conditions

add_library(boundary SHARED
  updateBC.c
  bounceBack.c
  fixedT.c
  updateBoundaryT.c
  updateBoundaryDens.c
  updateBoundaryVel.c
  )