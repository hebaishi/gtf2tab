cmake_minimum_required (VERSION 2.6)
project (gtf2tab)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_SOURCE_DIR}/include")

set( SRC_DIR "${PROJECT_SOURCE_DIR}/src" )

SET( CMAKE_CXX_FLAGS  "-Wall -std=c++11" )

option(BUILD_TESTS "Build Unit Testing Binaries" OFF)

if (BUILD_TESTS)
  add_subdirectory(tests)
endif()

# add the executable
add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp ${SRC_DIR}/parsegtf.cpp ${SRC_DIR}/utility.cpp)
install (TARGETS ${PROJECT_NAME} DESTINATION bin)
