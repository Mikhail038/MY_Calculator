#include <stdio.h>
#include "calc.h"

int main ()
{
    char* RawLine = NULL;

    scanf ("%m[^\n]", &RawLine);

    //printf ("'%s'\n", RawLine);

    const char* Line = remove_spaces (RawLine);

    //printf ("'%s'\n", Line);

    printf ("%lg\n", get_Main (Line));

    free (RawLine);

    return 0;
}
