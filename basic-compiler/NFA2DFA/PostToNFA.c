#include <stdio.h>

#include "PostToNFA.h"
#include "NFAFragmentStack.h"

NFAFragmentStack fragmentStack;

// Initialize fragment stack
int nstate = 1;
NFAState* create_nfa_state()
{
    NFAState *s = (NFAState*)malloc(sizeof(NFAState));

    s->name = nstate++;
    s->transform = '\0';
    s->next1 = NULL;
    s->next2 = NULL;
    s->accept_flag = 0;

    return s;
}

NAFFragment make_nfa_fragment(NFAState *start_state, NFAState *accept_state)
{
    return {start_state, accept_state};
}


NFAState* post2nfa(char *postfix)
{
    char *p;
    NAFFragment *f1, *f2, fm;
    NAFFragment f = {0, 0};
    NFAState *new_start_state, *new_accept_state;
    p = postfix;

    while (*p != '\0')
    {
        char ch = *p;
        switch (ch)
        {
        case /* constant-expression */:
            /* code */
            break;
        
        default:
            break;
        }
        ++p;
    }

    return f;
}