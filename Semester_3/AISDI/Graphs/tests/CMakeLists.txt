find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(aisdiGraphsTests test_main.cpp BridgeTests.cpp)
target_link_libraries(aisdiGraphsTests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(boostUnitTestsRun aisdiGraphsTests)

if (CMAKE_CONFIGURATION_TYPES)
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
      --force-new-ctest-process --output-on-failure
      --build-config "$<CONFIGURATION>"
      DEPENDS aisdiGraphsTests)
else()
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
      --force-new-ctest-process --output-on-failure
      DEPENDS aisdiGraphsTests)
endif()
