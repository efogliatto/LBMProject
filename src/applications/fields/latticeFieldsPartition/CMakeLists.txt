#------------------ Lattice Fields Partition------------------#

set ( PROJECT_LINK_LIBS liblbmodel.so libbasic.so libtime.so libio.so libfields.so libgeometry.so ${Boost_LIBRARIES} ${MPI_LIBRARIES})
link_directories( ~/LBMProject/lib )


# latticeMesh
add_executable(latticeFieldsPartition "latticeFieldsPartition.C")
target_link_libraries(latticeFieldsPartition ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})