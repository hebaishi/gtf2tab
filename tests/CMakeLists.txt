set( TEST_DIR "${PROJECT_SOURCE_DIR}/tests" )

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

add_executable(utility_test ${TEST_DIR}/utility_test.cpp ${SRC_DIR}/utility.cpp)
target_link_libraries( utility_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} )

add_executable(parsegtf_test ${TEST_DIR}/parsegtf_test.cpp ${SRC_DIR}/parsegtf.cpp ${SRC_DIR}/utility.cpp)
target_link_libraries( parsegtf_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE} )

enable_testing()
add_test(ParseGTF_tests parsegtf_test)
add_test(Utility_tests utility_test)
