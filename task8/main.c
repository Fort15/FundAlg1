#include "foo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int base;
    char buf[256];
    if (!fgets(buf, sizeof(buf), stdin)) {
        printf("Ошибка считывания\n");
        return 0;
    }
    Status status = validate_base(&base, buf);
    if (status != STATUS_OK) {
        printf("Неправильно задано основание системы счисления\n");
        return 0;
    }
    
    long long max_abs = -1, sign = 1;
    char stroka[256];
    char max_str[256];
    if (!fgets(stroka, sizeof(stroka), stdin)) {
        printf("Ошибка считывания\n");
        return 0;
    }
    while (strcmp(stroka, "Stop\n") && strcmp(stroka, "Stop")) {

        size_t len = strlen(stroka);
        if (len > 0 && stroka[len - 1] == '\n') {
            stroka[len - 1] = '\0';
        }

        long long chislo; 
        status = str_to_ll(stroka, base, &chislo);
        
        if (status != STATUS_OK) {
            if (status == STATUS_TOO_BIG_LL) printf("Очень большое число\n");
            else printf("Неправильно задано число\n");
            return 0;
        }

        if (llabs(chislo) > max_abs) {
            if (chislo < 0) sign = -1;
            else sign = 1;
            max_abs = llabs(chislo);
            strcpy(max_str, stroka);
        }

        if (!fgets(stroka, sizeof(stroka), stdin)) {
            printf("Ошибка считывания\n");
            return 0;
        }
    }

    if (max_abs == -1) {
        printf("Не было введено ни одного числа\n");
        return 0;
    }

    // char* norm_max_str = normalize(max_str);
    // if (sign == 1) printf("Максимальное по модулю число = %s\n", norm_max_str);
    // else printf("Максимальное по модулю число = -%s\n", norm_max_str);
    printf("Максимальное по модулю число = %lld\n", max_abs * sign);
    // printf("Максимальное по модулю число = %s\n", number_with_base(max_abs * sign, base));

    printf("В системе с основанием 9 = %s\n", number_with_base(max_abs * sign, 9));
    printf("В системе с основанием 18 = %s\n", number_with_base(max_abs * sign, 18));
    printf("В системе с основанием 27 = %s\n", number_with_base(max_abs * sign, 27));
    printf("В системе с основанием 36 = %s\n", number_with_base(max_abs * sign, 36));

    return 0;
}