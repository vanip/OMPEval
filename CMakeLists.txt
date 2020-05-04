cmake_minimum_required(VERSION 3.17)
project(OMPEval)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

add_subdirectory(pybind11)
add_subdirectory(omp)

link_directories(C:/Users/ishikawatt/AppData/Local/Programs/Python/Python38/libs)
include_directories(omp)
#add_executable(OMPEval benchmark.cpp)
pybind11_add_module(pyomp pyompeval.cpp)
pybind11_add_module(benchmark benchmark.cpp)
target_link_libraries(pyomp PRIVATE libomp)
target_link_libraries(benchmark PRIVATE libomp)
