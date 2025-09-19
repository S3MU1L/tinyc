cmake_minimum_required(VERSION 4.0)
project(tinyc)

set(CMAKE_CXX_STANDARD 17)

add_executable(tinyc
        tinyc/src/main.cpp
        tinyc/src/lexer/token_type.hpp
        tinyc/src/lexer/token.hpp
        tinyc/src/util/args_parser.hpp
        tinyc/src/util/error.hpp
        tinyc/src/util/file_reader.hpp
        tinyc/src/lexer/lexer.hpp
        tinyc/src/lexer/lexer.cpp
        tinyc/src/util/option.hpp
        tinyc/src/parser/Expr.hpp
        tinyc/src/parser/Stmt.hpp)
