#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "EliminateLeftRecursion.h"


const char *VoidSymbol = "$ ";
const char *postfix = "'";


typedef struct _SYMBOL
{
    int isToken;
    char Name[MAX_STR_LENGTH];
}SYMBOL;

typedef struct _RULE_ENTRY
{
    char RuleName[MAX_STR_LENGTH];
    SYMBOL Selects[64][64]; // 
}RULE_ENTRY;

static const RULE_ENTRY rule_table[] = {
    // A -> Aa | bA | c | Ad 
    "A",{
            {{0, "A"}, {1, "a"}},
            {{1, "b"}, {0, "A"}},
            {{1, "c"}},
            {{0, "A"}, {1, "d"}}
        }
};

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

Rule* init_rules(void)
{
    Rule *pHead,*pRule;

    RuleSymbol *pSymbolPtr1 = NULL, *pSymbolPtr2 = NULL;
    int nRuleCount = sizeof(rule_table) / sizeof(rule_table[0]);

    int i, j, k;
    Rule **pRulePtr = &pHead;
    for(i = 0; i < nRuleCount; i++)
    {
        *pRulePtr = create_rule(rule_table[i].RuleName);
        pRulePtr = &(*pRulePtr)->pNextRule;
    }

    pRule = pHead;
    for(i = 0; i < nRuleCount; i++)
    {
        for(j = 0; rule_table[i].Selects[j][0].Name[0] != '\0'; j++)
        {
            for(k = 0; k < rule_table[i].Selects[j][k].Name[0] != '\0'; k++)
            {
                const SYMBOL *pSymbol = &rule_table[i].Selects[j][k];
                printf("Symbol: [%d][%d] = {%s} \n", j, k, pSymbol->Name);

                RuleSymbol *newRuleSymbol = create_rule_symbol();
                newRuleSymbol->isToken = pSymbol->isToken;

                if(1 == pSymbol->isToken)
                {
                    // 终结符
                    strcpy(newRuleSymbol->TokenName, pSymbol->Name);
                }
                else
                {   
                    // 非终结符
                    strcpy(newRuleSymbol->TokenName, pSymbol->Name);
                    newRuleSymbol->pRule = find_rule(pHead, pSymbol->Name);
                    if(NULL == newRuleSymbol->pRule)
                    {
                        printf("Init rules error, miss rule \"%s\"\n", pSymbol->Name);
                        exit(1);
                    }
                }

                if(pSymbolPtr2 == NULL)
                {
                    pSymbolPtr2 = newRuleSymbol;
                    if(pSymbolPtr1 == NULL)
                    {
                        pSymbolPtr1 = pSymbolPtr2;
                        if(pRule->pFirstSymbol == NULL)
                        {
                            pRule->pFirstSymbol = pSymbolPtr1;
                        }
                    }
                    else
                    {
                        pSymbolPtr1->pOther = pSymbolPtr2;
                        pSymbolPtr1 = pSymbolPtr2;
                    }
                }
                else
                {
                    pSymbolPtr2->pNextSymbol = newRuleSymbol;
                    pSymbolPtr2 = newRuleSymbol; // 移动下一个
                }
            }
            printf("=================================================================\n");
            pSymbolPtr2 = NULL;
        }
        pSymbolPtr1 = NULL;
        pRule = pRule->pNextRule;
    }
    return pHead;
}

// 将一个RuleSymbol添加到 Select 的末尾
// Select 是该产生式的候选项
void add_symbol_to_select(RuleSymbol *pSelect, RuleSymbol *pNewSymbol)
{
    // TODO
    if(NULL == pSelect) 
        return;
    // 找到下一个RuleSymbol 为 NULL
    while (pSelect->pOther != NULL)
    {
        pSelect = pSelect->pOther;
    }
    pSelect->pOther = pNewSymbol;
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
void remove_left_recursion(Rule *pHead)
{
    RuleSymbol *pSelect; // Select游标
    Rule *pNewRule; // Rule指针
    // TODO
    // 识别左递归: Select链表中
    // 替换对应的产生式
    // 创建 A'
    while (pHead != NULL)
    {
        char rule_name = pHead->RuleName;
        RuleSymbol *pSelect = pHead->pFirstSymbol;

        Rule *pp = create_rule();
        strcat(pNewRule->RuleName, Postfix); // 就是A-> A'
        // 产生式左部和右部第一个符号相等
        while (pSelect != NULL)
        {
            if(pSelect->isToken == 0 && pSelect->TokenName == rule_name)
            {
                pp->pFirstSymbol = pSelect->pNextSymbol;
                
            }

            if(pSelect->isToken == 1)
            {
                
            }

            pSelect = pSelect->pOther;
        }
        pHead = pHead->pNextRule;
    }
    
    return;
}

Rule* create_rule(const char *pRuleName)
{
    Rule* pRule = (Rule*)malloc(sizeof(Rule));

    strcpy(pRule->RuleName, pRuleName);
    pRule->pFirstSymbol = NULL;
    pRule->pNextRule = NULL;

    return pRule;
}

RuleSymbol* create_rule_symbol(void)
{
    RuleSymbol *pSymbol = (RuleSymbol*)malloc(sizeof(RuleSymbol));

    pSymbol->pNextSymbol = NULL;
    pSymbol->pOther = NULL;
    pSymbol->isToken = -1;
    pSymbol->TokenName[0] = '\0';
    pSymbol->pRule = NULL;

    return pSymbol;
}

Rule* find_rule(Rule *pHead, const char *RuleName)
{
    Rule *pRule;
    for(pRule=pHead; pRule != NULL; pRule = pRule->pNextRule)
    {
        if(0 == strcmp(pRule->RuleName, RuleName))
        {
            break;
        }
    }

    return pRule;
}

void print_rule(Rule *pHead)
{
    // TODO
    int nRuleCount = sizeof(rule_table) / sizeof(rule_table[0]);
    int i = 0;
    Rule *p = pHead;
    while (p != NULL)
    {
        printf("%s->", p->RuleName);
        RuleSymbol *ppHead = p->pFirstSymbol;
        while (ppHead != NULL)
        {
            RuleSymbol *ppp = ppHead;
            while (ppp != NULL)
            {
                printf("%s", ppp->TokenName);
                ppp = ppp->pNextSymbol;
            }
            
            if(ppHead->pOther != NULL) 
            {
                printf(" | ");
            }

            ppHead = ppHead->pOther;
        }
        
        p = p->pNextRule;
    }
}
