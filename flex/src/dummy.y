%{
    int yylex();
    void yyerror(char*);
%}

%token EOF

%%

program: EOF
