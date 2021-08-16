cmake_minimum_required(VERSION 3.8)
project(flex_intro)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_C_FLAGS "-m64 -g -O0 -D_DEBUG -Wall")

set(C_SOURCE_FILES src/flex.c)

set(FLEX_SOURCE_FILES src/flex.l)

include_directories(AFTER src)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(
        Parser
        src/dummy.y
        ${CMAKE_SOURCE_DIR}/src/parser/parser.c
)

FLEX_TARGET(
        Scanner
        ${FLEX_SOURCE_FILES}
        ${CMAKE_SOURCE_DIR}/src/lexer/lexer.c
)

ADD_FLEX_BISON_DEPENDENCY(
        Scanner
        Parser
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
        flex
        ${C_SOURCE_FILES}
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
)
