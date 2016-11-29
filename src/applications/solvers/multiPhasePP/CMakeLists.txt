#------------------ Pseudopotential Solver with Heat Transfer ------------------#

set ( PROJECT_LINK_LIBS libio.so libbasic.so libtime.so liblbmodel.so liblimodel.so libC_operations.so libMPI_Sync.so libcio.so libboundary.so libbasiclbe.so)
link_directories( ~/LBMProject/lib )


# multiPhasePP
add_executable( multiPhasePP "multiPhasePP.c")
target_link_libraries(multiPhasePP ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS} ${MPI_LIBRARIES})