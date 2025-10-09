#include "foo.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Неверное число аргументов\n");
        return 0;
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("Не удалось открыть входной файл\n");
        return 0;
    }

    FILE *out = fopen(argv[2], "w");
    if (!out) {
        printf("Не удалось открыть выходной файл\n");
        fclose(in);
        return 0;
    }

    int c;
    char buf[256];
    int ind = 0;

    while ((c = fgetc(in)) != EOF) {
        if (c == '+' || c == '-' || (c >= '0' && c <= '9') || 
            (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                if (ind < sizeof(buf) - 1) {
                    buf[ind++] = (char)c;
                }
        } else {
            if (ind > 0) {
                if (ind >= sizeof(buf) - 1) {
                    fprintf(out, "Очень большое число\n");
                } else {
                    buf[ind] = '\0';

                    char* input_number = normalize(buf);
                    int base;
                    Status status = min_base(input_number, &base);
                    if (status != STATUS_OK) {
                        fprintf(out, "Неправильная система счисления\n");
                    } else {
                        long long input_number10;
                        status = str_to_ll(input_number, base, &input_number10);
                        if (status == STATUS_TOO_BIG_LL) {
                            fprintf(out, "%s Очень большое число\n", input_number);
                        } else if (status == STATUS_INVALID_NUMBER) {
                            fprintf(out, "%s Некорректное число\n", input_number);
                        } else {
                            fprintf(out, "%s %d %lld\n", input_number, base, input_number10);
                        }
                    }
                }
                ind = 0;
            }
        }
    }

    if (ind > 0) {
        if (ind >= sizeof(buf) - 1) {
            fprintf(out, "Очень большое число\n");
        } else {
            buf[ind] = '\0';
            char* input_number = normalize(buf);
            int base;
            Status status = min_base(input_number, &base);
            
            if (status != STATUS_OK) {
                fprintf(out, "%s Некорректное число\n", input_number);
            } else {
                long long input_number10;
                status = str_to_ll(input_number, base, &input_number10);
                if (status == STATUS_TOO_BIG_LL) {
                    fprintf(out, "%s Очень большое число\n", input_number);
                } else if (status == STATUS_INVALID_NUMBER) {
                    fprintf(out, "%s Некорректное число\n", input_number);
                } else {
                    fprintf(out, "%s %d %lld\n", input_number, base, input_number10);
                }
            }
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}