#include "wolf3d.h"

float        float_modulo(float num)
{
    //printf("num %f ", num);
    num = (int)num % 360 + num - (int)num;
    //printf("num modulo %f\n", num);
    return (num);
}

float        angle_adaptater(float angle)
{
    float    num;

    if (angle < 0.0)
        angle += 360;
    else if (angle > 360.0)
        angle = float_modulo(angle);
    return (angle);
}
