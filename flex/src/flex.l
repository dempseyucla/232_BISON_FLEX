/* NOTE: % must be in the first column (no indentation) */
/* TODO add more regular expressions and returns for the other TOKEN types */


%option noyywrap
%option nounput
%option noinput

%{
   #include "flex.h"
%}

letter          [a-z]
digit           [0-9]

float           {digit}+\.{digit}*
ident           {letter}+

%%

if          {return IF_TOKEN;}
{float}     {return FLOAT_TOKEN;}
{ident}     {return IDENT_TOKEN;}



<<EOF>>     {return EOF_TOKEN;}
[ \n\r\t]   ; //skip whitespace
.           {printf("ERROR: invalid character: >>%s<<\n", yytext);}

%%

