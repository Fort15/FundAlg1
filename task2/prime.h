#ifndef PRIME_H
#define PRIME_H

#define MAX_N 10000
#define MAX_T 10000

typedef enum {
    STATUS_OK,     
    STATUS_WRONG_T,    
    STATUS_WRONG_N,    
    STATUS_INVALID_INPUT,
    STATUS_TOO_BIG_INT,
    STATUS_INVALID_INPUT_N,
} Status;

Status n_prime(int n, int *chislo);
Status stroka_to_int(const char *str, int *result);
// Status n_prime(int n, int *primes, int *prime_count, int *last_checked, int *chislo);

#endif