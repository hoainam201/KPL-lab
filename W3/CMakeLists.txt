cmake_minimum_required(VERSION 3.19)
project(W3 C)

set(CMAKE_C_STANDARD 99)

add_executable(W3 main.c charcode.c error.c parser.c reader.c scanner.c token.c)