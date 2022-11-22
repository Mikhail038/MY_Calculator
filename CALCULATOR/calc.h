#ifndef CALC_H
#define CALC_H

#include "MYassert.h"
#include "assert.h"

//=======================================================================================================================================================================================

const char* remove_spaces (char* Buffer);

//=======================================================================================================================================================================================

double get_Main (const char* Buffer);

double get_Add (void);

double get_Mul (void);

double get_Pow (void);

double get_Bracket (void);

double get_Number (void);

double get_Frac (void);

double get_Int (void);

double get_Function (void);

double get_$ (void);

//=======================================================================================================================================================================================

#endif
