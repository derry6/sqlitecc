project(sqlitecc)
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(include/sqlitecc)
add_subdirectory(src)
add_subdirectory(examples)


