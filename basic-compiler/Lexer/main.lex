%option noyywrap
%{
#include <stdio.h>
#include "define.h"

int lineno = 0;

// 符号计数器
int error_no = 0;

int if_no = 0;
int then_no = 0;
int else_no = 0;
int end_no = 0;
int repeat_no = 0;
int until_no = 0;
int read_no = 0;
int write_no = 0;

int id_no = 0;
int num_no = 0;

int assign_no = 0;
int eq_no = 0;
int lt_no = 0;
int plus_no = 0;
int minus_no = 0;
int times_no = 0;
int over_no = 0;
int lparen_no = 0;
int rparen_no = 0;
int semi_no = 0;

int comment_no = 0;
%}

/* Definitions Section */
%x STATE_X
newline  \n
whitespace [\t]+

%%
        /* Rules Section */
ruleA   /* after regex */ { /* code block */ } /* after code block */
        /* Rules Section (indented) */
<STATE_X>{
        ruleC   ECHO;
        ruleD   ECHO;
        %{
        /* code block */
        %}
    }
":=" {return ASSIGN;}
"=" {return EQ;}
"<" {return LT;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return TIMES;}
"/" {return OVER;}
"(" {return LPAREN;}
")" {return RPAREN;}
";" {return SEMI;}

{newline} {lineno++;}
{whitespace} {/*忽略空白*/}

"{" {
        // 匹配注释
        char c;
        int comment = 1;
        do {
            c = input();
            if(c == EOF){
                comment=0;
                break;
            }
            else if (c == '\n') {
                lineno++;
            } else if (c == '}') {
                break;
            }
        } while(1);
        return comment ? COMMENT : ERROR;
    }
.   {return ERROR;}

%%
/* User Code Section */
TokenType id2keyword(const char *token);
void stat(TokenType tt, const char *token);
void output();

int main(int argc, char *argv[])
{
    TokenType tt;

    if(argc < 2)
    {
        printf("Usage : scan.exe filename. \n");
        return 1;
    }

    // 打开待处理的文件
    FILE *file = fopen(argv[1], "rt");
    if(NULL == file)
    {
        printf("Can not open file \"%s\".\n", argv[1]);
        return 1;
    }

    //将打开的文件作为lex扫描程序的程序输入
    yyin = file;

    while((tt = yylex()) != ENDFILE)
    {
        // 根据符号类型统计数量
        stat(tt, yytext);
    }

    // 输出统计量
    output();
    //关闭文件
    fclose(file);

    return 0;
}

typedef struct _KeyWord_Entry
{
    const char *word;
    TokenType type;
}KeyWord_Entry;

static const KeyWord_Entry key_table[] = {
    {"if", IF},
    {"then", THEN},
    {"else", ELSE},
    {"end", END},
    {"repeat", REPEAT},
    {"until", UNTIL},
    {"read", READ},
    {"write", WRITE}
};

// 将标识符转化为对应关键字类型
TokenType id2keyword(const char *id)
{
    //

    return ID;
}

void stat(TokenType tt, const char *token)
{
    if(ID == tt)
    {
        tt = id2keyword(token);
    }

    switch(tt)
    {
    case IF:
        if_no++;
        break;
    case THEN:
        then_no++;
        break;
    case ELSE:
        else_no++;
        break;
    case END:
        end_no++;
        break;
    case REPEAT:
        repeat_no++;
        break;
    case UNTIL:
        until_no++;
        break;
    case READ:
        read_no++;
        break;
    case WRITE:
        write_no++;
        break;
    case ID:
        id_no++;
        break;
    case NUM:
        num_no++;
        break;
    case ASSIGN:
        assign_no++;
        break;
    case EQ:
        eq_no++;
        break;
    case LT:
        lt_no++;
        break;
    case PLUS:
        plus_no++;
        break;
    case MINUS:
        minus_no++;
        break;
    case TIMES:
        times_no++;
        break;
    case OVER:
        over_no++;
        break;
    case LPAREN:
        lparen_no++;
        break;
    case RPAREN:
        rparen_no++;
        break;
    case SEMI:
        semi_no++;
        break;
    case COMMENT:
        comment_no++;
        break;
    case ERROR:
        error_no++;
        break;
    }
}

void output()
{
    printf("if: %d \n", if_no);
    printf("then: %d \n", then_no);
    printf("else: %d \n", else_no);
    printf("end: %d \n", end_no);
    printf("repeat: %d \n", repeat_no);
    printf("until: %d \n", until_no);
    printf("read: %d \n", read_no);
    printf("write: %d \n", write_no);

    printf("id: %d \n", id_no);
    printf("num: %d \n", num_no);

    printf("assign: %d \n", assign_no);
    printf("eq: %d \n", eq_no);
    printf("lt: %d \n", lt_no);
    printf("plus: %d \n", plus_no);
    printf("minus: %d \n", minus_no);
    printf("times: %d \n",times_no);
    printf("over: %d \n", over_no);
    printf("lparen: %d \n", lparen_no);
    printf("rparen: %d \n", rparen_no);
    printf("semi: %d \n", semi_no);

    printf("comment: %d \n", comment_no);
    printf("error: %d \n", error_no);
    printf("line: %d \n", lineno);
}