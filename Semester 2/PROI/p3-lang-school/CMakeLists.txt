cmake_minimum_required(VERSION 3.5)
project(Project_two)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/*.cpp")
include_directories(include)


add_executable(Project3_test1  test/test1.cpp ${SOURCES})
add_executable(Project3 main.cpp ${SOURCES})
