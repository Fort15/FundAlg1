#include "integrals.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Status parse_eps(const char *stroka, double *eps) { 
    if (!stroka || !eps) {
        return STATUS_INVALID_NUMBER;
    }

    char *endptr;
    double x = strtod(stroka, &endptr);

    if (*endptr != '\0') return STATUS_INVALID_EPS;
    if (x <= 0) return STATUS_INVALID_EPS;
    *eps = x;
    return STATUS_OK;
}

double f_a(double x) {
    return (x != 0) ? log(1.0 + x) / x : 1.0;
}

double f_b(double x) {
    return exp(-x * x / 2.0);
}

double f_c(double x) {
    int inf = 100;
    return (x != 1.0) ? -log(1.0 - x) : inf;
}

double f_d(double x) {
    return pow(x, x);
}

double integrate(double a, double b, double eps, double (*f)(double)) {
    int n = 1;
    double h = b - a;
    double fa = f(a), fb = f(b);
    double Sprev = 0.0, Scur = (fa + fb) * 0.5 * h;

    while (fabs(Scur - Sprev) >= eps) {
        if (n > 1000000) {
            break;
        }
        Sprev = Scur;
        n *= 2;
        h = (b - a) / n;
        double sum = fa + fb;
        for (int i = 1; i < n; ++i) {
            double x = a + i * h;
            sum += 2 * f(x);
        }
        Scur = 0.5 * h * sum;
    }

    return Scur;
}