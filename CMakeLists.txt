cmake_minimum_required(VERSION 3.20)
project(4InLine)

set(CMAKE_CXX_STANDARD 20)
set(Performance 0)

add_executable(4InLine main.cpp MiniMax.h FourInLine.h auto_tests.h zobristhashing.h TranspositionTable.h)

if (Performance)
    target_compile_options(4InLine PUBLIC "-O3")
    target_compile_options(4InLine PUBLIC "-march=athlon64-sse3")
endif ()
