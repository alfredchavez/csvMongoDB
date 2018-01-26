cmake_minimum_required(VERSION 3.9)

project(csvcollectiontest)

set(TEST_FILES
        csvcollectiontest.cpp
        collectiontest.cpp
)

enable_testing()
add_executable(csvcollectiontest ${TEST_FILES})
target_link_libraries(csvcollectiontest
        gtest
        gtest_main
        csvcollection
        )

set(csvcollectiontest1 csvcollectiontest)

add_custom_command(TARGET ${csvcollectiontest1}
        POST_BUILD
        COMMAND ctest -V --output-on-failure
        )

add_test(csvcollectiontest csvcollectiontest)
