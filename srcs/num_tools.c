#include "wolf3d.h"

double        double_modulo(double num)
{
    //printf("num %f ", num);
    num = (int)num % 360 + num - (int)num;
    //printf("num modulo %f\n", num);
    return (num);
}

double        angle_adaptater(double angle)
{
    if (angle < 0.0)
        angle += 360.0;
    else if (angle > 360.0)
        angle = double_modulo(angle);
    return (angle);
}
