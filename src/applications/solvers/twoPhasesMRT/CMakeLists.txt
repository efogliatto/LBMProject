#------------------ Lattice Mesh------------------#

set ( PROJECT_LINK_LIBS libio.so libbasic.so libtime.so liblbmodel.so liblbe.so libC_operations.so)
link_directories( ~/LBMProject_v3/lib )


# twoPhasesMRT
add_executable(twoPhasesMRT "twoPhasesMRT.c")
target_link_libraries(twoPhasesMRT ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS} ${MPI_LIBRARIES})