#include "NFA2DFA.h"
#include "NFAFragmentStack.h"

void init_nfa_fragment_stack(NFAFragmentStack *ps)
{
    ps->top = -1;
}

void push_nfa_fragment(NFAFragmentStack *ps, NFAFragment *elem)
{
    if(MAX_STACK_LENGTH - 1 <= ps->top)
        return;
    
    ps->top++;
    ps->buffer[ps->top] = elem;

    return;
}

NFAFragment* pop_nfa_fragment(NFAFragmentStack *ps)
{
    int pos;
    NFAFragment *state = 0;

    if(nfa_fragment_stack_empty(ps))
        return state;

    pos = ps->top;
    ps->top--;

    return ps->buffer[top];
}

int nfa_fragment_stack_empty(NFAFragmentStack *ps)
{
    return -1 == ps->top ? 1 : 0;
}