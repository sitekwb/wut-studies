
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -Wall -pedantic -Wextra ")
add_executable(aisdiLinear main.cpp Vector.h LinkedList.h)
add_dependencies(aisdiLinear check)
