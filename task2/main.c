#include "prime.h"
#include <stdio.h>


int main() {
    int T, n, prime;
    Status status;
    if (scanf("%d", &T) != 1) return STATUS_INVALID_INPUT_T;

    if (T <= 0 || T > 10000) return STATUS_WRONG_T; 
    while (T--) {
        if (scanf("%d", &n) != 1) return STATUS_INVALID_INPUT_N;
        status = n_prime(n, &prime);
        if (status != STATUS_OK) return (int)status;

        printf("%d\n", prime);
    }
    return STATUS_OK;
}