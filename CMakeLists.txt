cmake_minimum_required(VERSION 3.10)

project(cubesat_OBC C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_REQUIRED_STANDARD ON)

include_directories(
    obc 
    obc/comms
    obc/core 
    obc/drivers
    obc/faults
    obc/gnc 
    obc/utils 
)

file(GLOB_RECURSE OBC_SOURCES obc/*.c)

add_executable(OBC ${OBC_SOURCES})

target_link_libraries(OBC m)

message(STATUS "CMake configuration complete. Ready to build OBC.")