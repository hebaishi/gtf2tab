cmake_minimum_required (VERSION 2.6)
project (gtf2tab)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_SOURCE_DIR}/include")

set( SRC_DIR "${PROJECT_SOURCE_DIR}/src" )

if (UNIX)
  SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -O3" )
  SET( CMAKE_EXE_LINKER_FLAGS  "-pthread" )
endif()

option(BUILD_TESTS "Build Unit Testing Binaries" OFF)

if (BUILD_TESTS)
  add_subdirectory(tests)
endif()

# add the executable
add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp ${SRC_DIR}/parsegtf.cpp ${SRC_DIR}/utility.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

install (TARGETS ${PROJECT_NAME} DESTINATION bin)
