cmake_minimum_required(VERSION 3.0)
project(clexer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(source src/lexer.cpp src/token.cpp)

include_directories(include)
add_executable(main main.cpp ${source})