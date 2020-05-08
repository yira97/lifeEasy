cmake_minimum_required(VERSION 3.15)
project(lifeEasy)

add_compile_options(-std=c++17)

include_directories(include)

add_executable(lifeEasy src/main.cpp)