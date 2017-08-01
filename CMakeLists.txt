cmake_minimum_required(VERSION 3.0)
project(DEMP-EvGen)

set (DEMP-EvGen_VERSION_MAJOR 0)
set (DEMP-EvGen_VERSION_MINOR 1)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net Tree)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

include_directories(include)
include_directories(${ROOT_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cxx")

message("Root Include Dirs: " ${ROOT_INCLUDE_DIRS})
message("Root Libraries: " ${ROOT_LIBRARIES})

add_executable (main ${SOURCES})
target_link_libraries(main ${ROOT_LIBRARIES})
