#------------------ Generacion de bibliotecas ------------------#
 
# Basic geometry library
# file(GLOB BASIC_SOURCE "*.C")
# add_library(basic SHARED ${BASIC_SOURCE})

add_library(basic SHARED dataTypes/Vector3.C
  dataTypes/pdf.C
  dataTypes/Matrix.C
  )