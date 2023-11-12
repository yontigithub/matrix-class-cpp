cmake_minimum_required(VERSION 3.23)
project(matrix_class_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(matrix_class_cpp
    Exceptions.cpp
    Exceptions.h
    main.cpp
    Matrix.h
    utils.h
    utils.cpp)
