#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

typedef enum {
    STATUS_OK,
    STATUS_INVALID_ARGC,    // неверное число аргументов
    STATUS_INVALID_FLAG,    // неверный флаг
    STATUS_INVALID_FILE,
    STATUS_MEMORY_FAILED,
    STATUS_SAME_FILES,
} Status;


Status same_files(const char *file1, const char *file2);
Status out_file_path(const char *path, char **output);
Status validate_flag(const char *stroka, char *flag, int *have_n);
Status flag_d(FILE *in, FILE *out);
Status flag_i(FILE *in, FILE *out);
Status flag_s(FILE *in, FILE *out);
Status flag_a(FILE *in, FILE *out);
#endif