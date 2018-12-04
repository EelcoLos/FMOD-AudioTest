#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"

#include <iostream>


void static ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}