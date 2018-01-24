cmake_minimum_required(VERSION 3.9)

project(csvcollection)

set(HEADERS_FILES
        inc/csvcollection.h
        )

set(SOURCES_FILES
        src/csvcollection.cpp
        )

add_library(csvcollection STATIC ${HEADERS_FILES} ${SOURCES_FILES})

target_include_directories(csvcollection
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        PUBLIC $<INSTALL_INTERFACE:inc/csvcollection>
        )