# specify minimum cmake version

cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 14)


if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")

add_definitions("-Wall")

add_subdirectory(src)

