mkdir build & cd build

cmake -G Ninja -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_EXTERNAL_PROJECT=simplelang \
    -DLLVM_EXTERNAL_SIMPLELANG_SOURCE_DIR=../simplelang \
    -DCMAKE_INSTALL_PREFIX=../llvm-demo \
    /d/research/llvm/demo/simple_lang

# 安装
ninja install