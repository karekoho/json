cmake_minimum_required(VERSION 3.0.2)
project(json)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCES
    src/json/json_value.cpp
    src/json/json_undefined.cpp
    src/json/json_string.cpp
    src/json/json_object.cpp
    src/json/json_number.cpp
    src/json/json_json.cpp
    src/json/json_boolean.cpp
    src/json/json_array.cpp
    src/json/json_leaf.cpp
# headers
    src/json/json_value.h
    src/json/json_undefined.h
    src/json/json_string.h
    src/json/json_object.h
    src/json/json_number.h
    src/json/json_null.h
    src/json/json_json.h
    src/json/json_boolean.h
    src/json/json_array.h
    src/json/json_leaf.h
    src/json/json_exception.h)

add_library(json SHARED ${SOURCES})
install(TARGETS json DESTINATION lib)
install(FILES json.h DESTINATION include)

# If “make install” is invoked or INSTALL is built, this directory is prepended onto all install directories. 
# This variable defaults to /usr/local on UNIX and c:/Program Files on Windows
# cmake .. -DCMAKE_INSTALL_PREFIX=../_install

