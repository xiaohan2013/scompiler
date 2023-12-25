#pragma once

#ifndef _REGEXPTOFNA_H_
#define _REGEXPTOFNA_H_

#include <stdio.h>

// 定义数据结构
typedef struct _NFAState {
    char transform; // 状态间转换的标识，用 $ 表示 “ε-转换”
    struct _NFAState* next1; // 指向下一个状态
    struct _NFAState* next2; // 指向下一个状态
    int name; // 状态名称
    int accept_flag; // 是否为接受状态： 1，表示接受状态，0：表示拒绝状态
} NFAState;

//Fragment 是一个NFA片段
typedef struct _NFAFragment {
    NFAState* start_state;  // 开始状态
    NFAState* accept_state; //接受状态
}NFAFragment;

// 声明函数
NFAState* CreateNFAState();
NFAState* post2nfa(char* postfix);
NFAFragment MakeNFAFragment(
    NFAState* start_state,
    NFAState* accept_state
);

// 声明全局变量
extern int nstate;
extern const char VoidTrans;
extern char* regexp;

#endif _REGEXPTOFNA_H_