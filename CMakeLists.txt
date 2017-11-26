cmake_minimum_required (VERSION 2.6)
project (gtf2tab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( SRC_DIR "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include" )

include_directories("${INCLUDE_DIR}")

if ( UNIX )
  SET( CMAKE_EXE_LINKER_FLAGS  "-pthread" )
endif()

option(BUILD_TESTS "Build Unit Testing Binaries" ON)

if (BUILD_TESTS)
  add_subdirectory(tests)
endif()

set(SOURCES
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/parsegtf.cpp
  ${SRC_DIR}/utility.cpp
)

set(HEADERS
  ${INCLUDE_DIR}/parsegtf.hpp
  ${INCLUDE_DIR}/utility.hpp
  ${INCLUDE_DIR}/version.hpp
)

# add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
install (TARGETS ${PROJECT_NAME} DESTINATION bin)
if (APPLE)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND zip gtf2tab_osx.zip gtf2tab )
elseif (UNIX)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND tar -cvzf gtf2tab_x86_64.tar.gz gtf2tab -C ${PROJECT_BINARY_DIR} )
endif()
