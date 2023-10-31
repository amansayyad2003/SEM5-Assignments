cmake_minimum_required(VERSION 3.22.1)
project("Calci")

include_directories(mylib)

add_executable(a.out main.cpp)
target_link_libraries(a.out calci)

add_subdirectory(mylib)
