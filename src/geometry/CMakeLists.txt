#------------------ Generacion de bibliotecas ------------------#

 
# Basic geometry library
add_library(geometry SHARED
  shapes/basicShape.C
  shapes/box.C
  shapes/sphere.C
  shapes/bubble.C
  shapes/cylinder.C
  shapes/polyShapes.C
  shapes/shapesCreator.C
  shapes/semiPeriodicBox.C
  shapes/periodicBox.C
  fields/fieldShape.C
  )