mkdir build & cd build

cmake -G Ninja -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_EXTERNAL_PROJECT=simplelang \
    -DLLVM_EXTERNAL_SIMPLELANG_SOURCE_DIR=../simplelang \
    -DCMAKE_INSTALL_PREFIX=../llvm-demo \
    /home/dev/demo/simple_lang

# 编译
ninja
# 安装
ninja install
