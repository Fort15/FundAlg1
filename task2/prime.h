#ifndef PRIME_H
#define PRIME_H

typedef enum {
    STATUS_OK,
    STATUS_INVALID_INPUT_T,     
    STATUS_WRONG_T,     // T < 10000
    STATUS_WRONG_N,     // N < 10000
    STATUS_INVALID_INPUT_N,
} Status;

Status n_prime(int n, int *chislo);

#endif