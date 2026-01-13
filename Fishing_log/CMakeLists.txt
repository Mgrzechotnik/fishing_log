cmake_minimum_required(VERSION 3.15)

project(Fishing_log VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FishingLog src/main.cpp)

target_include_directories(FishingLog PUBLIC include)

file(COPY ${CMAKE_SOURCE_DIR}/fish_list DESTINATION ${CMAKE_BINARY_DIR})
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/logs)