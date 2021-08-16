
#include <stdio.h>
#include "calc.h"

#define FLEX_BISON_LOG_PATH "../logs/flex_bison_log"

int main(int argc, char **argv)
{
    int input_from_file = 0;
    flex_bison_log_file = fopen(FLEX_BISON_LOG_PATH, "w");

    if (argc > 1)
    {
        stdin = fopen(argv[1], "r");
        input_from_file = 1;
    }

    while(1) {
        if (!input_from_file)
            printf("> ");
        if (yyparse()) exit(1);
    }
}

