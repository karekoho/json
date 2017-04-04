cmake_minimum_required(VERSION 2.8.9)
project(json)
set(CMAKE_BUILD_TYPE Release)
set(SOURCES
    json_value.cpp
    json_undefined.cpp
    json_string.cpp
    json_object.cpp
    json_number.cpp
    json_json.cpp
    json_boolean.cpp
    json_array.cpp
    json_leaf.cpp
# headers
    json.h
    json_value.h
    json_undefined.h
    json_string.h
    json_object.h
    json_number.h
    json_null.h
    json_json.h
    json_boolean.h
    json_array.h
    json_leaf.h
    json_exception.h)

add_library(json SHARED ${SOURCES})
#install(TARGETS json DESTINATION /usr/lib)
install(TARGETS json DESTINATION lib)
install(FILES json.h DESTINATION include)
