#include <stdio.h>
#include <stdlib.h>

#include "RegexpToNFA.h"
#include "RegexpToPost.h"
#include "NFAFragmentStack.h"

NFAFragmentStack fragmentStack; // 栈，用于存储NFA片段

// char* regexp = "ab";
char* regexp = "(a|b)*a(a|b)?";

int main(int argc, char** argv)
{
    printf("Hello, World!");

    char* post;
    NFAState* start;

    // 初始化栈
    InitNFAFragmentStack(&fragmentStack);
    // 将正则表达式转换为解析树的后序遍历序列
    post = re2post(regexp);
    printf("%s\n", post);
    // 将解析树的后序遍历转换为 NFA, 并返回开始状态
    start = post2nfa(post);

    return 0;
}


// 初始化一个状态
int nstate = 1; // 状态名计数器
NFAState* CreateNFAState() {
    NFAState* s = (NFAState*)malloc(sizeof(NFAState));

    s->name = nstate++;
    s->transform = '\0';
    s->next1 = NULL;
    s->next2 = NULL;
    s->accept_flag = 0;

    return s;
}

// 将开始状态和接收状态组成一个Fragment
NFAFragment MakeNFAFragment(NFAState* start_state, NFAState* accept_state)
{
    NFAFragment n = {start_state, accept_state};
    return n;
}

// 将解析树的后序遍历序列转换为NFA
const char VoidTrans = '$ '; // 表示空转换
NFAState* post2nfa(char* postfix)
{
    char* p; //
    NFAFragment fragment1, fragment2, fm; // NFA片段结构体变量
    NFAFragment fragment = {0, 0}; //  初始化用于返回的NFA片段
    NFAState *new_start_state, *new_accept_state; // 开始状态和接收状态指针

    //todo： Conversion
    for(p = postfix; *p != NULL; p++)
    {
        switch (*p)
        {
        case '.': // 连接
            // 栈顶两个片段出栈，构造新的 NFA片段
            fragment2 = PopNFAFragment(&fragmentStack);
            fragment1 = PopNFAFragment(&fragmentStack);
            fragment1.accept_state = fragment2.start_state;
            fm = MakeNFAFragment(fragment1.start_state, fragment2.accept_state);
            PushNFAFragment(&fragmentStack, fm);
            break;
        case '|': // 选择 /* alternate */
            fragment2 = PopNFAFragment(&fragmentStack);
            fragment1 = PopNFAFragment(&fragmentStack);
            new_start_state = CreateNFAState();
            new_start_state->transform = VoidTrans;
            new_start_state->next1 = fragment1.start_state;
            new_start_state->next2 = fragment2.start_state;
            new_accept_state = CreateNFAState();
            new_accept_state->transform = VoidTrans;
            new_accept_state->accept_flag = 1;
            fragment1.accept_state = new_accept_state;
            fragment2.accept_state = new_accept_state;
            fm = MakeNFAFragment(new_start_state, new_accept_state);
            PushNFAFragment(&fragmentStack, fm);
            break;
        case '*': /* zero or more */
            fragment1 = PopNFAFragment(&fragmentStack);
            new_start_state = CreateNFAState();
            new_accept_state = CreateNFAState();
            new_start_state->transform = VoidTrans;
            new_start_state->next1 = fragment1.start_state;
            new_start_state->next2 = new_accept_state;
            fragment1.accept_state->next1 = new_accept_state;
            fragment1.accept_state->next2 = fragment1.start_state;
            new_accept_state->accept_flag = 1;
            fm = MakeNFAFragment(new_start_state, new_accept_state);
            PushNFAFragment(&fragmentStack, fm);
            break;
        case '+': /* one or more */
            fragment1 = PopNFAFragment(&fragmentStack);
            new_accept_state = CreateNFAState();
            fragment1.accept_state->next1 = new_accept_state;
            new_accept_state->accept_flag = 1;
            new_accept_state->next1 = fragment1.start_state;
            fm = MakeNFAFragment(fragment1.start_state, new_accept_state);
            PushNFAFragment(&fragmentStack, fm);
            break;
        case '?': /* zero or one */
            fragment1 = PopNFAFragment(&fragmentStack);
            new_start_state = CreateNFAState();
            new_accept_state = CreateNFAState();
            new_start_state->transform=VoidTrans;
            new_start_state->next1 = fragment1.start_state;
            new_start_state->next2 = new_accept_state;
            new_accept_state->accept_flag = 1;
            fragment1.accept_state->next1 = new_accept_state;
            fm = MakeNFAFragment(new_start_state, new_accept_state);
            PushNFAFragment(&fragmentStack, fm);
            break;
        default: // 构造单字符 NFAFragment
            // 调用 CreateState 函数生成两个新的状态
            new_start_state = CreateNFAState();
            new_accept_state = CreateNFAState();
            // 开始状态 通过单字符 转换到接收状态
            new_start_state->transform = *p;
            new_start_state->next1 = new_accept_state;
            new_accept_state->accept_flag = 1;
            // 调用 MakeFragment 生成一个新的 NFA 片段并入栈
            fm = MakeNFAFragment(new_start_state, new_accept_state);
            PushNFAFragment(&fragmentStack, fm);
            break;
        }
    }
    return fragment.start_state;
}
