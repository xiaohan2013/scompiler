#pragma once

#ifndef _NFAFRAGMENTSTACK_H_
#define _NFAFRAGMENTSTACK_H_

// 定义头文件
#include "RegexpToNFA.h"

// 定义数据结构
#define MAX_STACK_LENGTH 1024 // 栈的最大长度

// 栈
typedef struct _NFAFragmentStack {
    NFAFragment buffer[MAX_STACK_LENGTH]; // 栈缓冲区
    int top; // 栈顶位置指针，而不是栈中元素的个数
}NFAFragmentStack;

// 声明函数
void InitNFAFragmentStack(NFAFragmentStack *ps);
void PushNFAFragment(NFAFragmentStack *ps, NFAFragment elem);
NFAFragment PopNFAFragment(NFAFragmentStack *ps);
int NFAFragmentStackEmpty(NFAFragmentStack *ps);

// 声明全局变量

#endif _NFAFRAGMENTSTACK_H_