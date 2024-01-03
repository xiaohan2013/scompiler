#pragma once

#ifndef __ELIMINATE_LEFT_RECURSION_H__
#define __ELIMINATE_LEFT_RECURSION_H__

void add_symbol_to_select(RuleSymbol *pSelect, RuleSymbol *pNewSymbol);
void add_select_to_rule(Rule *pRule,RuleSymbol *pNewSelect);

/*
    Direct Left recursion: A->Aα
    InDirect Left recursion: 
    Algorithm: eleminate left recursion
    Input: A grammar: a set of nonterminals A1,...,An，and their productions
    Output: A modified grammar generating the same language but without left recursion

    1. For each non-terminals Ai:
        1. Repeat until an iteration leaves the grammar unchanged;
            for each rule Ai->ai，ai being a sequence of terminals and non-terminals
                if ai begins with a nonterminals Aj and j < i:
                    Let βi be αi without its leading Aj
                    Remove the rule Ai -> αi
                    For each rule Aj -> αj
                        add the rule Ai -> αjβi
        2. Remove direct left recursion for Ai as described above.
*/
void eliminate_left_recursion(Rule *pHead);

int symbol_need_replace(const Rule *pCurrentRule, const RuleSymbol * pSymbol);
RuleSymbol* copy_symbol(Rule *pRule, RuleSymbol *pSymbolTemplate);
RuleSymbol* copy_select(const RuleSymbol *pSelectTemplate);
void free_select(RuleSymbol *pSelect);
RuleSymbol* repalce_select(const RuleSymbol *pSelectTemplate);
int rule_has_left_recursion(Rule *pRule);

#endif /* __ELIMINATE_LEFT_RECURSION_H__ */
