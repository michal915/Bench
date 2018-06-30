project(Bench CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O2 -fno-omit-frame-pointer -fno-exceptions -fno-rtti -pedantic")

include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(benchmark
  GIT_REPOSITORY https://github.com/google/benchmark
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION})

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

add_subdirectory(vector)
add_subdirectory(string)
add_subdirectory(cache-miss)
add_subdirectory(endl)
add_subdirectory(state-machine)
