#ifndef EXPLICITRUNGEKUTTA_H
#define EXPLICITRUNGEKUTTA_H

double func(double x, double u);

double ExplicitRungeKutta(double h, double xprev, double uprev, double (*f)(double x, double u));

double Implicit(double h, double x, double uprev,  double (*f)(double x, double u));


#endif // EXPLICITRUNGEKUTTA_H

