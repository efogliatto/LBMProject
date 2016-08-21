#------------------ Generacion de bibliotecas ------------------#
 
# Runtime selection library
add_library(time SHARED
  basicTime.C
  # fieldsTime.C
  # writeTime.C
  Time.C
  )