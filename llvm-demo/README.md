


## lexer
```sh
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..


cmake --build .

cmake -S . -B build --trace-source=CMakeLists.txt

cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..

-- Could NOT find LibEdit (missing: LibEdit_INCLUDE_DIRS LibEdit_LIBRARIES)
-- Found zstd: /usr/lib/x86_64-linux-gnu/libzstd.so
-- Could NOT find CURL (missing: CURL_LIBRARY CURL_INCLUDE_DIR)
sudo apt install -y libzstd-dev
sudo apt-get install -y libedit-dev
sudo apt-get install -y libcurl4-openssl-dev


clang-format-17 -i src/*.cpp src/*.h
```

## Compiler
```sh
./src/simple_compiler "with abc,xyz: (abc+xyz)*3 - 10/abc"
./src/simple_compiler "with a: a*3" > simple_compiler.ll

# LLVM llc工具把IR代码编译成目标文件
llc --filetype=obj -o=simple_calulator.o simple_compiler.ll


# Set up C++ standard library and header path
# 借助clang把我们的计算器程序模块跟runtime一起编译生成可执行程序
export SDKROOT=$(xcrun --sdk macosx --show-sdk-path)
clang++ -o SimpleCalculator SimpleCalculator.o ../CalculatorCompilerRuntime.cpp
clang++ -o SimpleCalculator -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk SimpleCalculator.o ../CalculatorCompilerRuntime.cpp

clang++ -w -o HelloLoop `llvm-config --cxxflags --ldflags --system-libs --libs core` HelloLoop.cpp

```

## Pass
LLVM 自定义Pass 工作流程
1. 在 llmv 代码中创建 Pass的路径 /llvm-project/llvm/lib/Transforms/xxxxPass
2. 在 自定义Pass 路径下创建 CMakeLists.txt
3. 在路径下，添加源文件 xxxxPass.cpp
4. 然后把代码加入到 CMakeLists.txt 中
```sh
cd /path/to/llvm-project
mkdir -p build
cd build

cmake -G Ninja -DLLVM_ENABLE_PROJECTS=clang ../llvm

ninja

mv ../llvm/lib/Transforms/SimpleModulePass/Test.c.txt ../llvm/lib/Transforms/SimpleModulePass/Test.c
clang -S -emit-llvm ../llvm/lib/Transforms/SimpleModulePass/Test.c -o ../llvm/lib/Transforms/SimpleModulePass/Test.ll

./bin/opt -load-pass-plugin=lib/SimpleModulePass.dylib -passes="simple-module-pass" -disable-output ../llvm/lib/Transforms/SimpleModulePass/Test.ll


./bin/opt -load-pass-plugin=lib/MyPass.dylib -passes="my-pass" -disable-output test.ll
```


## JIT
```sh
clang++ -w -o HelloJIT `llvm-config-17 --cxxflags --ldflags --system-libs --libs all` HelloJIT.cpp

```