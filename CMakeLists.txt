cmake_minimum_required(VERSION 3.16)

project(UniversityDatabase LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmarks) 

enable_testing()