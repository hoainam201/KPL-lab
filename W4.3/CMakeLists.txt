cmake_minimum_required(VERSION 3.19)
project(W4_3 C)

set(CMAKE_C_STANDARD 99)

add_executable(W4_3 main.c charcode.c debug.c error.c parser.c reader.c scanner.c semantics.c symtab.c token.c)