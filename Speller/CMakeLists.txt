cmake_minimum_required(VERSION 3.16)
project(Speller C)

set(CMAKE_C_STANDARD 11)

add_executable(Speller speller.c dictionary.h dictionary.c)