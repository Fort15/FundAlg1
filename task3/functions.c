#include "functions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Вспомогательные функции

int double_equal(double a, double b, double eps) {
    return fabs(a - b) <= eps;
}

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

void solve_uravn(double a, double b, double c, double eps) {
    if (double_equal(a, 0, eps)) {
        if (double_equal(b, 0, eps)) {
            if (double_equal(c, 0, eps)) printf("x - любое\n");
            else printf("Нет решений\n");
        }
        else {
            printf("x = %.3f\n" , -c / b);
        }
    }
    else {
        double D = b * b - 4 * a * c;
        if (D < 0) printf("Нет решений (комплексные)\n");
        else if (D == 0) printf("x = %.3f\n", -b / 2 / a);
        else {
            double x1 = (-b + sqrt(D)) / 2 / a, x2 = (-b - sqrt(D)) / 2 / a;
            printf("x1 = %.3f   x2 = %.3f\n", x1, x2);
        }
    }
}

Status stroka_to_double(const char *stroka, double *chislo) {
    if (!stroka || !chislo) return STATUS_INVALID_NUMBER;

    char *endptr = NULL;
    double x = strtod(stroka, &endptr);

    if (*endptr != '\0') return STATUS_INVALID_NUMBER;
    if (stroka == endptr) return STATUS_INVALID_NUMBER;

    *chislo = x;
    return STATUS_OK;
}

Status validate_flag(const char *stroka, char *flag) {
    if (!stroka || !flag) return STATUS_INVALID_FLAG;
    if (stroka[0] != '-' && stroka[0] != '/') return STATUS_INVALID_FLAG;

    char f = stroka[1];
    if (stroka[2] != '\0') return STATUS_INVALID_FLAG;

    switch (f) {
        case 'q': case 'm': case 't':
            *flag = f;
            return STATUS_OK;
        default:
            return STATUS_INVALID_FLAG;
    }
}

Status flag_m(int argc, char *argv[]) {
    if (argc != 4) {
        // printf("Нужно 2 числа a b\n");
        return STATUS_INVALID_ARGC;
    }

    int a, b;
    Status status;
    if ((status = stroka_to_int(argv[2] , &a)) != STATUS_OK) return status;
    if ((status = stroka_to_int(argv[3] , &b)) != STATUS_OK) return status;

    if (a == 0 || b == 0) {
        // printf("Должны быть ненулевые числа\n");
        return STATUS_INVALID_NUMBER;
    }

    if (a % b == 0) printf("%d кратно %d\n", a, b);
    else printf("%d не кратно %d\n", a, b);

    return STATUS_OK;
}

Status flag_t(int argc, char *argv[]) {
    if (argc != 6) {
        // printf("Нужно 4 числа: eps a b c\n");
        return STATUS_INVALID_ARGC;
    }

    double eps, a, b , c;
    Status status;
    if ((status = stroka_to_double(argv[2] , &eps)) != STATUS_OK) return status;
    if ((status = stroka_to_double(argv[3] , &a)) != STATUS_OK) return status;
    if ((status = stroka_to_double(argv[4] , &b)) != STATUS_OK) return status;
    if ((status = stroka_to_double(argv[5] , &c)) != STATUS_OK) return status;

    if (eps < 0 || a <= 0 || b <= 0 || c <= 0) {
        // printf("Все числа должны быть положительные\n");
        return STATUS_INVALID_NUMBER;
    }

    double A = a * a, B = b * b, C = c * c;
    if (double_equal(A + B, C, eps) || double_equal(A + C, B, eps) ||
        double_equal(B + C, A, eps)) {
            printf("Стороны являются сторонами прямоугольного треугольника\n");
        }
    else printf("Стороны не являются сторонами прямоугольного треугольника\n");
    return STATUS_OK;
}

Status flag_q(int argc, char *argv[]) {
        if (argc != 6) {
        // printf("Нужно 4 числа: eps a b c\n");
        return STATUS_INVALID_ARGC;
    }

    double eps, a, b , c;
    Status status;
    if ((status = stroka_to_double(argv[2] , &eps)) != STATUS_OK) return status;
    if ((status = stroka_to_double(argv[3] , &a)) != STATUS_OK) return status;
    if ((status = stroka_to_double(argv[4] , &b)) != STATUS_OK) return status;
    if ((status = stroka_to_double(argv[5] , &c)) != STATUS_OK) return status;

    if (eps < 0) {
        // printf("Эпсилон должен быть положительный\n");
        return STATUS_INVALID_NUMBER;
    }

    double all_koef[6][3] = {{a, b, c}, {a, c, b}, {b, a, c}, {b, c, a}, {c, a, b}, {c, b, a}};
    
    // проверка на уникальную перестановку
    for (int i = 0; i < 6; ++i) {
        int unique = 1;
        for (int j = 0; j < i; ++j) {
            if (double_equal(all_koef[i][0], all_koef[j][0], eps) && 
                double_equal(all_koef[i][1], all_koef[j][1], eps) &&
                double_equal(all_koef[i][2], all_koef[j][2], eps)) {
                    unique = 0;
                    break;
            }
        }
        if (unique) {
            printf("%.3fx^2 + %.3fx + %.3f = 0\n", all_koef[i][0], all_koef[i][1], all_koef[i][2]);
            solve_uravn(all_koef[i][0], all_koef[i][1], all_koef[i][2], eps);
        }
    }
    return STATUS_OK;
}