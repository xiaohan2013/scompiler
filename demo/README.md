


## lexer
```sh
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..


cmake --build .

cmake -S . -B build --trace-source=CMakeLists.txt

cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..

-- Could NOT find LibEdit (missing: LibEdit_INCLUDE_DIRS LibEdit_LIBRARIES)
-- Found zstd: /usr/lib/x86_64-linux-gnu/libzstd.so
-- Could NOT find CURL (missing: CURL_LIBRARY CURL_INCLUDE_DIR)
sudo apt install -y libzstd-dev
sudo apt-get install -y libedit-dev
sudo apt-get install -y libcurl4-openssl-dev
```

