#ifndef FOO_H
#define FOO_H

#include <stdio.h>

typedef enum {
    STATUS_OK,
    STATUS_SAME_FILES,
    STATUS_INVALID_BASE,
    STATUS_INVALID_NUMBER,
    STATUS_TOO_BIG_LL,
} Status;


Status same_files(const char *file1, const char *file2);
Status str_to_ll(const char* stroka, int base, long long* chislo);
Status min_base(const char* stroka, int* base);
char* normalize(char* stroka);


#endif