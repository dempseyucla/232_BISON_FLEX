%{
    #include "calc.h"
    #define ylog(r, p) {fprintf(flex_bison_log_file, "BISON: %s ::= %s \n", #r, #p); fflush(flex_bison_log_file);}
%}

%union
{
    double dval;
    struct number *nval;
}

%token <dval> INT FLOAT
%token EOL

%type <nval> number

%%

program:
    expr EOL {
        ylog(program, expr EOL);
        printNumber(stdout, $1);
        YYACCEPT;
    }
    | QUIT {
        ylog(program, QUIT);
        exit(0);
    };

expr:
    number {
        ylog(expr, number);
        $$ = $1;
    }
    | f_expr {
        ylog(expr, f_expr);
        $$ = $1;
    };

%%

