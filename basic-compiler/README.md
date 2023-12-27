## 编译
```sh
# Generator = make
cmake .. -B build
cmake --build build
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build --trace-source=CMakeLists.txt && cd build && make
rm -rf build && cmake -D CMAKE_BUILD_TYPE=Debug -S . -B build --trace-source=CMakeLists.txt && cd build && make && cd ../ && ./build/NFA2DFA/nfa_2_dfa.exe 
# Generator = Ninja


```
## 问题
1. CMake Error: CMake was unable to find a build program corresponding to "Unix Makefiles".  CMAKE_MAKE_PROGRAM is not set.  You probably need to select a different build tool.
    - 安装 make, pacman -S make



## GCC
```sh

# 加入调试信息
gcc -g -Wall RegexpToPost.c -o RegexpToPost

gdb RegexpToPost.exe
tui enable
b 36
print 
p *pointer@10



```
