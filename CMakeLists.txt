cmake_minimum_required(VERSION 2.8)
project(DEMP-EvGen)
set (DEMP-EvGen_VERSION_MAJOR 0)
set (DEMP-EvGen_VERSION_MINOR 1)

add_definitions (-DROOT_MATH_LOG)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net Tree MathMore)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

include_directories(include)
include_directories(${ROOT_INCLUDE_DIRS})
#include_directories(include/json)

file(GLOB SOURCES "src/*")
# file(GLOB SOURCES "src/*.cpp")

message("Root Include Dirs: " ${ROOT_INCLUDE_DIRS})
message("Root Libraries: " ${ROOT_LIBRARIES})
message("Mathmore: " ${ROOT_mathmore_FOUND})

add_executable (main ${SOURCES})
target_link_libraries(main ${ROOT_LIBRARIES})
