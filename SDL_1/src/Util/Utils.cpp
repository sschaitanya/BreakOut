//
//  Utils.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/17/20.
//

#include "Utils.hpp"
#include <cmath>

bool IsEqual(float x, float y)
{
    return fabsf(x - y) < EPSILON;
}

bool IsGreaterThanOrEqual(float x, float y)
{
    return x > y || IsEqual(x, y);
}

bool IsLessThanOrEqual(float x, float y)
{
    return x < y || IsEqual(x, y);
}

float MilliSecondsToSeconds(unsigned int milli_seconds){
    return static_cast<float>(milli_seconds)/1000.0f;
}


