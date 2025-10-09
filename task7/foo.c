#include "foo.h"
#include <limits.h>

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
        else if (*p >= 'a' && *p <= 'z') digit = *p - 'a' + 10;
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

Status min_base(const char* stroka, int* base) {
    if (!stroka || !base) return STATUS_INVALID_BASE;

    int max_digit = 0;
    const char* p = stroka;
    if (*p == '-' || *p == '+') p++;

    if (!*p) return STATUS_INVALID_BASE;

    while (*p) {
        int digit;
        if (*p >= '0' && *p <= '9') {
            digit = *p - '0';
        } else if (*p >= 'A' && *p <= 'Z') {
            digit = *p - 'A' + 10;
        } else if (*p >= 'a' && *p <= 'z') {
            digit = *p - 'a' + 10;
        } else {
            return STATUS_INVALID_BASE;
        }
        
        if (digit > max_digit) {
            max_digit = digit;
        }
        p++;
    }

    max_digit++;
    if (max_digit == 1) ++max_digit;
    if (max_digit < 2 || max_digit > 36) return STATUS_INVALID_BASE;

    *base = max_digit;
    
    return STATUS_OK;
}

char* normalize(char* stroka) {
    char* p = stroka;
    if (*p == '+' || *p == '-') {
        p++;
    }

    int was_negative = (stroka[0] == '-');
    
    while (*p == '0' && *(p + 1) != '\0') {
        p++;
    }
    
    if (was_negative && *p == '0' && *(p + 1) == '\0') {
        return p;
    }
    
    if (was_negative) {
        p--;
        *p = '-';
    }
    
    return p;
}