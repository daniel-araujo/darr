cmake_minimum_required(VERSION 3.14)

project(darr VERSION 1.7.8)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

install(TARGETS darr DESTINATION lib)
install(FILES src/darr.h DESTINATION include)
