#ifndef EXPLICITRUNGEKUTTA_H
#define EXPLICITRUNGEKUTTA_H

long double ExplicitRungeKutta(long double h, long double xprev, long double uprev, long double (*f)(long double x, long double u));

long double Implicit(long double h, long double x, long double uprev,  long double (*f)(long double x, long double u));


#endif // EXPLICITRUNGEKUTTA_H

