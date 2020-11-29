//
//  Utils.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/17/20.
//

#ifndef Utils_hpp
#define Utils_hpp

static const float EPSILON = 0.0001f;

const float PI = 3.14159f;
const float TWO_PI = 2.0f * PI;

bool IsEqual(float x, float y);

bool IsGreaterThanOrEqual(float x, float y);

bool IsLessThanOrEqual(float x, float y);

float MilliSecondsToSeconds(unsigned int milli_seconds);

#endif /* UTILS_UTILS_H_ */
