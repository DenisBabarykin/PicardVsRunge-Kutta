#include "Picard.h"
#include <cmath>

// These Picard's method iteration functions calcs solution for ODE: u'(x) = x^2 + u^2

double PicardFirstIteration(double x)
{
    return x * x * x / 3;
}

double PartialPicardSecondIteration(double x)
{
    return 1 + pow(x, 4) / 21;
}

double PartialPicardThirdIteration(double x)
{
    return x * pow(x, 8) / 693 + pow(x, 12) / 19845;
}
