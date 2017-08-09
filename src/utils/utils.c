#include "utils/utils.h"

char *string_format(const char *format, ...){
    char *string;
    
    va_list arg;
    va_start(arg, format);
    asprintf(&string, format, arg);
    va_end(arg);
    return string;
}

void string_change(char **dst, const char *src){
    if(*dst != NULL){
        free(dst);
        *dst = NULL;
    }
    
    *dst = malloc(sizeof(strlen(src)));
    if(*dst == NULL){
        printf("*dst = malloc(sizeof(strlen(src)));\n");
        exit(1);
    }
    strcpy(*dst, src);
}