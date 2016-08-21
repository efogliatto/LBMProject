#------------------ Generacion de bibliotecas ------------------#
 
# Basic fields library
add_library(fields SHARED
  latticeScalarFields/latticeScalarField.C
  latticeVectorFields/latticeVectorField.C
  latticePdfFields/latticePdfField.C
  latticePdfFields/cahnHilliardField/cahnHilliardField.C
  # LBfields/MRT/cahnHilliard/cahnHilliardMRTField.C
  # LBfields/MRT/LiangField/LiangField.C
  # LBfields/MRT/testField/testField.C
  )