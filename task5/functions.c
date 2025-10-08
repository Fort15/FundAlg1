#include "functions.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

Status validate_flag(const char *stroka, char *flag, int *have_n) {
    if (!stroka || !flag || !have_n) return STATUS_INVALID_FLAG;
    if (stroka[0] != '-' && stroka[0] != '/') return STATUS_INVALID_FLAG;

    char f;
    if (stroka[1] == 'n') {
        if (stroka[3] != '\0') return STATUS_INVALID_FLAG;
        f = stroka[2];
        *have_n = 1;
    } else {
        if (stroka[2] != '\0') return STATUS_INVALID_FLAG;
        f = stroka[1];
    }

    switch (f) {
        case 'd': case 'i': case 's': case 'a':
            *flag = f;
            return STATUS_OK;
        default:
            return STATUS_INVALID_FLAG;
    }
}

Status out_file_path(const char *path, char **output) {
    if (!path) return STATUS_INVALID_FILE;

    const char *filename = strchr(path, '/');
    if (!filename) filename = path;
    else filename++;

    size_t len_out = strlen("out_") + strlen(filename) + 1;
    char *out_path = malloc(len_out * sizeof(char));
    if (!out_path) return STATUS_MEMORY_FAILED;

    strcpy(out_path, "out_");
    strcat(out_path, filename);
    *output = out_path;
    return STATUS_OK;
}

Status flag_d(FILE *in, FILE *out) {
    int c;
    while ((c = fgetc(in)) != EOF) {
        if (!(c >= '0' && c <= '9')) fputc(c, out);
    }
    return STATUS_OK;
}

Status flag_i(FILE *in, FILE *out) {
    int c;
    int k = 0;

    while ((c = fgetc(in)) != EOF) {
        if (c == '\n') {
            fprintf(out, "%d\n", k);
            k = 0;
            continue;
        }
        c = tolower(c);
        if (c >= 'a' && c <= 'z') ++k;
    }

    if (k != 0) {
        fprintf(out, "%d\n", k);
        k = 0;
    }
    return STATUS_OK;
}

Status flag_s(FILE *in, FILE *out) {
    int c;
    int k = 0;

    while ((c = fgetc(in)) != EOF) {
        if (c == '\n') {
            fprintf(out, "%d\n", k);
            k = 0;
            continue;
        }
        if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'
            || c >= '0' && c <= '9' || c == ' ')) ++k;
    }

    if (k != 0) {
        fprintf(out, "%d\n", k);
        k = 0;
    }
    return STATUS_OK;
}

Status flag_a(FILE *in, FILE *out) {
    int c;
    while ((c = fgetc(in)) != EOF) {
        if (isdigit(c)) fputc(c, out);
        else {
            fprintf(out, "%X", c);
        }
    }
    return STATUS_OK;
}