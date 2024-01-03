#include "./SymbolTable.h"

#include <stdlib.h>
#include <string.h>

SymbolTable *pHead = NULL;
int RefErrorCount = 0;

Symbol* new_symbol()
{
    Symbol *pNewSymbol = (Symbol*)malloc(sizeof(Symbol));
    memset(pNewSymbol, 0, sizeof(Symbol));

    return pNewSymbol;
}


SymbolTable* new_symbol_table()
{
    SymbolTable *pNewTable = (SymbolTable*)malloc(sizeof(SymbolTable));
    memset(pNewTable, 0, sizeof(SymbolTable));
    return pNewTable;
}

// 在符号表链表的表头添加一个作用域
void push_scope()
{
    SymbolTable *p = new_symbol_table();
    if(pHead == NULL)
    {
        pHead = p;
    }
    else
    {
        p->pNext = pHead;
        pHead = p;
    }
}

// 把符号表链表中最内层的作用域设置为无效
void pop_scope()
{
    if(pHead == NULL) return;
    pHead->Invalid = 1;
}

// 对 symbol 进行一次引用
void ref_symbol(const char *pSymbolName)
{
    int pos = Hush(pSymbolName);
    Symbol *pSymbolList = pHead->Bucket[pos];

    if(pSymbolList == NULL) return;

    Symbol *p = pSymbolList;
    while (p != NULL)
    {
        if(0 == strcmp(p->SymbolName, pSymbolName))
        {
            p->RefCount++;
            return;
        }
        p = p->pNext;
    }
    return;
}

// 向符号表中添加一个 Symbol
// pSymbolName: 符号名称字符串指针
// pSymbolType: 符号类型字符串指针
void add_symbol(const char *pSymbolName, const char *pSymbolType)
{
    Symbol *pSymbol = new_symbol();
    strcpy(pSymbol->SymbolName, pSymbolName);
    strcpy(pSymbol->SymbolType, pSymbolType);

    int pos = Hush(pSymbolName);

    // 处理冲突
    Symbol *p = pHead->Bucket[pos];
    if(p == NULL)
    {
        pHead->Bucket[pos] = pSymbol;
    }
    else
    {
        while(p != NULL) p = p->pNext;
        p->pNext = pSymbol;
    }
}

// 求 Symbol 的哈希值
int Hush(const char *pSymbolName)
{
    int HashVal = 0, i;
    for(i = 0; i < pSymbolName[i] != '\0'; i++)
    {
        HashVal = ((HashVal << 4) + pSymbolName[i]) % BUCKET_SIZE;
    }

    return HashVal;
}

// 创建符号表
void create_symbol_table()
{
    push_scope();
    add_symbol("i", "int");
    add_symbol("j", "int");
    add_symbol("f", "function");
    {
        push_scope();
        add_symbol("i", "char");
        add_symbol("size", "int");
        add_symbol("temp", "char");

        {
            push_scope();
            add_symbol("i", "char *");
            add_symbol("j", "long");

            ref_symbol("j");
            ref_symbol("i");
            ref_symbol("f");
            ref_symbol("size");
            ref_symbol("new");

            pop_scope();
        }

        ref_symbol("j");
        pop_scope();
    }
    pop_scope();
}