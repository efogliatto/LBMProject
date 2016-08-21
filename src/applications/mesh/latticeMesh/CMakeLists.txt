#------------------ Lattice Mesh------------------#

set ( PROJECT_LINK_LIBS liblbmodel.so libbasic.so libtime.so libio.so libfields.so libgeometry.so ${Boost_LIBRARIES} ${MPI_LIBRARIES})
link_directories( ~/LBMProject_v3/lib )


# latticeMesh
add_executable(latticeMesh "latticeMesh.C")
target_link_libraries(latticeMesh ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})