#ifndef __POSTTONFA_H__
#define __POSTTONFA_H__

#include "NFAToDFA.h"

NFAState* create_nfa_state();
NFAFragment make_nfa_fragment(NFAState *start_state, NFAState *accept_state);
NFAState* post_to_nfa(char* postfix);

#endif /* __POSTTONFA_H__ */
