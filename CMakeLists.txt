cmake_minimum_required(VERSION 3.17)
project(glplayground)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(thirdparty)
find_package(OpenGL REQUIRED)

find_package(SDL3 QUIET)

# ------------------------- qrlx
add_subdirectory(lib)
add_subdirectory(src)
