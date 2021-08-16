%option noyywrap

%{
    #include "calc.h"
    #define llog(token) {fprintf(flex_bison_log_file, "LEX: %s \"%s\"\n", #token, yytext);fflush(flex_bison_log_file);}
%}

digit       [0-9]
int         [+-]?{digit}+

%%

{int} {
    llog(INT);
    yylval.dval = strtod(yytext, NULL);
    return INT;
}

[\n] {
    llog(EOL);
    return EOL;
}

[\r\t ] {}; /* skip whitespace */

. {
    llog(ERROR INVALID);
}

%%
