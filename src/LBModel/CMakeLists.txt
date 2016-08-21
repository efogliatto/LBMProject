#------------------ Generacion de bibliotecas ------------------#
 
# LBMmodel library
add_library(lbmodel SHARED 
  basicLBModel.C
  D2Q9.C
  D2Q5.C
  D2Q4.C
  D3Q7.C  
  LBModelCreator.C)