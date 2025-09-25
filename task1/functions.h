#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef enum {
    STATUS_OK,
    STATUS_INVALID_ARGC,    // неверное число аргументов
    STATUS_INVALID_NUMBER,  // неверное число
    STATUS_INVALID_FLAG,    // неверный флаг
    STATUS_NEGATIVE_IS_NOT_ALLOWED,
    STATUS_TOO_BIG_INT,     // переполнение int
} Status;


Status stroka_to_int(const char *stroka, int *chislo);
Status validate_flag(const char *stroka, char *flag);
Status flag_h(int x);
Status flag_p(int x);
Status flag_s(int x);
Status flag_e(int x);
Status flag_a(int x);
Status flag_f(int x);
#endif