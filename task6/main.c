#include <stdio.h>
#include "integrals.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Неверное число аргументов\n");
        return STATUS_INVALID_ARGC;
    }

    double eps;
    Status status = parse_eps(argv[1], &eps);
    if (status != STATUS_OK) {
        printf("Неправильно задан eps\n");
        return 0;
    }

    double a = 0.0, b = 1.0;
    double (*f)(double);
    printf("a. %.10f\n", integrate(a, b, eps, f_a));   // 0,8224670210725264
    printf("b. %.10f\n", integrate(a, b, eps, f_b)); // 0.8556243918921488
    printf("c. %.10f\n", integrate(a, b, eps, f_c));  // 1
    printf("d. %.10f\n", integrate(a, b, eps, f_d)); // 0.7834305107121344
}