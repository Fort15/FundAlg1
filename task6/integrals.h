#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef enum {
    STATUS_OK,
    STATUS_INVALID_ARGC,
    STATUS_INVALID_EPS,
    STATUS_INVALID_NUMBER,
} Status;

Status parse_eps(const char *stroka, double *eps);
double integrate_a(double a, double b, double eps);
double integrate_b(double a, double b, double eps);
double integrate_c(double a, double b, double eps);
double integrate_d(double a, double b, double eps);
#endif