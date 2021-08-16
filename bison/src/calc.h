#ifndef __calc_h_
#define __calc_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// The following include file is generated automatically by CMake
// (along the scanner and the parser)
// It will include an enum of all of the token types returned in calc.l
// This is why we haven't made our own enum with the necessary token types.
// It will probably be underlined in red FOREVER if you're on windows.
// But it should let you build and run anyway.
#include "parser.h"

// some macros for common numbers
#define ZERO (NUMBER){INT_TYPE, 0};
#define NAN_NUMBER (NUMBER){FLOAT_TYPE, NAN}

// we'll log what flex and bison do in a file
FILE* flex_bison_log_file;

// declaring the following Bison functions limits compiler warnings
int yyparse(void);
int yylex(void);
void yyerror(char *, ...);

typedef enum func_type
{
    NEG,
    ABS,
    EXP,
    LOG,
    SQRT,
    ADD,
    SUB,
    MULT,
    DIV,
    REM,
    OTHER // stranger danger
} FUNC_TYPE;

typedef enum
{
    INT_TYPE,
    FLOAT_TYPE
} NUM_TYPE;

typedef struct number
{
    NUM_TYPE type;
    double value;
} NUMBER;

NUMBER *createNumber(NUM_TYPE type, double value);
void printNumber(FILE *stream, NUMBER *number);
NUMBER *calc(FUNC_TYPE func, NUMBER *op1, NUMBER *op2);
FUNC_TYPE resolveFunc(char*);

#endif
