add_library(
    lexer
    lexer/lexer.hpp
    lexer/lexer.cpp
)

add_library(
    parser
    parser/parser.hpp
    parser/parser.cpp
)

add_library(
    reader
    reader/reader.hpp
    reader/reader.cpp
)

target_include_directories(reader PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/reader")
target_include_directories(lexer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lexer")
target_include_directories(parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/parser")

