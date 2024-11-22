#include "random.hxx"

#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.141592653
#endif

double my_math::drand()
{
    return (rand() + 1.0) / (RAND_MAX + 1.0);
}

double my_math::random_normal()
{
    return sqrt(-2 * log(drand())) * cos(2 * M_PI * drand());
}