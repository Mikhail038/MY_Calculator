//=======================================================================================================================================================================================

#include <math.h>
#include <string.h>

#include "calc.h"

//=======================================================================================================================================================================================

const char* Line = NULL;

// typedef struct
// {
//     int             length   = 0;
//     const char*     Name     = NULL;
//     double        (*function) (double) = NULL;
// } SUnFunction;


// const SUnFunction ArrUFunc[] =
// {
//
// };

//const int SzArrUFunc = sizeof (ArrUFunc);

//=======================================================================================================================================================================================
//
//  Main        ::= Add$
//  Add         ::= Mul{[+-]Mul}*
//  Mul         ::= Pow{[*/]Pow}*
//  Pow         ::= Bracket{[^]Bracket}*
//  Bracket     ::= '('Add')' | Number | Function
//  Number      ::= [eE] | [Pp][Ii] | Int{[.]Frac}?{[eE]Int}?
//  Frac        ::= [0-9]+
//  Int         ::= [0-9]+
//  Function    ::= "sin"Number | "cos"Number | "tg"Number | "ctg"Number | "ln"Number
//  $           ::= [\0]
//
//=======================================================================================================================================================================================

const char* remove_spaces (char* Buffer)
{
    int counter = 0;
    int inline_counter = 0;


    while (Buffer[counter] != '\0')
    {
        if (Buffer[counter] == ' ')
        {
            inline_counter = counter;

            while (Buffer[inline_counter] != '\0')
            {
                Buffer[inline_counter] = Buffer[inline_counter + 1];  //printf ("%d '%c' <- '%c'\n", inline_counter, Buffer[inline_counter], Buffer[inline_counter + 1]);

                inline_counter++; //printf ("'%c'\n", Buffer[inline_counter]);
            }
        }
        else
        {
            ++counter;
        }
    }

    return Buffer;
}

//=======================================================================================================================================================================================

double get_Main (const char* Buffer)
{
    Line = Buffer;

    double Value = get_Add ();

    double SecondValue = get_$ ();

    //MLA (*Line == '\0');

    return Value;
}

double get_Add (void)
{
    double Value = get_Mul ();

    while ((*Line == '+') || (*Line == '-'))
    {
        char Operation = *Line;
        Line++;

        double SecondValue = get_Mul ();

        if (Operation == '+')
        {
            Value = Value + SecondValue;
        }
        else
        {
            Value = Value - SecondValue;
        }
    }

    return Value;
}

double get_Mul (void)
{
    double Value = get_Pow ();

    while ((*Line == '*') || (*Line == '/'))
    {
        char Operation = *Line;
        Line++;

        double SecondValue = get_Pow ();

        if (Operation == '*')
        {
            Value = Value * SecondValue;
        }
        else
        {
            Value = Value / SecondValue;
        }
    }

    return Value;
}

double get_Pow (void)
{
    double Value = get_Bracket ();

    while (*Line == '^')
    {
        Line++;

        double SecondValue = get_Bracket ();

        Value = pow (Value, SecondValue);
    }

    return Value;
}

double get_Bracket (void)
{
    double Value = 0;

    //printf ("'%c'\n", *Line);

    if (*Line == '(')
    {
        Line++;

        Value = get_Add ();

        MLA (*Line == ')');

        Line++;
    }

    #define DEF_UFUNC(def_length, def_name, def_func) \
    else if (strncasecmp (Line, def_name, def_length) == 0) \
    {\
        \
        Value = get_Function ();\
    }

    #include "ufunctions.h"

    #undef DEF_UFUNC

    else
    {
        Value = get_Number ();
    }

    return Value;
}

double get_Number (void)
{
    if (*Line == 'e' || *Line == 'E')
    {
        Line++;
        return M_E;
    }

    if (strncasecmp (Line, "PI", 2) == 0)
    {
        Line += 2;

        return M_PI;
    }

    double Value = get_Int ();

    double SecondValue = 0;

    double ThirdValue = 0;

    if (*Line == '.')
    {
        Line++;

        SecondValue = get_Frac ();
    }


    if (*Line == 'e' || *Line == 'E')
    {
        Line++;

    //         int Marker = 0;
    //
    //         Marker = *Line;
    //
    //         MLA (Marker == '-' || Marker == '+');
    //
    //         Line++;

        ThirdValue = get_Int ();
    }

    Value = Value + SecondValue;

    Value = Value * pow (10, ThirdValue);

    return Value;
}

double get_Frac (void)
{
    int counter = 1;

    int in_counter = 0;

    double Value = 0;

    double Add = 0;

    const char* OldPtr = Line;

    while (*Line >= '0' && *Line <= '9')
    {
        Add = (*Line - '0');

        in_counter = counter;

        while (in_counter > 0)
        {
            Add /= 10;

            in_counter--;
        }

        Value = Value  + Add;

        counter++;

        Line++;
    }

    MLA (Line > OldPtr);

    return Value;
}

double get_Int (void)
{
    double Value = 0;

    const char* OldPtr = Line;

    while (*Line >= '0' && *Line <= '9')
    {
        Value = Value * 10 + (*Line - '0');

        Line++;
    }

    MLA (Line > OldPtr);

    return Value;
}

double get_Function (void)
{
    double Value = 0;

    const char* OldPtr = Line;

    if (0) {}
    #define DEF_UFUNC(def_length, def_name, def_func) \
    else if (strncasecmp (Line, def_name, def_length) == 0) \
    {\
        Line += def_length;\
        \
        Value = get_Bracket ();\
        \
        Value = def_func ;\
    }

    #include "ufunctions.h"

    #undef DEF_UFUNC




    MLA (Line > OldPtr);

    return Value;
}

double get_$ (void)
{
    double Value = 0;

    const char* OldPtr = Line;

    if (*Line == '\0')
    {
        Line++;
    }

    MLA (Line > OldPtr);

    return Value;
}

//=======================================================================================================================================================================================
