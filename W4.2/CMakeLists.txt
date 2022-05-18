cmake_minimum_required(VERSION 3.19)
project(W4_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(W4_2 main.c debug.c error.c parser.c reader.c symtab.c token.c charcode.c scanner.c)