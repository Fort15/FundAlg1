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

double integrate_a(double a, double b, double eps) {
    int n = 1;
    double h = b - a, Sprev = 0.0;
    double Scur = (1.0 + log(1.0 + b) / b) * 0.5 * h;

    while (fabs(Scur - Sprev) >= eps) {
        if (n > 1000000) {
            break;
        }
        Sprev = Scur;
        n *= 2;
        h = (b - a) / n;
        double sum = (1.0 + log(2.0) / 1.0);
        for (int i = 1; i < n; ++i) {
            double x = a + i * h;
            double fx = (fabs(x - 0.0) < 1e-12) ? 1.0 : log(1.0 + x) / x;
            sum += 2 * fx;
        }
        Scur = 0.5 * h * sum;
    }

    return Scur;
}

double integrate_b(double a, double b, double eps) {
    int n = 1;
    double h = b - a, Sprev = 0.0;
    double Scur = (exp(-a * a / 2.0) + exp(-b * b / 2.0)) * 0.5 * h;

    while (fabs(Scur - Sprev) >= eps) {
        if (n > 1000000) {
            break;
        }
        Sprev = Scur;
        n *= 2;
        h = (b - a) / n;
        double sum = exp(-a * a / 2.0) + exp(-b * b / 2.0);
        for (int i = 1; i < n; ++i) {
            double x = a + i * h;
            double fx = exp(-x * x / 2.0);
            sum += 2 * fx;
        }
        Scur = 0.5 * h * sum;
    }

    return Scur;
}

double integrate_c(double a, double b, double eps) {
    int n = 1;
    double h = b - a, Sprev = 0.0;
    int infinity = 100;
    double Scur = (log(1.0 / (1.0 - a)) + infinity) * 0.5 * h;

    while (fabs(Scur - Sprev) >= eps) {
        if (n > 1000000) {
            break;
        }
        Sprev = Scur;
        n *= 2;
        h = (b - a) / n;
        double sum = log(1.0 / (1.0 - a)) + infinity;
        for (int i = 1; i < n; ++i) {
            double x = a + i * h;
            double fx = log(1.0 / (1.0 - x));
            sum += 2 * fx;
        }
        Scur = 0.5 * h * sum;
    }

    return Scur;
}

double integrate_d(double a, double b, double eps) {
    int n = 1;
    double h = b - a, Sprev = 0.0;
    double Scur = (1 + pow(b, b)) * 0.5 * h;

    while (fabs(Scur - Sprev) >= eps) {
        if (n > 1000000) {
            break;
        }
        Sprev = Scur;
        n *= 2;
        h = (b - a) / n;
        double sum = 1 + pow(b, b);
        for (int i = 1; i < n; ++i) {
            double x = a + i * h;
            double fx = pow(x, x);
            sum += 2 * fx;
        }
        Scur = 0.5 * h * sum;
    }

    return Scur;
}