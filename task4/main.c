#include <stdio.h>
#include "constants.h"
#include <stdlib.h>


int main() {
    char line[256];
    
    printf("1.e 2.pi 3.ln2 4.sqrt(2) 5.γ\n");
    printf("Введите число от 1 до 5: ");
    
    if (!fgets(line, sizeof(line), stdin)) {
        printf("Ошибка ввода\n");
        return 0;
    }
    
    int x;
    char *endptr;
    long val = strtol(line, &endptr, 10);
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n') {
        endptr++;
    }
    
    if (endptr == line || *endptr != '\0' || val < 1 || val > 5) {
        printf("Введите число от 1 до 5\n");
        return 0;
    }
    x = (int)val;
    
    printf("Введите точность (eps > 0): ");
    if (!fgets(line, sizeof(line), stdin)) {
        printf("Ошибка ввода\n");
        return 0;
    }
    
    double eps = strtod(line, &endptr);
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n') {
        endptr++;
    }

    if (endptr == line || *endptr != '\0') {
        printf("Некорректный ввод\n");
        return 0;
    }
    if (eps <= 0) {
    printf("Эпсилон должен быть положительным числом\n");
    return 0;
    }
    printf("\nРезультаты вычислений:\n");
    printf("---------------------\n");
    Status status;
    double result;
    switch (x) {
        case 1: // e
            status = e_lim(eps, &result);
            if (status == STATUS_OK) printf("Предел: %.10f\n", result);
            status = e_ryad(eps, &result);
            if (status == STATUS_OK) printf("Ряд:    %.10f\n", result);
            status = e_newton(eps, &result);
            if (status == STATUS_OK) printf("Уравнение: %.10f\n", result);
            break;
        
        case 2: // pi
            status = pi_lim(eps, &result);
            if (status == STATUS_OK) printf("Предел: %.10f\n", result);
            status = pi_ryad(eps, &result);
            if (status == STATUS_OK) printf("Ряд:    %.10f\n", result);
            status = pi_newton(eps, &result);
            if (status == STATUS_OK) printf("Уравнение: %.10f\n", result);
            break;

        case 3: // ln2
            status = ln2_lim(eps, &result);
            if (status == STATUS_OK) printf("Предел: %.10f\n", result);
            status = ln2_ryad(eps, &result);
            if (status == STATUS_OK) printf("Ряд:    %.10f\n", result);
            status = ln2_newton(eps, &result);
            if (status == STATUS_OK) printf("Уравнение: %.10f\n", result);
            break;

        case 4: // sqrt2
            status = sqrt2_lim(eps, &result);
            if (status == STATUS_OK) printf("Предел: %.10f\n", result);
            status = sqrt2_ryad(eps, &result);
            if (status == STATUS_OK) printf("Ряд:    %.10f\n", result);
            status = sqrt2_newton(eps, &result);
            if (status == STATUS_OK) printf("Уравнение: %.10f\n", result);
            break;

        case 5: // gamma
            status = y_lim(eps, &result);
            if (status == STATUS_OK) printf("Предел: %.10f\n", result);
            status = y_ryad(eps, &result);
            if (status == STATUS_OK) printf("Ряд:    %.10f\n", result);
            status = y_newton(eps, &result);
            if (status == STATUS_OK) printf("Уравнение: %.10f\n", result);
            break;

        default:
            printf("Введите число от 1 до 5\n");
            return 0;
    }

    if (status != STATUS_OK) {
        printf("Ошибка %d\n", status);
        return 0;
    }

    return 0;
}