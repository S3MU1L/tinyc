cmake_minimum_required(VERSION 3.16)
project(tinyc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_path(ZSTD_INCLUDE_DIR zstd.h PATHS /usr/include /usr/local/include NO_DEFAULT_PATH)
find_library(ZSTD_LIBRARY NAMES zstd zstdcodec zstd_shared PATHS /usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib /lib /lib64 NO_DEFAULT_PATH)

if(NOT ZSTD_INCLUDE_DIR)
    find_path(ZSTD_INCLUDE_DIR zstd.h)
endif()
if(NOT ZSTD_LIBRARY)
    find_library(ZSTD_LIBRARY zstd)
endif()

if(ZSTD_LIBRARY AND NOT TARGET zstd::libzstd_shared)
    add_library(zstd::libzstd_shared SHARED IMPORTED)
    set_target_properties(zstd::libzstd_shared PROPERTIES
            IMPORTED_LOCATION "${ZSTD_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${ZSTD_INCLUDE_DIR}"
    )
endif()


find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(tinyc
        tinyc/src/main.cpp
        tinyc/src/lexer/token_type.hpp
        tinyc/src/lexer/token.hpp
        tinyc/src/common/args_parser.hpp
        tinyc/src/common/error.hpp
        tinyc/src/common/file_util.hpp
        tinyc/src/lexer/lexer.hpp
        tinyc/src/lexer/lexer.cpp
        tinyc/src/common/option.hpp
        tinyc/src/ast/expr.hpp
        tinyc/src/ast/stmt.hpp
        tinyc/src/parser/parser.hpp
        tinyc/src/parser/parser.cpp
        tinyc/src/codegen/codegen.hpp
        tinyc/src/codegen/codegen.cpp
        tinyc/src/ast/expr.cpp
        tinyc/src/ast/stmt.cpp
)

llvm_map_components_to_libnames(LLVM_LIBS Core Support)
target_link_libraries(tinyc PRIVATE ${LLVM_LIBS})
