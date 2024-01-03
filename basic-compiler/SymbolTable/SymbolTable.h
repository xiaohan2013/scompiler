#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#include <stdio.h>

#define MAX_STR_LENGTH 64
#define BUCKET_SIZE 5

typedef struct __Symbol {
    char SymbolName[MAX_STR_LENGTH]; // 符号名称
    char SymbolType[MAX_STR_LENGTH]; // 符号类型
    int ClashCount; // 冲突次数
    int RefCount; // 引用次数
    struct __Symbol *pNext; // 指向下一个Symbol
}Symbol;

typedef struct __SymbolTable
{
    Symbol *Bucket[BUCKET_SIZE]; // 符号桶
    int Invalid; // 作用域是否无效：1： 无效，0：有效
    struct __SymbolTable *pNext; // 执向下一个SymbolTable
}SymbolTable;

Symbol* new_symbol();
SymbolTable* new_symbol_table();
void push_scope();
void pop_scope();
void ref_symbol(const char *pSymbolName);
void add_symbol(const char *pSymbolName, const char *pSymbolType);
int Hush(const char *pSymbolName);
void create_symbol_table();


extern SymbolTable *pHead;
extern int RefErrorCount;

#endif /* __SYMBOL_TABLE_H__ */
