file(GLOB SOURCES "*.cpp")
include_directories(../include)
add_executable(aisdiGraphs ${SOURCES})
add_dependencies(aisdiGraphs check)
