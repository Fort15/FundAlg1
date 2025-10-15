#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef enum {
    STATUS_OK,
    STATUS_INVALID_ARGC,
    STATUS_INVALID_EPS,
    STATUS_INVALID_NUMBER,
} Status;

double f_a(double x);
double f_b(double x);
double f_c(double x);
double f_d(double x);

double integrate(double a, double b, double eps, double (*f)(double));

Status parse_eps(const char *stroka, double *eps);
#endif