#pragma once
#include <cmath>
#include "../raylib/src/raylib.h"

inline float WrapAngle(float angle)
{
    const float twoPi = 2.0f * PI;
    angle = fmodf(angle, twoPi);
    if (angle < 0)
        angle += twoPi;
    return angle;
}