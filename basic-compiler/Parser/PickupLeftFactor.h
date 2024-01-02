#pragma once

#ifndef __PICKUP_LEFT_FACTOR_H__
#define __PICKUP_LEFT_FACTOR_H__

#include "Common.h"

RuleSymbol* get_symbol(RuleSymbol *pSelect, int index);
int left_factor_max_length(RuleSymbol *pSelectTemplate);
int symbol_cmp(RuleSymbol *pRuleSymbol1, RuleSymbol *pRuleSymbol2);
int need_pickup(RuleSymbol *pSelectTemplate, int cnt, RuleSymbol *pSelect);
void add_select_to_rule(Rule *pRule, RuleSymbol *pRuleSymbol);
void get_unique_rule_name(Rule *pRule, char *pRuleName);
void pickup_left_factor(Rule *pHead);
void free_select(RuleSymbol *pSelect);


#endif /* __PICKUP_LEFT_FACTOR_H__ */
