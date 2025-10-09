#include <stdio.h>
#include "functions.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Неверное число аргументов\n");
        return 0;
    }

    Status status;
    char flag;
    status = validate_flag(argv[1], &flag);    
    if (status != STATUS_OK) {
        printf("Нерпавильно введён флаг\n");
        return 0;
    }

    status = STATUS_OK;
    switch (flag) {
        case 'q': status = flag_q(argc, argv); break;
        case 'm': status = flag_m(argc, argv); break;
        case 't': status = flag_t(argc, argv); break; 
        default: status = STATUS_INVALID_FLAG;
    }
    switch (status) {
        case STATUS_INVALID_NUMBER:
            printf("Неправильно введено число\n");
            break;
        case STATUS_TOO_BIG_INT:
            printf("Большое число\n");
            break;
        case STATUS_INVALID_ARGC:
            printf("Неверное число аргументов\n");
            break;
        case STATUS_INVALID_FLAG:
            printf("Неправильный флаг\n");
            break;
        case STATUS_OK:
            break;
        default:
            printf("Неизвестная ошибка\n");
            break;
    }
    return 0;
}