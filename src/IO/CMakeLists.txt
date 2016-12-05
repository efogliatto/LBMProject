#------------------ Generacion de bibliotecas ------------------#
 
# IO library
add_library(io SHARED
  dictionary.C
  vtkPatchWriter.C
  C_IO/readBasicInfo.C
  C_IO/readLatticeInfo.C
  C_IO/readMPIInfo.C
  C_IO/readTimeInfo.C
  C_IO/readLatticeMesh.C
  C_IO/readLbeField.C
  C_IO/readBoundaryElements.C
  C_IO/readBoundaryConditions.C
  C_IO/readVTKInfo.C
  C_IO/readLiModelInfo.C
  C_IO/readScalarField.C
  C_IO/readVectorField.C
  C_IO/readPdfField.C
  C_IO/readNeighbours.C
  C_IO/timeOptions.C
  C_IO/writeScalarField.C
  C_IO/writeVectorField.C
  C_IO/writePdfField.C
  )