extern char *yytext;

#include "flex.h"

int main(int argc, char **argv)
{

    freopen(argv[1], "r", stdin);

    /*
     * TODO
     * complete the array below to get string labels for TOKEN types
     * based on the TOKEN enumerator.
     * tokenTypeStrings[IF_TOKEN] should be "if"
     * tokenTypeStrings[INT_TOKEN] should be "int", etc
     */
    char *tokenTypeStrings[] = {
            "eof",
            "if",
            "float",
            "ident"
            //etc
    };

    printf("\n");
    TOKEN token;
    do
    {
        token = yylex();
        printf("{<%s> \"%s\"}\n", tokenTypeStrings[token], yytext);
    } while (token != EOF_TOKEN);
}

void yyerror(char *s) {/* dummy */}