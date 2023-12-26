cmake_minimum_required(VERSION 3.13.4)

project(compiler)

set(CMAKE_C_STANDARD 99)
# set(CMAKE_MAKE_PROGRAM )
set(CMAKE_C_COMPILER /clang64/bin/gcc)
# set(CMAKE_CXX_COMPILER /clang64/bin/g++)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")
set(CMAKE_BUILD_TYPE "Debug")

# add_subdirectory(Re2NFA)
add_subdirectory(NFA2DFA)