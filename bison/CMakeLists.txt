cmake_minimum_required(VERSION 3.8)

project(cpn_calculator)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-m64 -g -O0 -D_DEBUG -Wall")

set(SOURCE_FILES
        src/main.c src/calc.c
        ${CMAKE_SOURCE_DIR}/src/lexer/lexer.c
        ${CMAKE_SOURCE_DIR}/src/parser/parser.c
        )

include_directories(AFTER src ${CMAKE_SOURCE_DIR}/src/parser ${CMAKE_SOURCE_DIR}/src/lexer)

find_package(BISON)
find_package(FLEX)

FLEX_TARGET(lexer src/calc.l ${CMAKE_SOURCE_DIR}/src/lexer/lexer.c)
BISON_TARGET(parser src/calc.y ${CMAKE_SOURCE_DIR}/src/parser/parser.c VERBOSE)

ADD_FLEX_BISON_DEPENDENCY(lexer parser)

add_executable(
        calc
        ${SOURCE_FILES}
        ${BISON_parser_OUTPUTS}
        ${FLEX_scanner_OUTPUTS}
)

target_link_libraries(calc m)
