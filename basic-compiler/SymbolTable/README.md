### 编译
```sh

gcc -o main.exe -c main.c SymbolTable.c -g

# 把所有的C文件都编译为 obj 文件
gcc -c *.c 
# 然后，把所有的obj文件链接为一个可执行文件输出
gcc -o main.exe *.o -g

```