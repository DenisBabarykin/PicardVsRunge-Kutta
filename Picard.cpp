#include "Picard.h"
#include <cmath>

// These Picard's method iteration functions calcs solution for ODE: u'(x) = x^2 + u^2

long double PicardFirstIteration(long double x)
{
    return x * x * x / 3;
}

long double PartialPicardSecondIteration(long double x)
{
    return 1 + pow(x, 4) / 21;
}

long double PartialPicardThirdIteration(long double x)
{
    return x * pow(x, 8) / 693 + pow(x, 12) / 19845;
}
