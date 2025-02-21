cmake_minimum_required(VERSION 3.15)
project(buffy CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(buffy
        src/main.cpp
        src/humanoids/Humanoid.hpp
        src/humanoids/Humanoid.cpp
        src/humanoids/Human.hpp
        src/humanoids/Human.cpp
        src/humanoids/Vampire.hpp
        src/humanoids/Vampire.cpp
        src/action/Action.hpp
        src/action/Action.cpp
        src/utils/Vec2D.hpp
        src/utils/Vec2D.cpp
        src/humanoids/Buffy.hpp
        src/humanoids/Buffy.cpp
        src/action/Bite.hpp
        src/action/Kill.hpp

        src/utils/Vec2D.cpp
        src/humanoids/Human.cpp
        src/action/Move.hpp
        src/field/Field_Generic_Impl.hpp

        src/action/Bite.cpp
        src/action/Kill.cpp
        src/action/Action.cpp
        src/action/Move.cpp
        src/field/Field.hpp
        src/field/Field.cpp
        src/display/FieldController.hpp
        src/display/FieldController.cpp

        src/utils/Random.cpp
        src/utils/Random.hpp


        src/stats/FieldStatsCalculator.cpp
        src/stats/FieldStatsCalculator.hpp
        src/utils/Status.hpp
)
