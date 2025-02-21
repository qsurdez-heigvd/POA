cmake_minimum_required(VERSION 3.15)
project(river CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(river
        src/Controller.cpp
        src/Controller.hpp
        src/containers/Container.cpp
        src/containers/Container.hpp
        src/person/Person.cpp
        src/person/Person.hpp
        src/containers/Bank.cpp
        src/containers/Bank.hpp
        src/containers/Boat.cpp
        src/containers/Boat.hpp
        src/person/Thief.cpp
        src/person/Thief.hpp
        src/person/Kid.cpp
        src/person/Kid.hpp
        src/person/Girl.cpp
        src/person/Girl.hpp
        src/person/Boy.cpp
        src/person/Boy.hpp
        src/StateResult.hpp
        src/StateResult.cpp
        src/main.cpp
        src/person/IndependentPerson.hpp
        src/person/IndependentPerson.cpp
)
