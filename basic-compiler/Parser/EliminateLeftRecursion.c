#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Common.h"
#include "EliminateLeftRecursion.h"

const char *VoidSymbol = "$ ";
const char *Postfix = "'";

// 将一个RuleSymbol添加到 Select 的末尾
// Select 是该产生式的候选项
void add_symbol_to_select(RuleSymbol *pSelect, RuleSymbol *pNewSymbol)
{
    // TODO
    if(NULL == pSelect) 
        return;
    // 找到下一个RuleSymbol 为 NULL
    while (pSelect->pNextSymbol != NULL)
    {
        pSelect = pSelect->pNextSymbol;
    }
    pSelect->pNextSymbol = pNewSymbol;
}

// 将一个 Select 加入到一个文法末尾。当 Select 为 NULL 是就将一个 epsilon 终结符加入到文法末尾
// pRule：文法指针
// pNewSelect: select 指针
void add_select_to_rule(Rule *pRule, RuleSymbol *pNewSelect)
{
    // TODO
    if(NULL == pNewSelect)
    {
        pNewSelect=create_rule_symbol();
        pNewSelect->isToken=1;
        strcpy(pNewSelect->TokenName,VoidSymbol); //strcpy(dest,sour)
    }
    while (pRule->pNextRule != NULL)
    {
        pRule = pRule->pNextRule;
    }
    pRule->pFirstSymbol = pNewSelect;
}

// 左递归：文法中一个非终结符A使得对某个串α，存在一个推导 A->+ Aα
// 直接左递归：存在 A->* Aα，否则间接左递归
// A -> Aa | bA | c | Ad
// A -> bAA' | cA'
// A'-> aA'| dA'| $
// 算法：
//    1. 对 A 产生式进行分组，
//    2. 
void eliminate_left_recursion(Rule *pHead)
{
    RuleSymbol *pSelect; // Select游标
    Rule *pNewRule; // Rule指针
    // TODO
    // 识别左递归: Select链表中
    // 替换对应的产生式
    // 创建 A'
    Rule *pRule = pHead;
    while (pRule != NULL)
    {
        char *rule_name = pHead->RuleName;
        RuleSymbol *pSelect = pHead->pFirstSymbol;

        strcat(rule_name, Postfix);  // 就是A-> A'
        Rule *pNewRule = create_rule(rule_name);
        RuleSymbol *pNewRuleSymbol = create_rule_symbol();
        strcpy(pNewRuleSymbol->TokenName, rule_name);
        pNewRuleSymbol->isToken = 0;
        pNewRuleSymbol->pRule = pNewRule;

        // 产生式左部和右部第一个符号相等
        while (pSelect != NULL)
        {
            RuleSymbol *pRuleSymbolPart = pSelect;
            // 非终结符
            if(pSelect->isToken == 0 && strcmp(pSelect->TokenName, rule_name) == 0)
            {
                add_symbol_to_select(pRuleSymbolPart, pNewRuleSymbol);
                if(pNewRule->pFirstSymbol == NULL)
                {
                    pNewRule->pFirstSymbol = pRuleSymbolPart;
                }
                else
                {
                    RuleSymbol *pSymbol = pNewRule->pFirstSymbol;
                    while(pSymbol->pOther != NULL) {}
                    pSymbol->pOther = pRuleSymbolPart;
                }
            }

            // 终结符
            if(pSelect->isToken == 1)
            {
                add_symbol_to_select(pRuleSymbolPart, pNewRuleSymbol);
            }
            pSelect = pSelect->pOther;
        }
        pRule = pRule->pNextRule;

        // 根据Rule A'是否存在 RuleSymbol 来判断是否需要将其加入到
        if(pNewRule->pFirstSymbol != NULL)
        {
            add_select_to_rule(pHead, pNewRule);
        }
    }
    return;
}


int main(int argc, char* argv[])
{
    // 初始化文法
    Rule *pHead = init_rules();

    printf("Before remove left recursion: \n");
    print_rule(pHead);

    printf("After removing left recursion: \n");
    // remove_left_recursion(pHead);

    return 0;
}


