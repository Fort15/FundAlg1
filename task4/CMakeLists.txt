cmake_minimum_required(VERSION 3.10)
project(task4 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(task4_exe main.c constants.c)

target_link_libraries(task4_exe m)