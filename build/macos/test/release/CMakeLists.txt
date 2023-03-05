cmake_minimum_required(VERSION 3.0.2)
project(test_release)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(PATH "../../../../src/test/")
set(SOURCES
    ${PATH}main.cpp
    ${PATH}json_array_iterator_test.h
    ${PATH}json_exception_test.h
    ${PATH}json_mock_value.h
    ${PATH}json_object_iterator_test.h
    ${PATH}json_test.h
    ${PATH}unit_test.h
    ${PATH}json_array_test.h
    ${PATH}json_leaf_iterator_test.h
    ${PATH}json_null_test.h
    ${PATH}json_object_test.h
    ${PATH}json_undefined_test.h
    ${PATH}test_selector.h
    ${PATH}json_boolean_test.h
    ${PATH}json_leaf_test.h
    ${PATH}json_number_test.h
    ${PATH}json_string_test.h
    ${PATH}json_value_test.h)

find_library (GTEST_LIB gtest)
find_library (JSON_LIB format-json)

message (${GTEST_LIB})
message (${JSON_LIB})

add_executable (test_release ${SOURCES})
target_include_directories (test_release PUBLIC "/usr/local/include")
target_link_libraries (test_release ${GTEST_LIB} ${JSON_LIB})
