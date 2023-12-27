#include <stdio.h>
#include <stdlib.h>

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

NFAFragment make_nfa_fragment(NFAState *start_state, NFAState *accept_state)
{
    NFAFragment n = {start_state, accept_state};
    return n;
}


NFAState* post_to_nfa(char *postfix)
{
    char *p;
    NFAFragment *f1, *f2, fm;
    NFAFragment f = {0, 0};
    NFAState *new_start_state, *new_accept_state;
    p = postfix;

    while (*p != '\0')
    {
        char ch = *p;
        switch (ch)
        {
        case '|':
            /* code */
            break;
        case '&':
            break;
        case '*':
            break;
        case '?':
            break;
        case '+':
            break;
        default:
            break;
        }
        ++p;
    }

    return f.start_state;
}