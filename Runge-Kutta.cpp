#include "Runge-Kutta.h"
#include <cmath>

long double ExplicitRungeKutta(long double h, long double xprev, long double uprev, long double (*f)(long double, long double))
{
    return uprev + h * f(xprev, uprev);
}


long double Implicit(long double h, long double x, long double uprev, long double (*f)(long double, long double))
{
//    long double discriminant = 1 - 4 * h * (h * (x + h) * (x + h) + uprev);
//    return (1 - sqrt(discriminant)) / (2 * h);
    return 1 / (2 * h) - sqrt(1/pow(2*h, 2) - (uprev/h + x * x));
}
