#include "calc.h"

#define RED             "\033[31m"
#define RESET_COLOR     "\033[0m"

/*
 * This function takes as input a string (a function's name) and outputs the index
 * of that string in the array below. Not that the string below has all elements in
 * the same order as the FUNC_TYPE enum in calc.h, so the returned index will be the
 * member of FUNC_TYPE represented by the input string.
 *
 * For instance, if "abs" is passed in, the the ABS member of the FUNC_TYPE
 * enum will be returned (or, at least, its integer equivalent will be returned)
 */
FUNC_TYPE resolveFunc(char *func) {

    char *funcs[] = {
            "neg",          // returns negative of input
            "abs",          // returns absolute value of input
            "exp",          // returns e raised to power of input (man exp)
            "log",          // finds natural log (man math, find the right log function)
            "sqrt",         // returns square root of input
            "add",          // returns the sum of the two inputs
            "sub",          // returns the difference of the two inputs
            "mult",         // returns the product of the two inputs
            "div",          // returns the quotient of the two inputs
            "rem",          // finds the remainder of the first divided by the second (modulus); use fmod for floats
            ""              // unrecognized function name, kaboom (error).
    };

    int i = 0;
    while (funcs[i][0] != '\0') {
        if (!strcmp(funcs[i], func))
            return (FUNC_TYPE) i;
        i++;
    }
    /* It should be impossible to reach the yyerror and return below.
    * This is because only strings which are tokenized as functions
    * will be passed in here, so as long as the regex for our function
    * recognition is good, we will NEVER pass in a value that is
    * not in the array above.
    */
    yyerror("Invalid function \"%s\"", func); // paranoic -- should never happen
    return -1;
}

NUMBER *evalNeg(NUMBER *op)
{
    NUMBER *result = malloc(sizeof(NUMBER));
    result->value = -op->value;
    result->type = op->type;
    return result;
}

NUMBER *evalAbs(NUMBER *op)
{
    // TODO
    return NULL;
}

NUMBER *evalExp(NUMBER *op)
{
    // TODO
    return NULL;
}

NUMBER *evalLog(NUMBER *op)
{
    // TODO
    return NULL;
}

NUMBER *evalSqrt(NUMBER *op)
{
    // TODO
    return NULL;
}

NUMBER *evalAdd(NUMBER *op1, NUMBER *op2)
{
    if (op2 == NULL)
    {
        yyerror("Too few arguments in addition.");
    }
    NUMBER *result = malloc(sizeof(NUMBER));
    result->type = op1->type || op2->type;
    result->value = op1->value + op2->value;
    if (!result->type)
    {
        result->value = round(result->value);
    }
    return result;
}

NUMBER *evalSub(NUMBER *op1, NUMBER *op2)
{
    // TODO
    return NULL;
}

NUMBER *evalMult(NUMBER *op1, NUMBER *op2)
{
    // TODO
    return NULL;
}

NUMBER *evalDiv(NUMBER *op1, NUMBER *op2)
{
    // TODO
    return NULL;
}

NUMBER *evalRem(NUMBER *op1, NUMBER *op2)
{
    // TODO
    return NULL;
}

/*
 * The function to calculate simple math operation.
 *
 * The values of op1 and op2 may be omitted for functions that take one or no parameters.
 */
NUMBER *calc(FUNC_TYPE func, NUMBER *op1, NUMBER *op2)
{
    switch ( func )
    {
        case NEG:
            return evalNeg(op1);
        case ABS:
            return evalAbs(op1);
        case EXP:
            return evalExp(op1);
        case LOG:
            return evalLog(op1);
        case SQRT:
            return evalSqrt(op1);
        case ADD:
            return evalAdd(op1, op2);
        case SUB:
            return evalSub(op1, op2);
        case MULT:
            return evalMult(op1, op2);
        case DIV:
            return evalDiv(op1, op2);
        case REM:
            return evalRem(op1, op2);
        case OTHER:
            yyerror("Invalid function \"%s\".", func);
    }
    // these 5 lines cannot be reached and are only here to get rid of warnings...
    yyerror("Impossible state reached in calc function...");
    NUMBER *result = malloc(sizeof(NUMBER));
    *result = NAN_NUMBER;
    return result;
}

NUMBER *createNumber(NUM_TYPE type, double value)
{
    NUMBER *number = malloc(sizeof(NUMBER));
    number->value = value;
    number->type = type;
    return number;
}

void printNumber(FILE *dest, NUMBER *number)
{
    if (number == NULL)
    {
        return;
    }
    switch (number->type)
    {
        case INT_TYPE:
            fprintf(dest, "INT : %.0lf\n", number->value);
            break;
        case FLOAT_TYPE:
            fprintf(dest, "FLOAT : %lf\n", number->value);
            break;
    }
    fflush(dest);
}

void yyerror(char *errorFormat, ...) {
    char buffer[256];
    va_list args;
    va_start (args, errorFormat);
    vsnprintf (buffer, 255, errorFormat, args);

    printf( RED "\nERROR: %s\nExiting...\n" RESET_COLOR, buffer);
    fflush(stdout);

    va_end (args);
    exit(1);
}
