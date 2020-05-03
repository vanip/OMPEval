cmake_minimum_required(VERSION 3.17)
project(OMPEval)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(omp)

include_directories(omp)
add_executable(OMPEval benchmark.cpp)
target_link_libraries(OMPEval libomp)
