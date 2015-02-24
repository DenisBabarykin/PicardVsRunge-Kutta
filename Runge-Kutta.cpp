#include "Runge-Kutta.h"
#include <cmath>

double func(double x, double u)
{
    return x * x + u * u;
}


double ExplicitRungeKutta(double h, double xprev, double uprev, double (*f)(double, double))
{
    return uprev + h * f(xprev, uprev);
}


double Implicit(double h, double x, double uprev, double (*f)(double, double))
{
    double discriminant = 1 - 4 * h * (h * (x + h) * (x + h) + uprev);
    return (1 - sqrt(discriminant)) / (2 * h);
}
