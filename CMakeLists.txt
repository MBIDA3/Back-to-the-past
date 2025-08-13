cmake_minimum_required(VERSION 3.29)
project(Back_to_the_past C)

set(CMAKE_C_STANDARD 23)

add_executable(Back_to_the_past main.c
        story.c
        game_engine.c
        inventor.c
        save_load.c
        error.c
        includes/story.h
        includes/inventor.h
        includes/game_engine.h
        includes/error.h
        includes/save_load.h
)
