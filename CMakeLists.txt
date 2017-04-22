cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR)
project (Kaleidoscope)

set(CMAKE_CXX_STANDARD 14)

include_directories ("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/lib")
add_subdirectory (lib)

add_executable(kaleidoscope main.cpp)
target_link_libraries(kaleidoscope Kompiler)
