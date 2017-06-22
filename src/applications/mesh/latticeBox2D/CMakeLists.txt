#------------------ Lattice Box 2D------------------#

set ( PROJECT_LINK_LIBS liblbmodel.so libbasic.so libtime.so libio.so ${Boost_LIBRARIES} ${MPI_LIBRARIES})
link_directories( ~/LBMProject/lib )


# latticeBox2D
add_executable(latticeBox2D "latticeBox2D.C" "periodicX.C" "periodicY.C")
target_link_libraries(latticeBox2D ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})