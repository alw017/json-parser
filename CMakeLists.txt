cmake_minimum_required(VERSION 3.7)

if(${CMAKE_VERSION} VERSION_LESS 3.29)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.29)
endif()

project(JSONParser VERSION 1.0
	DESCRIPTION "JSON Parser Prototype"
	LANGUAGES CXX)

add_subdirectory(src)

add_executable(tester main.cpp)

target_link_libraries(tester PUBLIC reader)
target_link_libraries(reader PUBLIC lexer)
target_link_libraries(tester PUBLIC parser)