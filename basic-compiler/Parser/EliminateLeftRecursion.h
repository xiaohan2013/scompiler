#ifndef __ELIMINATE_LEFT_RECURSION_H__
#define __ELIMINATE_LEFT_RECURSION_H__

#include "Common.h"


void add_symbol_to_select(RuleSymbol *pSelect, RuleSymbol *pNewSymbol);
void add_select_to_rule(Rule *pRule,RuleSymbol *pNewSelect);
void remove_left_recursion(Rule *pHead);


#endif /* __ELIMINATE_LEFT_RECURSION_H__ */
