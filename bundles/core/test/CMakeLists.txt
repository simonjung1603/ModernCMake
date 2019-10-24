set(TEST_SOURCES
    MidiMessageTest.cpp
)
set(TEST_NAME all_tests)

add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE 
    "${CMAKE_SOURCE_DIR}/../third_party/doctest"
)

add_executable(test_runner test_runner.cpp ${TEST_SOURCES})
target_link_libraries(test_runner core doctest)

add_test(${TEST_NAME} test_runner)

set_tests_properties(${TEST_NAME} PROPERTIES ENVIRONMENT "PATH=${CMAKE_BINARY_DIR}/bin;$ENV{PATH}")
