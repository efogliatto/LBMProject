#------------------ Pseudopotential MRT Solver with Heat Transfer ------------------#

set ( PROJECT_LINK_LIBS libio.so libbasic.so libtime.so liblbmodel.so liblimodel.so libC_operations.so libMPI_Sync.so libcio.so libboundary.so)
link_directories( ~/LBMProject_v3/lib )


# pseudoPotHeatT
add_executable(pseudoPotHeatT "pseudoPotHeatT.c")
target_link_libraries(pseudoPotHeatT ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS} ${MPI_LIBRARIES})