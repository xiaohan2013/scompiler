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

/*
    Thompson's construction:
    Reguar expressions and nondeterministic finite automata are tow representations of formal language.This method
    can transform regular expression into an equivlant nondeterministic finite automaton(NFA). This NFA can be used  to match
    strings against the regular expression.
    Rules:
        1. empty-expression ε
        2. symbol a 
        3. union expression: s|t
        4. concatenation expression: st
        5. Kleene star expression: s*
        6. parenthesized expression: (s) -> N(s)
    With these rules, using the empty expression and symbol rules as base cases, it is possible to prove with mathematical induction
    that any regular expression may be converted into an equivalent NFA.
*/
NFAState* post_to_nfa(char *postfix)
{
    char *p;
    NFAFragment *f1, *f2, fm;
    NFAFragment f = {0, 0};
    NFAState *new_start_state, *new_accept_state;
    p = postfix;

    while (*p != '\0')
    {
        char ch = *p++;
        switch (ch)
        {
        case '|':  // union expression
            new_start_state = create_nfa_state();
            new_start_state->transform = '$'
            new_accept_state = create_nfa_state();
            new_accept_state->accept_flag = 1;
            f1 = pop_nfa_fragment(&fragmentStack);
            f1_start_state = f1.start_state;
            f1_accept_state = f1.start_state;
            f2 = pop_nfa_fragment(&fragmentStack);
            f2_start_state = f2.start_state;
            f2_accept_state = f2.accept_state
            new_start_state->next1 = f1_start_state;
            new_start_state->next2 = f2_start_state;
            f1_accept_state->next1 = new_accept_state;
            f1_accept_state->transform = '$';
            f1_accept_state->accept_flag = 0;
            f2_accept_state->next1 = new_accept_state；
            f2_accept_state->transform = '$';
            f2_accept_state->accept_flag = 0;
            fm = make_nfa_fragment(new_start_state, new_accept_state);
            push_nfa_fragment(&fragmentStack, fm);
            break;
        case '&':
            f1 = pop_nfa_fragment(&fragmentStack);
            f2 = pop_nfa_fragment(&fragmentStack);
            f1_start_state = f1.start_state;
            f1_accept_state = f1.accept_state;
            free(f1_accept_state);
            f2_start_state = f2.start_state;
            f2_accept_state = f2.accept_state;
            f1_start_state->next1 = f2_start_state;
            fm = make_nfa_fragment(f1_start_state, f2_accept_state);
            push_nfa_fragment(&fragmentStack, fm);
            break;
        case '*':
            f1 = pop_nfa_fragment(&fragmentStack);
            f1_start_state = f1.start_state;
            f1_accept_state = f1.accept_state;
            f1_accept_state->accept_flag = 0;
            new_start_state = create_nfa_state();
            new_start_state->transform = '$';
            new_accept_state = create_nfa_state();
            new_accept_state->accept_flag = 1;
            new_start_state->next1 = f1_start_state;
            new_start_state->next2 = new_accept_state;
            f1_accept_state->next1 = f1_start_state;
            f1_accept_state->next2 = new_accept_state;
            fm = make_nfa_fragment(new_start_state, new_accept_state);
            push_nfa_fragment(&fragmentStack, fm);
            break;
        case '?':
            f1 = pop_nfa_fragment(&fragmentStack);
            f1_start_state = f1.start_state;
            f1_accept_state = f1.accept_state;
            f1_accept_state->accept_flag = 0;
            new_start_state = create_nfa_state();
            new_start_state->transform = '$';
            new_accept_state = create_nfa_state();
            new_accept_state->accept_flag = 1;
            new_start_state->next1 = f1_start_state;
            new_start_state->next2 = new_accept_state;
            f1_accept_state->next2 = new_accept_state;
            fm = make_nfa_fragment(new_start_state, new_accept_state);
            push_nfa_fragment(&fragmentStack, fm);
            break;
        case '+':
            f1 = pop_nfa_fragment(&fragmentStack);
            f1_start_state = f1.start_state;
            f1_accept_state = f1.accept_state;
            f1_accept_state->accept_flag = 0;
            f1_accept_state->transform='$';
            new_accept_state = create_nfa_state();
            new_accept_state->transform = '$';
            new_accept_state->accept_flag = 1;
            f1_accept_state->next1 = new_accept_state;
            new_accept_state->next1 = f1_start_state;
            fm = make_nfa_fragment(f1_start_state, new_accept_state);
            push_nfa_fragment(&fragmentStack, fm);
            break;
        default:
            new_start_state = create_nfa_state();
            new_accept_state = create_nfa_state();
            new_accept_state->transform = ch;
            new_accept_state->next1 = new_accept_state;
            new_accept_state->accept_flag = 1;
            fm = make_nfa_fragment(new_start_state, new_accept_state);
            push_nfa_fragment(&fragmentStack, fm);
            break;
        }
    }

    return f.start_state;
}