#include "functions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// валидация данных

Status stroka_to_int(const char *stroka, int *chislo) {
    if (!stroka || !chislo) return STATUS_INVALID_NUMBER;

    char *endptr = NULL;
    long x = strtol(stroka, &endptr, 10);

    if (*endptr != '\0') return STATUS_INVALID_NUMBER;
    if (stroka == endptr) return STATUS_INVALID_NUMBER;
    if (x > 2147483647 || x < -2147483648) return STATUS_TOO_BIG_INT;

    *chislo = (int)x;
    return STATUS_OK;
}

Status validate_flag(const char *stroka, char *flag) {
    if (!stroka || !flag) return STATUS_INVALID_FLAG;
    if (stroka[0] != '-' && stroka[0] != '/') return STATUS_INVALID_FLAG;

    char f = stroka[1];
    if (stroka[2] != '\0') return STATUS_INVALID_FLAG;

    switch (f) {
        case 'h': case 'p': case 's': case 'e': case 'a': case 'f':
            *flag = f;
            return STATUS_OK;
        default:
            return STATUS_INVALID_FLAG;
    }
}

// действия с числом

Status flag_h(int x) {
    if (x <= 0 || x > 100) {
        printf("Нет натуральных чисел в пределах 100 кратных %d\n", x);
        return STATUS_OK;
    }

    for (int i = x; i <= 100; i += x) {
        printf("%d ", i);
    }
    printf("\n");
    return STATUS_OK;
}

Status flag_p(int x) {
    if (x <= 1) {
        printf("Число %d не является ни простым, ни составным\n", x);
        return STATUS_OK;
    }

    int is_prime = 1;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            is_prime = 0;
            break;
        }
    }

    if (is_prime) printf("Число %d является простым\n", x);
    else printf("Число %d является составным\n", x);
    return STATUS_OK;
}

Status flag_s(int x) {
    if (x == 0) {
        printf("0\n");
        return STATUS_OK;
    }
    if (x < 0) {
        printf("Нельзя отрицательные числа\n");
        return STATUS_NEGATIVE_IS_NOT_ALLOWED;
    }

    char buf[32];
    char *p = buf + 31;
    *p-- = '\0';
    int r;
    while (x) {
        r = x % 16;
        if (r > 9) *p-- = r - 10 + 'A';
        else *p-- = r + '0';
        x /= 16;
    }
    printf("%s\n", p + 1);
    return STATUS_OK;
}

Status flag_e(int x) {
    if (x < 1 || x > 10) return STATUS_INVALID_NUMBER;


    for (int base = 1; base <= 10; ++base) {
        long long result = 1;
        for (int exp = 1; exp <= x; ++exp) {
            result *= base;
            if (exp > 1) printf("  ");
            printf("%2d ^ %-2d = %-10lld", base, exp, result);
        }
        printf("\n");
    }
    return STATUS_OK;
}

Status flag_a(int x) {
    if (x <= 0) {
        printf("Нельзя вычислить сумму (или просто 0)\n");
        return STATUS_OK;
    }

    long long result = (long long)x * (x + 1) / 2;
    printf("Сумма натуральных чисел от 1 до %d = %lld\n", x, result);
    return STATUS_OK;
}

Status flag_f(int x) {
    if (x < 0) {
        printf("Нельзя отрицательные\n");
        return STATUS_NEGATIVE_IS_NOT_ALLOWED;
    }
    if (x >= 21) {
        printf("Слишком большой факториал\n");
        return STATUS_INVALID_NUMBER;    // 21! > ull
    }
    unsigned long long fact = 1;
    for (int i = 2; i <= x; ++i) {
        fact *= i;
    }
    printf("%llu\n", fact);
    return STATUS_OK;   
}
