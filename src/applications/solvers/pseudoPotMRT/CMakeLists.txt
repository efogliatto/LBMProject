#------------------ Pseudopotential MRT Solver ------------------#

set ( PROJECT_LINK_LIBS libio.so libbasic.so libtime.so liblbmodel.so liblimodel.so libC_operations.so libMPI_Sync.so)
link_directories( ~/LBMProject_v3/lib )


# pseudoPotMRT
add_executable(pseudoPotMRT "pseudoPotMRT.c")
target_link_libraries(pseudoPotMRT ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS} ${MPI_LIBRARIES})