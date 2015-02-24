#ifndef PICARD
#define PICARD

// These Picard's method iteration functions calcs solution for ODE: u'(x) = x^2 + u^2

long double PicardFirstIteration(long double x);
long double PartialPicardSecondIteration(long double x);
long double PartialPicardThirdIteration(long double x);

#endif // PICARD

