#ifndef PICARD
#define PICARD

// These Picard's method iteration functions calcs solution for ODE: u'(x) = x^2 + u^2

double PicardFirstIteration(double x);
double PartialPicardSecondIteration(double x);
double PartialPicardThirdIteration(double x);

#endif // PICARD

