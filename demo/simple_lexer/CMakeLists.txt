cmake_minimum_required(VERSION 3.8)

project("SimpleLexer")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMKAE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang-cpp)
set(LLVM_INSTALL_PREFIX "/usr/lib/llvm-17")


# CMake的相关cmake文件，由Cmake官方提供的 cmake-modules
include(CheckIncludeFile) # Provides a macro to check if a header file can be included in C.
include(CheckIncludeFileCXX) # Provides a macro to check if a header file can be included in CXX
include(CheckLibraryExists) # Check if the function exists
include(CheckCXXCompilerFlag) # Check whether the CXX compiler supports a given flag

# add LLVM and standard configurations
# 查找名为 LLVM 的包，找不到就报错。实际上找一个名为 llvm.cmake 的文件。不直接去找动态库和头文件而是去找包配置文件
# 只用 Config 模式, 会去不同的位置寻找 LLVMConfig.cmake 文件
# 导入LLVM
# find_package(LLVM REQUIRED CONFIG)
include("/usr/lib/llvm-17/cmake/LLVMConfig.cmake")
set(LLVM_DIR "/usr/lib/llvm-17/cmake")
message("Found LLVM ${LLVM_PACKAGE_VERSION}, build type ${LLVM_BUILD_TYPE}")
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})
include(DetermineGCCCompatible)
include(ChooseMSVCCRT)

# Use LLVM
add_definitions(${LLVM_DEFINITIONS})
message(STATUS "LLVM_DEFINITIONS : ${LLVM_DEFINITIONS}")
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
message(STATUS "LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
# Find the libraries that coorespond to the LLVM components that we wish to use
llvm_map_components_to_libnames(llvm_libs Core)

if(LLVM_COMPILER_IS_GCC_COMPATIBLE)
    if(NOT LLVM_ENABLE_RTTI)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
    endif()
    if(NOT LLVM_ENABLE_EH)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
    endif()
endif()

add_subdirectory("src")