#include "NFA2DFA.h"
#include "NFAStateStack.h"

void init_nfa_state_stack(NFAStateStack *ps)
{
    ps->top = -1;
}

void push_nfa_state(NFAStateStack *ps, NFAState *elem)
{
    if(MAX_STACK_LENGTH - 1 <= ps->top)
        return;
    
    ps->top++;
    ps->buffer[ps->top] = elem;

    return;
}

NFAState* pop_nfa_state(NFAStateStack *ps)
{
    int pos;
    NFAState *state = 0;

    if(nfa_state_stack_empty(ps))
        return state;

    pos = ps->top;
    ps->top--;

    return ps->buffer[top];
}

int nfa_state_stack_empty(NFAStateStack *ps)
{
    return -1 == ps->top ? 1 : 0;
}