cmake_minimum_required(VERSION 4.0)
project(tinyc)

set(CMAKE_CXX_STANDARD 14)

add_executable(tinyc
        tinyc/main.cpp
        tinyc/src/lexer/token_type.h
        tinyc/src/lexer/token.h)
