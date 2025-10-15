#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char* argv[]) { 
    if (argc < 3 || argc > 4) {
        printf("Неверное число аргументов\n");
        return 0;   
    }

    int have_n = 0;
    char flag;
    Status status = validate_flag(argv[1], &flag, &have_n);
    if (status != STATUS_OK) {
        printf("Нерпавильно введён флаг\n");
        return 0;
        // return status;
    }

    const char *input_path = argv[2];
    char *output_path = NULL;
    char *temp_path = NULL;

    if (have_n) {
        if (argc != 4) {
            printf("Неверное число аргументов\n");
            return 0;
        }
        output_path = argv[3];
    } else {
        if (argc != 3) {
            printf("Неверное число аргументов\n");
            return STATUS_INVALID_ARGC;
        }
        status = out_file_path(input_path, &temp_path);
        if (status != STATUS_OK) {
            printf("Ошибка создания выходного файла\n");
            return 0;
        }
        output_path = temp_path;
    }

    int output_exists = (access(output_path, F_OK) == 0);
    if (output_exists) {
        Status same_status = same_files(input_path, output_path);
        if (same_status == STATUS_SAME_FILES) {
            printf("Ошибка: входной и выходной файлы совпадают, риск затирания данных.\n");
            if (temp_path) free(temp_path);
            return 0;
        }
    }
    FILE *input_file = fopen(input_path, "r");
    if (!input_file) {
        printf("Ошибка при открытии входного файла\n");
        if (temp_path) free(temp_path);
        return 0;
    }

    FILE *output_file = fopen(output_path, "w");
    if (!output_file) {
        printf("Ошибка при открытии выходного файла\n");
        fclose(input_file);
        if (temp_path) free(temp_path);
        return 0;
    }

    status = STATUS_OK;
    switch (flag) {
        case 'd': status = flag_d(input_file, output_file); break;
        case 'i': status = flag_i(input_file, output_file); break;
        case 's': status = flag_s(input_file, output_file); break;
        case 'a': status = flag_a(input_file, output_file); break;
        default: status = STATUS_INVALID_FLAG;
    }


    fclose(input_file);
    fclose(output_file);
    if (temp_path) free(temp_path);
    return 0;
}
