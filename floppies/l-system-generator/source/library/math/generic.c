#include "math/generic.h"

float signf(float value)
{
    if (value > 0) return 1;
    if (value < 0) return -1;
    return 0;
}