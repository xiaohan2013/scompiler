#ifndef __NFATODFA_H__
#define __NFATODFA_H__

#include <stdio.h>
// 包含其他头文件

// 定义数据结构
#define MAX_STATE_NUM 64

typedef struct _NFAState
{
    /* data */
    char transform;
    struct _NFAState *next1;
    struct _NFAState *next2;
    int name;
    int accept_flag; 
}NFAState;

typedef struct _NFAFragment
{
    /* data */
    NFAState *start_state;
    NFAState *accept_state;
}NFAFragment;

// 转换
typedef struct _Transform
{
    /* data */
    char transform_char;
    int dfa_state_index;
    NFAState *nfa_list[MAX_STATE_NUM];
    int nfa_state_count;
    struct _Transform *next_transform;
}Transform;

typedef struct _DFAState
{
    /* data */
    NFAState *nfa_list[MAX_STATE_NUM]; // NFA状态集合
    int nfa_state_count; // 状态集合计数
    Transform *first_transform;  // 指向第一个转换
}DFAState;

// DFA
typedef struct DFA {
    DFAState *dfa_list[MAX_STATE_NUM];
    int length; //状态集合计数
}DFA;

// 处理函数
// 
void epsilon_closure(NFAState *state, NFAState **state_array, int *count);
DFAState* create_dfa_state(Transform *pTransform);
Transform* create_dfa_transform(char transform_char, NFAState **nfa_state_array, int count);
Transform* is_transform_exist(DFAState* dfa_state, char transform_char);
void add_nfa_state_array_to_transform(NFAState **nfa_state_array, int count, Transform *transform_ptr);
DFA* post2dfa(DFA *dfs_ptr, char *postfix);

// 全局变量
extern const char VoidTrans;
extern NFAState *start;

#endif // __NFATODFA_H__
