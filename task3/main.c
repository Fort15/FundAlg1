#include <stdio.h>
#include "functions.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Неверное число аргументов\n");
        return STATUS_INVALID_ARGC;
    }

    Status status;
    char flag;
    status = validate_flag(argv[1], &flag);    
    if (status != STATUS_OK) {
        printf("Нерпавильно введён флаг\n");
        return status;
    }

    status = STATUS_OK;
    switch (flag) {
        case 'q': status = flag_q(argc, argv); break;
        case 'm': status = flag_m(argc, argv); break;
        case 't': status = flag_t(argc, argv); break; 
        default: status = STATUS_INVALID_FLAG;
    }

    return status;
}