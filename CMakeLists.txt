cmake_minimum_required(VERSION 3.16)

project(ArgumentParser
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(argument_parser
    src/argument_parser.cpp
)

target_include_directories(argument_parser
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
