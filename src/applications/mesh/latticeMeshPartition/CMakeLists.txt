#------------------ Lattice Mesh Partition------------------#

set ( PROJECT_LINK_LIBS liblbmodel.so libbasic.so libtime.so libio.so libfields.so libgeometry.so ${Boost_LIBRARIES} ${MPI_LIBRARIES})
link_directories( ~/LBMProject_v2.0/lib )


# latticeMeshPartition
add_executable(latticeMeshPartition "latticeMeshPartition.C")
target_link_libraries(latticeMeshPartition ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})