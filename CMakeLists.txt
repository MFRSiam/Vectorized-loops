cmake_minimum_required(VERSION 3.26)
enable_language(ASM)
project(CppVectorisedLoops)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FAs")

if(MSVC)
    add_compile_options(/arch:AVX512)
endif()

add_executable(CppVectorisedLoops main.cpp
        src/vFor.cpp
        src/vFor.hpp)
