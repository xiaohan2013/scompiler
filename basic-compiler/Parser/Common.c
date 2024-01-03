#include "./Common.h"


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
