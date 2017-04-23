cmake_minimum_required (VERSION 2.8.7 FATAL_ERROR)
project (Kaleidoscope)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXT_DIR ext)

configure_file(${CMAKE_EXT_DIR}/gtest/CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

add_subdirectory(
  ${CMAKE_BINARY_DIR}/googletest-src
  ${CMAKE_BINARY_DIR}/googletest-build
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/lib")
add_subdirectory(lib)

add_executable(kaleidoscope main.cpp)
target_link_libraries(kaleidoscope Kompiler)

add_subdirectory(tests)
add_test(NAME tests COMMAND tests)
enable_testing(true)

