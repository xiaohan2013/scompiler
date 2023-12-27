#ifndef __NFAFRAGMENTSTATESTACK_H__
#define __NFAFRAGMENTSTATESTACK_H__

#include "NFAToDFA.h"

#define MAX_STACK_LENGTH 1024

typedef struct _NFAFragmentStack
{
    NFAFragment buffer[MAX_STACK_LENGTH];
    int top;
}NFAFragmentStack;


// 声明函数
void init_nfa_fragment_stack(NFAFragmentStack *ps);
void push_nfa_fragment(NFAFragmentStack *ps, NFAFragment elem);
NFAFragment pop_nfa_fragment(NFAFragmentStack *ps);
int nfa_fragment_stack_empty(NFAFragmentStack *ps);



#endif /* __NFAFRAGMENTSTATESTACK_H__ */
