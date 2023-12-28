#include <stdio.h>
#include <stdlib.h>

#include "RegexpToPost.h"


// 将输入的正则表达式字符串转换为解析树的后缀遍历序列: infix2postfix conversion
// https://eecs.wsu.edu/~nroy/courses/cpts122/labs/Infix2Postfix.pdf
// https://swtch.com/~rsc/regexp/regexp1.html
// 1. scan the input string(infix notation) from left to right. One pass is sufficient.
// 2. 
// () | ? * + 
// Rules: 
//    1. If the input symbol is a letter, append it directly to the output queue
//    2. If the input symbol is an operator, if there exists an operator already on the top of the operator stack with higher or equal precedence than
//       our current input symbol, remove the operator from the top of the operator stack and append to  the output queue. Do this until the curent
//       input symbol has a higher precedence than the symbol on the top of the operator stack, or the operator stack is empty.
//    3. If the input symbol is an operator AND there is a left parenthesis on the top the stack, push the input symbol onto he stack on the of the left parenthesis.
//    4. If the input symbol is an (, append it to the operator stack.
//    5. If the input symbol is an ), pop all opeartors from the operator stack and append them to the output queue until you find an (. Then
//       you can remove both of those parenthesises and continue with the algorithm.
// Precedence from highest to lowest
// 1. Closure(Kleen star) a* ? +, left-associative
// 2. Concatenation ab -> a.b
// 3. Union a+b(a|b)
char* re2post(char* re)
{
    char *ptr_re = re;
    // 这是动态分配内存，需要用指针来指向。适合用链表数据结构。
    // 对于动态内存分配的情况需是在 struct 的情况下使用；
    // char *postfix = (char*)malloc(sizeof(char));
    // char *op_stack = (char*)malloc(sizeof(char));
    static char postfix[20];
    char *res_postfix = postfix;
    char op_stack[10];
    char *stack_top_ptr = op_stack;
    *stack_top_ptr = '#'; // 栈底
    char *ptr_postfix = postfix;
    while (*ptr_re != '\0')
    {
        char ch = *ptr_re++;
        printf("re character: %c\n", ch);
        switch (ch)
        {
        case '(': // 左括号前需要加 连接符
            // if(*stack_top_ptr != '#')
            // {
            //     *stack_top_ptr = '.';
            // }
            // ++stack_top_ptr; // 向上移一个位置给
            stack_top_ptr++;
            *stack_top_ptr = ch;
            printf("Input symbol: %c, op_stack=%s, stack_top=%c, res_postfix=%s \n", ch, op_stack, *stack_top_ptr, res_postfix);
            break;
        case ')':
            // 没有左括号，非法字符串
            if(*stack_top_ptr == '#')
                return NULL;
            while(*stack_top_ptr != '(')
            {
                *ptr_postfix = *stack_top_ptr;
                *stack_top_ptr = '\0';
                --stack_top_ptr;
                ++ptr_postfix;
                *ptr_postfix = '\0';
            }
            // 移除左括号
            *stack_top_ptr = '\0';
            --stack_top_ptr;
            printf("Input symbol: %c, op_stack=%s, res_postfix=%s \n", ch, op_stack, res_postfix);
            break;
        case '|':
            // 优先级最低，先入栈
            ++stack_top_ptr;
            *stack_top_ptr = ch;
            printf("Input symbol: %c, op_stack=%s, stack_top=%c, res_postfix=%s \n", ch, op_stack, *stack_top_ptr, res_postfix);
            break;
        case '*':
        case '+':
        case '?':
            // 优先级最高，但是在 left-parenthesis 在栈顶时还是继续入栈
            if(*stack_top_ptr == '(')
            {
                ++stack_top_ptr;
                *stack_top_ptr = ch;
            }

            // while(*stack_top_ptr != '#')
            // {
            //     *ptr_postfix = *stack_top_ptr;
            //     *stack_top_ptr = '\0';
            //     --stack_top_ptr;
            //     ++ptr_postfix;
            //     *ptr_postfix = '\0';
            // }
            *ptr_postfix = ch;
            ptr_postfix++;
            *ptr_postfix = '\0';
            printf("Input symbol: %c, op_stack=%s, stack_top=%c, res_postfix=%s \n", ch, op_stack, *stack_top_ptr, res_postfix);
            break;
        default: // letter
            *ptr_postfix = ch;
            ptr_postfix++;
            *ptr_postfix = '\0';
            printf("Input symbol: %c, op_stack=%s, stack_top=%c, res_postfix=%s \n", ch, op_stack, *stack_top_ptr, res_postfix);
            break;
        }
    }
    // 出栈
    while(*stack_top_ptr != '#')
    {
        *ptr_postfix = *stack_top_ptr;
        *stack_top_ptr = '\0';
        --stack_top_ptr;
        ++ptr_postfix;
        *ptr_postfix = '\0';
    }
    printf("op_stack=%s, stack_top=%c, res_postfix=%s \n", op_stack, *stack_top_ptr, res_postfix);

    return &postfix;
}

// char* regexp = "a(a|1)*";
// char* regexp = "(a|b)*abb(a|b)*";

// int __main(int argc, char** argv)
// {
//     char *post;
//     post = re2post(regexp);
//     printf("regular expression: %s;\n postfix sequences: %s \n", regexp, post);

//     return 0;
// }