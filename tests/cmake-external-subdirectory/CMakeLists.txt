cmake_minimum_required(VERSION 3.14)

project(cmake VERSION 1.0.0)

add_subdirectory(../.. darr)

add_executable(main main.c)
target_link_libraries(main darr)
