
#include <math.h>

#include "calc.h"

//=======================================================================================================================================================================================

const char* Line = NULL;

//=======================================================================================================================================================================================
//
//  G ::= E$
//  E ::= T{[+-]T}*
//  T ::= S{[*/]S}*
//  S ::= P{[^]P}*
//  P ::= '('E')'|N
//  N ::= [0-9]+
//  $ ::= [\0]
//
//
//
//
//===================s====================================================================================================================================================================

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

double get_G (const char* Buffer)
{
    Line = Buffer;

    double Value = get_E ();

    double SecondValue = get_$ ();

    //MLA (*Line == '\0');

    return Value;
}

double get_E (void)
{
    double Value = get_T ();

    while ((*Line == '+') || (*Line == '-'))
    {
        char Operation = *Line;
        Line++;

        double SecondValue = get_T ();

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

double get_T (void)
{
    double Value = get_S ();

    while ((*Line == '*') || (*Line == '/'))
    {
        char Operation = *Line;
        Line++;

        double SecondValue = get_S ();

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

double get_S (void)
{
    double Value = get_P ();

    while (*Line == '^')
    {
        Line++;

        double SecondValue = get_P ();

        Value = pow (Value, SecondValue);
    }

    return Value;
}

double get_P (void)
{
    double Value = 0;

    if (*Line == '(')
    {
        Line++;

        Value = get_E ();

        MLA (*Line == ')');

        Line++;
    }
    else
    {
        Value = get_N ();
    }

    return Value;
}

double get_N (void)
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
