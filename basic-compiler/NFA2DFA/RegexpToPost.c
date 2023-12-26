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
// 1. Closure(Kleen star) a*
// 2. Concatenation ab
// 3. Union a+b(a|b)
char* re2post(char* re) 
{
    char *ptr_re = re;
    char *postfix = (char*)malloc(sizeof(char));
    char *op_stack = (char*)malloc(sizeof(char));
    char *stack_top_ptr = op_stack;
    char *ptr_postfix = postfix;
    while (*ptr_re != '\0')
    {
        char c = *ptr_re++;
        printf("re character: %c\n", c);
        switch (c)
        {
        case '(':
            *stack_top_ptr++ = c;
            break;
        case ')':
            
            break;
        case '|':
            *stack_top_ptr++ = c;
            break;
        case '+':
        case '*':
        case '?':
            *ptr_postfix++ = c;
            break;
        default:
            *ptr_postfix++ = c;
            break;
        }
    }
    free(op_stack);
    return postfix;
}