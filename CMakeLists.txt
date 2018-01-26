cmake_minimum_required(VERSION 3.9)

project(csvMongoDB)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_FLAGS_X "-pthread -lmongoclient -lboost_thread -lboost_system -lboost_regex")

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CMAKE_FLAGS_X}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_FLAGS_X}")

file(COPY res/test/test.csv
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/test)

file(COPY res/test/application.properties
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/test)


enable_testing()
add_subdirectory(libs/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(libs/csvcollection)

add_executable(csvMongoDB src/main.cpp)
target_link_libraries(csvMongoDB csvcollection)

