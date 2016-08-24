#------------------ Generacion de bibliotecas ------------------#
 
# IO library
add_library(io SHARED
  dictionary.C
  vtkPatchWriter.C
  C_IO/readBasicInfo.C
  C_IO/readScalarField.C
  C_IO/readVectorField.C
  # C_IO/readPdfField.C
  # C_IO/readNeighbours.C
  # C_IO/timeOptions.C
  )