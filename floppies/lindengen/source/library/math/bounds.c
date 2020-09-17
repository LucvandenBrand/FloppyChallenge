#include "math/bounds.h"

float clamp(float value, float min_value, float max_value) {
    const float clamp_min = value < min_value ? min_value : value;
    return clamp_min > max_value ? max_value : clamp_min;
}

float snap_to_value(float snapped_value, float value, float threshold)
{
    float delta = snapped_value - value;
    float absolute_delta = delta < 0 ? -1 * delta : delta;
    if (absolute_delta > threshold)
        return snapped_value;
    return value;
}