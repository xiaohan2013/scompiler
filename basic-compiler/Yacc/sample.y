%{
#include <stdio.h>
#include <ctype.h>

#define YYDEBUG 1
%}

%%
comamnd: A
    ;
A: 'a'
    | '('A')'
    ;

%%

main()
{
    extern int yydebug;
    yydebug = 0;
    return yyparse();
}

int yylex(void)
{
    int c;
    while((c = getchar()) == ' ');
    if(c == '\n') return 0;

    return c;
}

int yyerror(char *s)
{
    fprintf(stdout, "%s\n", s);
    return 0;
}