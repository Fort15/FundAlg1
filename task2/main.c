#include "prime.h"
#include <stdio.h>


int main() {
    // int primes[MAX_N];
    // int prime_count = 0;
    // int last_checked = 1;
    char line[256];

    if (!fgets(line, sizeof(line), stdin)) {
        printf("Не удалось считать строку\n");
        return 0;
    }
    
    int T;
    Status status = stroka_to_int(line, &T);
    if (status != STATUS_OK) {
        printf("Некорректное число\n");
        return 0;
    }
    if (T <= 0 || T > MAX_T) {
        printf("Введено неверное T ([1, 10000])\n");
        return 0;
    }
    while (T--) {
        if (!fgets(line, sizeof(line), stdin)) {
            printf("Не удалось считать строку\n");
            return 0;
        }
        
        int n;
        status = stroka_to_int(line, &n);
        if (status != STATUS_OK) {
            printf("Некорректное число\n");
            // continue;
            return 0;
        }
        
        int prime;
        status = n_prime(n, &prime);
        switch (status) {
            case STATUS_INVALID_INPUT_N:
                printf("Неправильно введено N\n");
                break;
            
            case STATUS_WRONG_N:
                printf("Слишком большое N ([1, 10000])\n");
                break;
            
            case STATUS_OK:
                printf("Простое число под номер %d = %d\n", n, prime);
                break;

            default:
                printf("Неизвестная ошибка\n");
                break;
        }
    }
    
    return 0;
}