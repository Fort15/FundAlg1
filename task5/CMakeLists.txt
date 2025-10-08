cmake_minimum_required(VERSION 3.10)
project(task5 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(task5 main.c functions.c)

target_link_libraries(task5 m)