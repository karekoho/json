cmake_minimum_required(VERSION 3.0.2)
project(format-json)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(PATH "../../../../src/json/")
set(SOURCES
    ${PATH}json_value.cpp
    ${PATH}json_undefined.cpp
    ${PATH}json_string.cpp
    ${PATH}json_object.cpp
    ${PATH}json_number.cpp
    ${PATH}json_json.cpp
    ${PATH}json_array.cpp
    ${PATH}json_exception.cpp
# headers
    ${PATH}json_value.h
    ${PATH}json_undefined.h
    ${PATH}json_string.h
    ${PATH}json_object.h
    ${PATH}json_number.h
    ${PATH}json_null.h
    ${PATH}json_json.h
    ${PATH}json_boolean.h
    ${PATH}json_array.h
    ${PATH}json_leaf.h
    ${PATH}json_exception.h)

add_library(format-json SHARED ${SOURCES})
install(TARGETS format-json DESTINATION lib)
install(DIRECTORY ${PATH} DESTINATION include/format FILES_MATCHING PATTERN "*.h")

# If “make install” is invoked or INSTALL is built, this directory is prepended onto all install directories. 
# This variable defaults to /usr/local on UNIX and c:/Program Files on Windows
# cmake .. -DCMAKE_INSTALL_PREFIX=../_install

