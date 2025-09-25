#include <stdio.h>
#include "functions.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Неверное число аргументов\n");
        return STATUS_INVALID_ARGC;
    }

    Status status;

    int x;
    status = stroka_to_int(argv[1], &x);    
    if (status != STATUS_OK) {
        printf("Неправильно введено число\n");
        return status;
    }

    char flag;
    status = validate_flag(argv[2], &flag);
    if (status != STATUS_OK) {
        printf("Нерпавильно введён флаг\n");
        return status;
    }


    status = STATUS_OK;
    switch (flag) {
        case 'h': status = flag_h(x); break;
        case 'p': status = flag_p(x); break;
        case 's': status = flag_s(x); break;
        case 'e': status = flag_e(x); break;
        case 'a': status = flag_a(x); break;
        case 'f': status = flag_f(x); break;
        default: status = STATUS_INVALID_FLAG;
    }

    return status;
}