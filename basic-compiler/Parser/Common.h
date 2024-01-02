#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>

#define MAX_STR_LENGTH 64


typedef struct __SYMBOL
{
    int isToken;
    char SymbolName[MAX_STR_LENGTH];
}SYMBOL;

typedef struct __RULE_ENTRY
{
    char RuleName[MAX_STR_LENGTH]; // 
    SYMBOL symbols[64];
}RULE_ENTRY;


struct __RULE;
typedef struct __RuleSymbol {
    struct __RuleSymbol *pNextSymbol; // 执行下一个 Symbol
    struct __RuleSymbol *pOhter; // 指向下一个 select 
    int isToken; 
    char TokenName[MAX_STR_LENGTH];
    struct __Rule *pRule;
}RuleSymbol;

typedef struct __Rule {
    struct __Rule *pNextRule; // 执向下一条文法
    char RuleName[MAX_STR_LENGTH];  // 文法的名称，产生式的左半部分
    struct __RuleSymbol *pFirstSymbol; // 指向文法的第一个 select 的第一个 Symbol
}Rule;


typedef struct __Set {
    char Name[MAX_STR_LENGTH]; // 集合名称
    char Terminal[32][MAX_STR_LENGTH]; // 终结符数组
    int nTerminalCnt; // 终结符个数
}Set;

typedef struct __SetList {
    Set sets[32]; // 集合数组
    int nSetCnt; // 数组元素个数
}SetList;

Rule* init_rules(void);
Rule* create_rule(const char *pRuleName);
RuleSymbol* create_symbol(void);
Rule* find_rule(Rule *pHead, const char *rule_name);
void print_rule(Rule *pHead);

// 全局变量
extern const char *VoidSymbol;
extern const char *Postfix;

#endif /* __COMMON_H__ */
