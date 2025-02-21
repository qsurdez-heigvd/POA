cmake_minimum_required(VERSION 3.10)
project(LabMatrix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

include_directories(.)

enable_testing()

add_executable(matrix src/Matrix.cpp src/Matrix.hpp src/main.cpp
        src/operations/Operation.hpp
        src/operations/Subtraction.cpp
        src/operations/Subtraction.hpp
        src/operations/Multiplication.cpp
        src/operations/Multiplication.hpp
        src/operations/Addition.cpp
        src/operations/Addition.hpp
        src/utils/utils.cpp
        src/utils/utils.hpp)

add_executable(testMatrix test/test.cpp src/Matrix.hpp src/Matrix.cpp
        src/operations/Addition.hpp
        src/operations/Addition.cpp
        src/operations/Operation.hpp
        src/operations/Subtraction.cpp
        src/operations/Subtraction.hpp
        src/operations/Multiplication.cpp
        src/operations/Multiplication.hpp
        src/utils/utils.hpp
        src/utils/utils.cpp)

set_target_properties(matrix PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(
        testMatrix
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(testMatrix)

if(MSVC)
    target_compile_options(matrix PRIVATE /W4 /WX)
else()
    target_compile_options(matrix PRIVATE -Wall -Wpedantic -Werror)
endif()