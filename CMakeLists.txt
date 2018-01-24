cmake_minimum_required(VERSION 3.9)
project(csvMongoDB)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_FLAGS_X "-pthread -lmongoclient -lboost_thread -lboost_system -lboost_regex")

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CMAKE_FLAGS_X}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_FLAGS_X}")

add_executable(csvMongoDB src/main.cpp libs/csvcollection/src/csvcollection.cpp libs/csvcollection/inc/csvcollection.h)