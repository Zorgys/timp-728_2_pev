#include <stdio.h>
#include <math.h>

int main (void)
{
    double A, B;
    int err = scanf("%lf %lf", &A, &B);
    double Ans = pow(A, B);
    err = printf("%lf", Ans);
    return err;
}