#------------------ Caracteristicas generales del proyecto ------------------#

cmake_minimum_required(VERSION 2.8.9)
project(LBMProject_v2.0)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# Bibliotecas externas: Boost
find_package( Boost 1.55 COMPONENTS system program_options mpi serialization filesystem REQUIRED )

# Bibliotecas externas: MPI
find_package(MPI REQUIRED)

# Bring the headers
include_directories(include ${MPI_INCLUDE_PATH} ${Boost_INCLUDE_DIRS})

# Compiler options for Cpp
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --std=c++11 -Wall" )

# Compiler options for C
SET( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall" )

# # Linker flags
# SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
# SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

# Directorio con fuentes
add_subdirectory (src)