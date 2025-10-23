cmake_minimum_required(VERSION 3.15)
project(OpenWorldGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(GameMain 
    main.cpp
    ecs_types.h
    component_pool.h
    ecs_registry.h
    game_components.h
    game_systems.h
    game.h
)

# Compiler options
target_compile_options(GameMain PRIVATE -Wall -Wextra -O2)

# C++ standard
set_target_properties(GameMain PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)