#ifndef __NFASTATESTACK_H__
#define __NFASTATESTACK_H__

#include "NFAToDFA.h"


#define MAX_STACK_LENGTH 1024

typedef struct _NFAStateStack
{
    NFAState *buffer[MAX_STACK_LENGTH];
    int top;
}NFAStateStack;


void init_nfa_state_stack(NFAStateStack *ps);
void push_nfa_state(NFAStateStack *ps, NFAState *elem);
NFAState* pop_nfa_state(NFAStateStack *ps);
int nfa_state_stack_empty(NFAStateStack *ps);

#endif /* __NFASTATESTACK_H__ */
