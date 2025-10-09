#include "prime.h"
#include <limits.h>
#include <stdlib.h>


Status stroka_to_int(const char *stroka, int *chislo) {
    if (!stroka || !chislo) return STATUS_INVALID_INPUT;

    char *endptr = NULL;
    long x = strtol(stroka, &endptr, 10);

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n') {
        endptr++;
    }

    if (*endptr != '\0') return STATUS_INVALID_INPUT;
    if (stroka == endptr) return STATUS_INVALID_INPUT;
    if (x > INT_MAX || x < INT_MIN) return STATUS_TOO_BIG_INT;

    *chislo = (int)x;
    return STATUS_OK;
}

int is_prime(int chislo) {
    if (chislo <= 1 || (chislo % 2 == 0 && chislo != 2)) return 0;
    for (int i = 3; (long long) i * i <= chislo; i += 2) {
        if (chislo % i == 0) return 0;
    }
    return 1;
}

Status n_prime(int n, int *chislo) {
    if (n <= 0 || !chislo) return STATUS_INVALID_INPUT_N;
    if (n > MAX_N) return STATUS_WRONG_N;

    int k = 0, number = 1;
    while (k < n) {
        ++number;
        if (is_prime(number)) ++k;
    }
    *chislo = number;
    return STATUS_OK;
}





// Status n_prime(int n, int *primes, int *prime_count, int *last_checked, int *chislo) {
//     if (n <= 0 || n > MAX_N || !primes || !prime_count || !last_checked || !chislo) {
//         return STATUS_WRONG_N;
//     }
    
//     if (n <= *prime_count) {
//         *chislo = primes[n - 1];
//         return STATUS_OK;
//     }
    
//     int current_prime = (*prime_count == 0) ? 2 : *last_checked + 1;
//     while (*prime_count < n) {
//         if (is_prime(current_prime)) {
//             primes[*prime_count] = current_prime;
//             (*prime_count)++;
//         }
//         current_prime++;
//     }
    
//     *last_checked = current_prime - 1;
//     *chislo = primes[n - 1];
//     return STATUS_OK;
// }