#------------------ Generacion de bibliotecas ------------------#
 
# IO library
add_library(io SHARED
  dictionary.C
  vtkPatchWriter.C
  # readBasicInfo.C
  # readScalarField.C
  # readVectorField.C
  # readPdfField.C
  # readNeighbours.C
  # C_IO/timeOptions.C
  )