#include "PickupLeftFactor.h"


RuleSymbol* get_symbol(RuleSymbol *pSelect, int index)
{
    int i = 0;
    RuleSymbol *pRuleSymbol;
    for(pRuleSymbol = pSelect, i = 0; pRuleSymbol != NULL; pRuleSymbol = pRuleSymbol->pNextSymbol,i++)
    {
        if(i == index)
            return pRuleSymbol;
    }
    return NULL;
}

// 比较两个类型相同的Symbol是否具有相同名字
// 相同返回1，不同返回0
int symbol_cmp(RuleSymbol *pSymbol1,  RuleSymbol *pSymbol2)
{
    if(pSymbol1->isToken == pSymbol2->isToken && strcmp(pSymbol1->TokenName, pSymbol2->TokenName) == 0)
    {
        return 1;
    }
    return 0;
}


// 以 SelectTempalte为模块，确定左因子的最大长度
// 如果返回0，说明不存在左因子
int left_factor_max_length(RuleSymbol *pSelectTemplate)
{
    int len = 0;
    RuleSymbol *p = pSelectTemplate;
    while (p != NULL)
    {
        
    }
    
}

// 将 pRuleName 与文法中其他的 RuleName 比较，如果相同就增加一个后缀
void get_unique_rule_name(Rule *pHead, char *pRuleName)
{
    Rule *pRuleCursor = pHead;
    for(;pRuleCursor != NULL;)
    {
        if(0 == strcmp(pRuleCursor->RuleName, pRuleName))
        {
            strcat(pRuleName, Postfix);
            pRuleCursor = pHead;
            continue;
        }
        pRuleCursor = pRuleCursor->pNextRule;
    }
}

// 释放一个 Select 内存
void free_select(RuleSymbol *pSelect)
{
    RuleSymbol *p = pSelect;
    while (p != NULL)
    {
        RuleSymbol *pTmp = p;
        p = p->pNextSymbol;
        free(pTmp);
    }
}

int main(int argc, char** argv)
{
    return 1;
}