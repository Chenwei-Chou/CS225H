add_test( [==[Scan produces correct character count 1]==] /workspaces/cs225env/cs225/hw2/build/test [==[Scan produces correct character count 1]==]  )
set_tests_properties( [==[Scan produces correct character count 1]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225env/cs225/hw2/build)
add_test( [==[Scan produces correct value 1]==] /workspaces/cs225env/cs225/hw2/build/test [==[Scan produces correct value 1]==]  )
set_tests_properties( [==[Scan produces correct value 1]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225env/cs225/hw2/build)
add_test( [==[Scan produces correct character count 2]==] /workspaces/cs225env/cs225/hw2/build/test [==[Scan produces correct character count 2]==]  )
set_tests_properties( [==[Scan produces correct character count 2]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225env/cs225/hw2/build)
add_test( [==[Scan produces correct value 2]==] /workspaces/cs225env/cs225/hw2/build/test [==[Scan produces correct value 2]==]  )
set_tests_properties( [==[Scan produces correct value 2]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225env/cs225/hw2/build)
add_test( [==[All Z-values are correct 1]==] /workspaces/cs225env/cs225/hw2/build/test [==[All Z-values are correct 1]==]  )
set_tests_properties( [==[All Z-values are correct 1]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225env/cs225/hw2/build)
add_test( [==[All Z-values are correct 2]==] /workspaces/cs225env/cs225/hw2/build/test [==[All Z-values are correct 2]==]  )
set_tests_properties( [==[All Z-values are correct 2]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225env/cs225/hw2/build)
add_test( [==[Z-array computed efficiently.]==] /workspaces/cs225env/cs225/hw2/build/test [==[Z-array computed efficiently.]==]  )
set_tests_properties( [==[Z-array computed efficiently.]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225env/cs225/hw2/build)
add_test( [==[Z-array computed efficiently 2]==] /workspaces/cs225env/cs225/hw2/build/test [==[Z-array computed efficiently 2]==]  )
set_tests_properties( [==[Z-array computed efficiently 2]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225env/cs225/hw2/build)
add_test( [==[Output vector is correctly sized.]==] /workspaces/cs225env/cs225/hw2/build/test [==[Output vector is correctly sized.]==]  )
set_tests_properties( [==[Output vector is correctly sized.]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225env/cs225/hw2/build)
add_test( [==[Output vector is correct.]==] /workspaces/cs225env/cs225/hw2/build/test [==[Output vector is correct.]==]  )
set_tests_properties( [==[Output vector is correct.]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225env/cs225/hw2/build)
add_test( [==[Output vector is correct 2]==] /workspaces/cs225env/cs225/hw2/build/test [==[Output vector is correct 2]==]  )
set_tests_properties( [==[Output vector is correct 2]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225env/cs225/hw2/build)
add_test( [==[Output vector handles no match.]==] /workspaces/cs225env/cs225/hw2/build/test [==[Output vector handles no match.]==]  )
set_tests_properties( [==[Output vector handles no match.]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225env/cs225/hw2/build)
set( test_TESTS [==[Scan produces correct character count 1]==] [==[Scan produces correct value 1]==] [==[Scan produces correct character count 2]==] [==[Scan produces correct value 2]==] [==[All Z-values are correct 1]==] [==[All Z-values are correct 2]==] [==[Z-array computed efficiently.]==] [==[Z-array computed efficiently 2]==] [==[Output vector is correctly sized.]==] [==[Output vector is correct.]==] [==[Output vector is correct 2]==] [==[Output vector handles no match.]==])
