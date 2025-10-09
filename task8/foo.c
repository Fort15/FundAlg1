#include "foo.h"
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

Status validate_base(int* base, char buf[]) {
    if (isdigit(buf[0]) && isdigit(buf[1]) && buf[2] == '\n') {
        *base = (buf[0] - '0') * 10 + (buf[1] - '0');
    } else if (isdigit(buf[0]) && buf[1] == '\n') {
        *base = (buf[0] - '0');
    } else {
        return STATUS_INVALID_BASE;
    }
    if (*base < 2 || *base > 36) {
        return STATUS_INVALID_BASE;
    }
    return STATUS_OK;
}

Status str_to_ll(const char* stroka, int base, long long* chislo) {
    const char* p = stroka;
    int sign = 1;
    if (*p == '-') {
        sign = -1;
        ++p;
    } else if (*p == '+') ++p;

    if (!*p) return STATUS_INVALID_NUMBER;

    unsigned long long result = 0;

    while (*p) {
        int digit;
        if (*p >= '0' && *p <= '9') digit = *p - '0';
        else if (*p >= 'A' && *p <= 'Z') digit = *p - 'A' + 10;
        else return STATUS_INVALID_NUMBER;

        if (digit >= base) return STATUS_INVALID_NUMBER;

        result = result * base + digit;
        if (result > LLONG_MAX) {    // == llmin не обрабатывается исходя из модуля
            return STATUS_TOO_BIG_LL;
        }
        ++p;
    }
    *chislo = (sign == 1) ? (long long)result : -(long long)result;
    return STATUS_OK;
}

char* number_with_base(long long chislo, int base) {
    static char buf[256];
    char *p = buf + sizeof(buf) - 1;
    int sign = 1;
    unsigned long long num;
    int r;
    
    if (chislo == 0) {
        *(--p) = '0';
        return p;
    }
    if (chislo < 0) {
        sign = -1;
        num = -(unsigned long long)chislo;
    } else {
        num = (unsigned long long)chislo;
    }
    *p-- = '\0';
    while (num) {
        r = num % base;
        if (r > 9) *p-- = r - 10 + 'A';
        else *p-- = r + '0';
        num /= base;
    }

    *p++;
    if (sign == -1) *(--p) = '-';
    return p;
}

// char* normalize(char* str) {
//     char* p = str;
//     if (*p == '-' || *p == '+') p++;
//     while(*p == '0' && *(p + 1) != '\0') {
//         p++;
//     }
//     return p;
// }