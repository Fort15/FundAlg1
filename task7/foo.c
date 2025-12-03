#include "foo.h"
#include <limits.h>
#ifdef _WIN32  
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/types.h>
#endif


Status same_files(const char *file1, const char *file2) {
#ifdef _WIN32  
    BY_HANDLE_FILE_INFORMATION info1, info2;  
    HANDLE hFile1 = CreateFile(file1,   
                            GENERIC_READ,   
                            FILE_SHARE_READ,   
                            NULL,   
                            OPEN_EXISTING,   
                            FILE_ATTRIBUTE_NORMAL,   
                            NULL);  
    
    HANDLE hFile2 = CreateFile(file2,   
                            GENERIC_READ,   
                            FILE_SHARE_READ,   
                            NULL,   
                            OPEN_EXISTING,   
                            FILE_ATTRIBUTE_NORMAL,   
                            NULL);  
    
   if (hFile1 == INVALID_HANDLE_VALUE || hFile2 == INVALID_HANDLE_VALUE) {
        if (hFile1 != INVALID_HANDLE_VALUE) CloseHandle(hFile1);
        if (hFile2 != INVALID_HANDLE_VALUE) CloseHandle(hFile2);
        return STATUS_FILE_ERROR;
    }
    
    BOOL success1 = GetFileInformationByHandle(hFile1, &info1);  
    BOOL success2 = GetFileInformationByHandle(hFile2, &info2);  
    CloseHandle(hFile1);  
    CloseHandle(hFile2);  
    
    if (!success1 || !success2) {
        return STATUS_FILE_ERROR;
    }
    
    if (info1.dwVolumeSerialNumber == info2.dwVolumeSerialNumber &&  
        info1.nFileIndexHigh == info2.nFileIndexHigh &&  
        info1.nFileIndexLow == info2.nFileIndexLow) {
        return STATUS_SAME_FILES;
    }
    return STATUS_OK;
#else  
    struct stat st1, st2;
    if (stat(file1, &st1) != 0) return STATUS_OK;    
    if (stat(file2, &st2) != 0) return STATUS_OK;    
    
    if ((st1.st_dev == st2.st_dev) && (st1.st_ino == st2.st_ino)) {
        return STATUS_SAME_FILES;
    }
    return STATUS_OK;
#endif  
    return STATUS_FILE_ERROR;  
}

Status str_to_ll(const char* stroka, int base, long long* chislo) {
    const char* p = stroka;
    int sign = 1;
    if (*p == '-') {
        sign = -1;
        ++p;
    } else if (*p == '+') ++p;

    if (!*p) return STATUS_INVALID_NUMBER;

    unsigned long long result = 0;

    while (*p) {
        int digit;
        if (*p >= '0' && *p <= '9') digit = *p - '0';
        else if (*p >= 'A' && *p <= 'Z') digit = *p - 'A' + 10;
        else if (*p >= 'a' && *p <= 'z') digit = *p - 'a' + 10;
        else return STATUS_INVALID_NUMBER;

        if (digit >= base) return STATUS_INVALID_NUMBER;

        result = result * base + digit;
        if (result > LLONG_MAX) {    // == llmin не обрабатывается исходя из модуля
            return STATUS_TOO_BIG_LL;
        }
        ++p;
    }
    *chislo = (sign == 1) ? (long long)result : -(long long)result;
    return STATUS_OK;
}

Status min_base(const char* stroka, int* base) {
    if (!stroka || !base) return STATUS_INVALID_BASE;

    int max_digit = 0;
    const char* p = stroka;
    if (*p == '-' || *p == '+') p++;

    if (!*p) return STATUS_INVALID_BASE;

    while (*p) {
        int digit;
        if (*p >= '0' && *p <= '9') {
            digit = *p - '0';
        } else if (*p >= 'A' && *p <= 'Z') {
            digit = *p - 'A' + 10;
        } else if (*p >= 'a' && *p <= 'z') {
            digit = *p - 'a' + 10;
        } else {
            return STATUS_INVALID_BASE;
        }
        
        if (digit > max_digit) {
            max_digit = digit;
        }
        p++;
    }

    max_digit++;
    if (max_digit == 1) ++max_digit;
    if (max_digit < 2 || max_digit > 36) return STATUS_INVALID_BASE;

    *base = max_digit;
    
    return STATUS_OK;
}

char* normalize(char* stroka) {
    char* p = stroka;
    if (*p == '+' || *p == '-') {
        p++;
    }

    int was_negative = (stroka[0] == '-');
    
    while (*p == '0' && *(p + 1) != '\0') {
        p++;
    }
    
    if (was_negative && *p == '0' && *(p + 1) == '\0') {
        return p;
    }
    
    if (was_negative) {
        p--;
        *p = '-';
    }
    
    return p;
}