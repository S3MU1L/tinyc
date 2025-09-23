cmake_minimum_required(VERSION 3.16)
project(tinyc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

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
        tinyc/src/parser/expr.hpp
        tinyc/src/parser/stmt.hpp
        tinyc/src/parser/parser.hpp
        tinyc/src/parser/parser.cpp
        tinyc/src/parser/ast_printer.hpp
        tinyc/src/parser/ast_printer.hpp
        tinyc/src/codegen/codegen.hpp
        tinyc/src/codegen/codegen.cpp
)

target_link_libraries(tinyc PRIVATE LLVM)