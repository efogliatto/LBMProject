#------------------ Equilibrium initializer for two phases solver ------------------#

set ( PROJECT_LINK_LIBS liblbmodel.so libbasic.so libtime.so libio.so libfields.so libgeometry.so ${Boost_LIBRARIES} ${MPI_LIBRARIES})
link_directories( ~/LBMProject/lib )


# twoPhasesFields
add_executable(setTwoPhasesFields "setTwoPhasesFields.C")
target_link_libraries(setTwoPhasesFields ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})