cmake_minimum_required(VERSION 3.0)
project(clexer)

set(source src/lexer.cpp src/token.cpp)

include_directories(include)
add_executable(lexer Lexer.cpp ${source})