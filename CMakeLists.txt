cmake_minimum_required(VERSION 3.10)
project(SquareMatrix)

set(CMAKE_CXX_STANDARD 14)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/debug/build)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/release/build)

include_directories(.)

find_package(Threads)

add_executable(SquareMatrix
        main.cpp
        SquareMatrix.h
        SquareMatrixController.h)

target_link_libraries (SquareMatrix ${CMAKE_THREAD_LIBS_INIT})