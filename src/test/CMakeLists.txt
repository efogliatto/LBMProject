#------------------ Unit tests ------------------#

set ( PROJECT_LINK_LIBS libbasic.so libtime.so liblbmodel.so libio.so libfields.so libgeometry.so )
link_directories( ~/LBMProject_v2.0/lib )


# Test 1. basicPatch
add_executable(test1 "test1.C")
target_link_libraries(test1 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 2. lbPatch
add_executable(test2 "test2.C")
target_link_libraries(test2 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 3. boundaryPatch
add_executable(test3 "test3.C")
target_link_libraries(test3 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 4. commPatch
add_executable(test4 "test4.C")
target_link_libraries(test4 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 5. IOPatch
add_executable(test5 "test5.C")
target_link_libraries(test5 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 6. mpiPatch
add_executable(test6 "test6.C")
target_link_libraries(test6 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 7. latticeField
add_executable(test7 "test7.C")
target_link_libraries(test7 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 8. latticeScalarField
add_executable(test8 "test8.C")
target_link_libraries(test8 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 9. latticeVectorField
add_executable(test9 "test9.C")
target_link_libraries(test9 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 10. latticePdfField
add_executable(test10 "test10.C")
target_link_libraries(test10 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 11. latticeMesh (mesh generation)
add_executable(test11 "test11.C")
target_link_libraries(test11 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 12. latticeMeshPartition
add_executable(test12 "test12.C")
target_link_libraries(test12 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 13. latticeFieldPartition
add_executable(test13 "test13.C")
target_link_libraries(test13 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 14. Read fields from .vtu
add_executable(test14 "test14.C")
target_link_libraries(test14 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PROJECT_LINK_LIBS})

# Test 15. cahnHilliard
add_executable(test15 "test15.C")
target_link_libraries(test15 ${PROJECT_LINK_LIBS} ${Boost_LIBRARIES} ${MPI_LIBRARIES} ${PROJECT_LINK_LIBS})