#ifndef __DEFINE_H__
#define __DEFINE_H__

typedef enum 
{
    // 文件结束
    ENDFILE,
    // 错误
    ERROR,

    // 关键字
    IF,
    THEN,
    ELSE,
    END,
    REPEAT,
    UNTIL,
    READ,
    WRITE,
    // 标识符
    ID,
    // 无符号整数
    NUM,

    // 特殊符号
    ASSIGN,
    EQ,
    LT,
    PLUS,
    MINUS,
    TIMES,
    OVER,
    LPAREN,
    RPAREN,
    SEMI,

    // 注释
    COMMENT
}TokenType;

#endif /* __DEFINE_H__ */
