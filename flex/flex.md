# Part 1: Lexing with Flex

We will cover a minimal introduction to the use of flex in this lab. [This pdf](./resources/LexAndYaccTutorial.pdf) will provide some more detail, and you will likely want to refer to it throughout the lab to fill in the gaps, and particularly to explore the capabilities of flex's regular expressions.

If you are not familiar with regular expressions, or it's been a while and you're rusty, you may want to watch [this video](https://www.youtube.com/watch?v=sa-TUpSx1JA) first.

Consider this grammar:

```
<program> ::= <statement> | <statement> <program>
<statement> ::= <assignStmt> | <ifStmt> | <whileStmt> | <repeatStmt> | <printStmt>

<assignStmt> ::= <ident> = <expr> ;
<ifStmt> ::= if ( <expr> ) <statement>
<whileStmt> ::= while ( <expr> ) <statement>
<repeatStmt> ::= repeat ( <expr> ) <statement>
<printStmt> ::= print <expr> ;

<expr> ::= <term> | <term> <addop> <expr>
<term> ::= <factor> | <factor> <multop> <term>
<factor> ::= <ident> | <number> | <addop> <factor> | ( <expr> )

<number> ::= <int> | <float>
<int> ::= <digit> | <int> <digit>
<float> ::= <digit>. | <digit> <float> | <float> <digit>

<ident> ::= <letter> | <ident> <letter> | <ident> <digit>

<addop> ::= + | -
<multop> ::= * | / | %

<digit> ::= 0-9
<letter> ::= a-z | A-Z | _ | $
```

Enumerate all of the token types in this grammar in the `TOKEN` enum in `flex.h`. In `flex.c`, fill out the `tokenTypeStrings` array in the same order as the `TOKEN` enum. This way, the elements of the `TOKEN` enum can be used to index the `tokenTypeStrings` array and get the corresponding string for printing purposes. This works because enum elements are really just named integers, starting at `0` by default and progressing upward in the order they appear in the enum.

Once you've enumerated all of the `TOKEN` types, you're ready to begin working on the `flex.l`. This file is essentially a configuration file, which flex will use to generate a scanner.

`flex.l` is divided into 3 sections. These sections are separated by lines containing `%%`.

The first section is for **definitions**, the second for **rules**, and the third for **subroutines**. Your task is to complete the first and second sections (the third section will be left empty).

## The Definitions Section

The first section can, in theory, be left empty for what we are doing today, but it should not be. In this section, you can define shortcuts for regular expressions.

Consider these lines in `flex.l`:

```
letter          [a-z]
digit           [0-9]
```

The two lines above define `letter` to be a shorthand for the regular expression `[a-z]` and `digit` one for `[0-9]`.

Next, consider these lines:

```
float           {digit}+\.{digit}*
ident           {letter}+
```

The two lines above define `float` to be one or more digits, followed by a period and then 0 or more digits, and define `ident` to be 1 or more letters.

Note that when the `digit` and `letter` definitions were used in the `float` and `ident` definitions, they were encased in curly braces `{}`; this is how definitions are referenced. The `letter` and`ident` definitions do not match the grammar, and will therefore need to be rewritten. Moreover, regular expressions cannot be recursively defined in `flex` (or in any regular expression implementation that I've seen), so you will have to solve the `ident` production's recurrence to determine what sorts of strings an `ident` can be made out of.

## The Rules Section

The second section (after the first `%%`) is for tokenization rules. Each line consists of a regular expression (or a definition from the first section) followed by a block (written in C) specifying what action is to be taken when a string is encountered which matches said regular expression. The goal in each block is to return the correct token type (and do anything else that needs doing, but for this lab we will just be returning token types).

`flex.h` has been included at the top of the definitions section, so the blocks of C code in the rules section can reference anything accessible to `flex.h`. This is necessary; the token types being returned are defined in `flex.h`.

Consider these lines provided in the rules section:

```
if          {return IF_TOKEN;}
{float}     {return FLOAT_TOKEN;}
{ident}     {return IDENT_TOKEN;}
```

These lines mean, respectively:

* When the string "if" is encountered, return an `IF_TOKEN`.
* When a string matching the `float` definition is encountered, return a `FLOAT_TOKEN`.
* When a string matching the `ident` definition is encountered, return an `IDENT_TOKEN`.

Some of the strings which need to be tokenized (such as parenthesis) have meta-meaning in regular expressions, and therefore will need to either be escaped or put in quotes in order to function as literal characters in a regular expression. For instance:

```
This does not work:
(			{return LPAREN_TOKEN;}
```

```
Either of these work:
\(			{return LPAREN_TOKEN;}
"("			{return LPAREN_TOKEN;}
```

The order in which tokenization rules appear matters. For example, any keyword (print, repeat, etc) will also match the regular expression for an identifier. As such, all of the keyword tokenizations must happen *before* the identifier tokenization, so keywords match their patterns and return the correct token type before they are ever compared to the `ident` definition.

Three more rules have been provided at the bottom of the rules section (and they should be the last three in the rules section when you are done):

```
<<EOF>>     {return EOF_TOKEN;}
[ \n\r\t]   ; //skip whitespace
.           {printf("ERROR: invalid character: >>%s<<\n", yytext);}
```

These rules are to tokenize the end of file, skip whitespace, and catch any invalid characters, respectively.

## The Subroutines Section

We'll talk about this section briefly in a future lab, but for now we're just going to leave it blank. Feel free to read up on it in the provided PDF!

## Output

When you have completed the `TOKEN` enum in `flex.h`, the `tokenTypeStrings` array in `flex.c`, and definitions and rules sections in `flex.l`, you are ready to test!

There is a provided sample input, `input.txt`, with the following contents:

```
while (0.4) abc_1_2 = agd + 1;
if (condition) print ("hello") ;
```

For this sample input, the output should be:

```
{<while> "while"}
{<lparen> "("}
{<float> "0.4"}
{<rparen> ")"}
{<ident> "abc_1_2"}
{<assign> "="}
{<ident> "agd"}
{<addop> "+"}
{<int> "1"}
{<semicolon> ";"}
{<if> "if"}
{<lparen> "("}
{<ident> "condition"}
{<rparen> ")"}
{<print> "print"}
{<lparen> "("}
ERROR: invalid character: >>"<<
{<ident> "hello"}
ERROR: invalid character: >>"<<
{<rparen> ")"}
{<semicolon> ";"}
{<eof> ""}
Process finished with exit code 0
```

You do not need to edit the main to match this output; the only change you need to make to `flex.c` is to fill out the `tokenTypeStrings` array.

Each token is printed with both its type and the string value that was tokenized. In some cases this is redundant, and that's fine; we will work on more complex tokenization rules which process the string value or simply ignore it in a later lab.

When you run, a lexer called `lexer.c` is generated in the `src/lexer` directory; your `flex.l` file served as a configuration file specifying how this lexer should function.

## Submission Checklist

Your submission should:

* Complete the `TOKEN` enum in `flex.h`.
* Complete the `tokenTypeStrings` array in `flex.c` such that the token types are named in the same order they are declared in the `TOKEN` enum.
* Improve `input.txt` to rigorously test your scanner for the provided grammar (it is completely inadequate as provided; it doesn't even test every token type, let alone stress-test for spacing issues and invalid inputs).
* Include a screenshot of a sample run with your improved `input.txt`.
