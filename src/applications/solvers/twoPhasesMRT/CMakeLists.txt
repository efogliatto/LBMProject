#------------------ Lattice Mesh------------------#

set ( PROJECT_LINK_LIBS libio.so libbasic.so libtime.so liblbmodel.so libliangmodel.so libC_operations.so libMPI_Sync.so)
link_directories( ~/LBMProject/lib )


# twoPhasesMRT
add_executable(twoPhasesMRT "twoPhasesMRT.c")
target_link_libraries(twoPhasesMRT ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS} ${MPI_LIBRARIES})