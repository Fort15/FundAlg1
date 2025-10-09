#ifndef FOO_H
#define FOO_H

typedef enum {
    STATUS_OK,
    STATUS_INVALID_BASE,
    STATUS_INVALID_NUMBER,
    STATUS_TOO_BIG_LL,
} Status;

Status validate_base(int* base, char buf[]);
Status str_to_ll(const char* stroka, int base, long long* chislo);
char* number_with_base(long long chislo, int base);
// char* normalize(char* stroka);

#endif