#ifndef __flex_h_
#define __flex_h_

#include <stdio.h>

// TODO complete the TOKEN enum
typedef enum {
    EOF_TOKEN,
    IF_TOKEN,
    FLOAT_TOKEN,
    IDENT_TOKEN
    //etc
} TOKEN;

int yylex(void);
void yyerror(char *s);

#endif
