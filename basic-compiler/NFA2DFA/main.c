#include<stdio.h>
#include<stdlib.h>

#include "NFAToDFA.h"
#include "PostToNFA.h"
#include "RegexpToPost.h"


char* regexp = "a(a|1)*";

int main(int argc, char** argv)
{

    char *post;
    post = re2post(regexp);
    printf("regular expression: %s;\n postfix sequences: %s \n", regexp, post);

    

    return 0;
}

// 创建一个DFA的状态转换
Transform* create_dfa_transform(char transofrm_char, NFAState **nfa_state_array, int count)
{
    int i;
    Transform *ptr_transoform = (Transform*)malloc(sizeof(Transform));

    for(i = 0; i < count; i++)
    {
        ptr_transoform->nfa_list[i] = nfa_state_array[i];
    }
    ptr_transoform->nfa_state_count = count;
    ptr_transoform->transform_char = transofrm_char;
    ptr_transoform->dfa_state_index = -1;
    ptr_transoform->next_transform = NULL;

    return ptr_transoform;
}

// 创建一个DFA状态
DFAState* create_dfa_state(Transform *transform)
{
    int i;
    DFAState *ptr_dfs_state = (DFAState*)malloc(sizeof(DFAState));

    for(i = 0; i < transform->nfa_state_count; i++)
    {
        ptr_dfs_state->nfa_list[i] = transform->nfa_list[i];
    }
    ptr_dfs_state->nfa_state_count = transform->nfa_state_count;
    ptr_dfs_state->first_transform = NULL;

    return ptr_dfs_state;
}

// 判断一个转换中的NFA状态集合是否为某一个DAF状态中的NFA状态集合的子集
int nfa_state_is_subset(DFA *ptr_dfa, Transform *transform)
{
    // TODO
    return 0;
}

// 判断某个DFA状态中的转换链表中是否已经存在一个字符转换
Transform* is_transform_exist(DFAState *dfs_state, char tranform_char)
{
    //TODO
    return NULL;
}

// 将一个NFA集合合并 到一个DFA转换中的NFA集合中。合并后的集合中不应该重复NFA状态
void add_nfa_state_array_to_transform(NFAState **nfa_state_array, int count, Transform *transform)
{
    // TODO
    return;
}

// 使用二叉树的先序遍历求一个NFA状态的 epsilon-clousure
void epsilon_closure(NFAState *state, NFAState **state_array, int *count)
{
    // init_nfa_state_stack(&state_stack);

    // TODO
    return;
}

// 将解析树的后序遍历转换为DFA
NFAState *start = NULL;
DFA* post_to_dfa(DFA *ptr_dfa, char *postfix)
{
    int i, j;
    Transform *p;
    NFAState *nfa_state_array[MAX_STATE_NUM];
    int cnt = 0; // epsilon闭包中的元素个数
    
    // post2nfa 将解析树的后序遍历序列转换为 NFA，并返回开始状态
    start = post_to_nfa(postfix);
    // TODO

    return ptr_dfa;
}