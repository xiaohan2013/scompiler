## 编译

```sh
bison -vdty sample.y
flex sample.l
gcc -o sample y.tab.c lex.yy.c
```


