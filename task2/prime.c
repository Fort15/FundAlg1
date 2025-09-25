#include "prime.h"


int is_prime(int chislo) {
    if (chislo <= 1 || (chislo % 2 == 0 && chislo != 2)) return 0;
    for (int i = 3; (long long) i * i <= chislo; i += 2) {
        if (chislo % i == 0) return 0;
    }
    return 1;
}

Status n_prime(int n, int *chislo) {
    if (n <= 0 || !chislo) return STATUS_INVALID_INPUT_N;
    if (n > 10000) return STATUS_WRONG_N;

    int k = 0, number = 1;
    while (k < n) {
        ++number;
        if (is_prime(number)) ++k;
    }
    *chislo = number;
    return STATUS_OK;
}