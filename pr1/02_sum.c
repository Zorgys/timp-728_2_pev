#include <stdio.h>

int main (void)
{
    double A, B;
    int err = scanf("%lf %lf", &A, &B);
    double Ans = A + B;
    err = printf("%lf", Ans);
    return err;
}