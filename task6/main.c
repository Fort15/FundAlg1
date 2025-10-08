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
    printf("a. %.10f\n", integrate_a(a, b, eps));   // 0,8224670210725264
    printf("b. %.10f\n", integrate_b(a, b, eps)); // 0.8556243918921488
    printf("c. %.10f\n", integrate_c(a, b, eps));  // 1
    printf("d. %.10f\n", integrate_d(a, b, eps)); // 0.7834305107121344
}