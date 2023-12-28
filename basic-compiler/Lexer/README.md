```sh
# 生成源文件

rm -rf main.c && flex -DYY_SKIP_YYWRAP -d -v -f -o main.c main.lex 
rm -rf main.c && flex -d -v -f -o main.c main.lex 

# 编译
gcc -ansi -Wall -E -c -g main.c -o main.exe

gcc -g -Wall main.c -o main
./main.exe sample.txt

# 打印系统中已经登记的库
ldconfig -p
ldconfig -l <file_path_of_shared_libraries> 
ldconfig <folder_of_shared_libraries>
LD_LIBRARY_PATH=<folder_of_standalone_library>:${LD_LIBRARY_PATH}  <standalone_precess> 
/etc/ld.so.conf.d
ldd <executable_file>
ldd <shared_library>
LDFLAGS+=--allow-shlib-undefined

```
**__需要注意在windows下使用flex写文件需要从info flex下去拷贝一个模板然后再编辑__**