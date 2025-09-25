#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef enum {
    STATUS_OK,
    STATUS_INVALID_FLAG,
    STATUS_INVALID_ARGC,
    STATUS_INVALID_NUMBER,
    STATUS_TOO_BIG_INT,
} Status;

Status validate_flag(const char *stroka, char *flag);
Status flag_q(int argc, char *argv[]);
Status flag_m(int argc, char *argv[]);
Status flag_t(int argc, char *argv[]);
Status stroka_to_int(const char *stroka, int *chislo);
Status stroka_to_double(const char *stroka, double *chislo);
int double_equal(double a, double b, double eps);
void solve_uravn(double a, double b, double c, double eps);

#endif