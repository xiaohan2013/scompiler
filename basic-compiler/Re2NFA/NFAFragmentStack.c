#include "NFAFragmentStack.h"

// 初始化栈
void InitNFAFragmentStack(NFAFragmentStack *ps) 
{
    ps->top = -1;
}

// 元素入栈
void PushNFAFragment(NFAFragmentStack *ps, NFAFragment elem)
{
    if(MAX_STACK_LENGTH - 1 <= ps->top)
        return;
    
    ps->top++;
    ps->buffer[ps->top] = elem;

    return;
}

// 元素出栈
NFAFragment PopNFAFragment(NFAFragmentStack *ps) 
{
    int pos;
    NFAFragment fragment = {0, 0};

    if(NFAFragmentStackEmpty(ps))
        return fragment;

    pos =  ps->top;
    ps->top--;

    return ps->buffer[pos];
}

// 判断栈是否为空
int NFAFragmentStackEmpty(NFAFragmentStack *ps)
{
    return -1 == ps->top ? 1 : 0;
}