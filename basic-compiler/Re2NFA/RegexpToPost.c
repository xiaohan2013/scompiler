#include <stdio.h>
#include <string.h>


#include "RegexpToPost.h"

// 将正则表达式字符串解析为后序遍历序列
char* re2post(char* re)
{
    int nalt; // 表示解析到这个字符为止，已经有多少个分支结构
    int natom; // 表示解析到这个字符为止，已经有多少个原子结构
    static char buf[8000]; 
    char* dst;

    struct {
        int nalt;
        int natom;
    }paren[100], *p;

    p = paren;
    dst = buf;
    nalt = 0;
    natom = 0;
    
    if(strlen(re) >= sizeof(buf) / 2)
    {
        return NULL;
    }

    for(;*re;re++) {
        switch (*re)
        {
        case '(':
            /* code */
            if(natom > 1)
            {
                --natom;
                *dst++='.';
            }
            if(p >= paren+100)
                return NULL;

            p->nalt = nalt;
            p->natom = natom;
            p++;
            nalt = 0;
            natom = 0;
            break;
        case '|':
            if(natom == 0)
            {
                return NULL;
            }

            while (--natom >0)
            {
                /* code */
                *dst++='.';
            }
            nalt++;
            break;
        case ')':
            if(p == paren)
                return NULL;
            if(natom ==0)
                return NULL;
            while (--natom)
            {
                /* code */
                *dst ++='.';
            }
            for(;nalt > 0; nalt--)
            {
                *dst++='|';
            }
            --p;
            nalt = p->nalt;
            natom = p->natom;
            natom++;
            break;
        case '*':
        case '+':
        case '?':
            if(natom == 0)
                return NULL;
            
            *dst ++= *re;
            break;
        default:
            if(natom > 1)
            {
                --natom;
                *dst++='.';
            }
            *dst ++=*re;
            natom++;
            break;
        }
    }

    if(p != paren)
        return NULL;
    
    while (--natom > 0)
    {
        /* code */
        *dst++='.';
    }
    
    for(; nalt > 0; nalt--)
    {
        *dst++='|';
    }
    *dst = 0;

    return buf;
}