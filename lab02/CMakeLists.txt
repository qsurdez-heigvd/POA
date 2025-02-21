cmake_minimum_required(VERSION 3.10)
project(LabSquadron)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

include_directories(.)

enable_testing()

add_executable(squadron src/main.cpp
        src/ship/Ship.cpp
        src/ship/Ship.hpp
        src/squadron/Squadron.cpp
        src/squadron/Squadron.hpp
        src/ship/cargo/CargoShip.cpp
        src/ship/cargo/CargoShip.hpp
        src/ship/TIE/TIE.cpp
        src/ship/TIE/TIE.hpp
        src/ship/TIE/TIEInterceptor.cpp
        src/ship/TIE/TIEInterceptor.hpp
        src/ship/cargo/Shuttle.cpp
        src/ship/cargo/Shuttle.hpp
        src/ship/cargo/StarDreadnought.cpp
        src/ship/cargo/StarDreadnought.hpp
        src/utils/ostreamUtils.cpp
        src/utils/ostreamUtils.hpp
        src/ship/TIE/TIEBaseModel.cpp
        src/ship/TIE/TIEBaseModel.hpp)

add_executable(testUnits src/test/test.cpp
        src/ship/Ship.cpp
        src/ship/Ship.hpp
        src/squadron/Squadron.cpp
        src/squadron/Squadron.hpp
        src/ship/cargo/CargoShip.cpp
        src/ship/cargo/CargoShip.hpp
        src/ship/TIE/TIE.cpp
        src/ship/TIE/TIE.hpp
        src/ship/TIE/TIEInterceptor.cpp
        src/ship/TIE/TIEInterceptor.hpp
        src/ship/cargo/Shuttle.cpp
        src/ship/cargo/Shuttle.hpp
        src/ship/cargo/StarDreadnought.cpp
        src/ship/cargo/StarDreadnought.hpp
        src/utils/ostreamUtils.cpp
        src/utils/ostreamUtils.hpp
        src/ship/TIE/TIEBaseModel.cpp
        src/ship/TIE/TIEBaseModel.hpp)

set_target_properties(testUnits PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(
        testUnits
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(testUnits)