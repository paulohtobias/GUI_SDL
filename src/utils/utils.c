#include "utils/utils.h"

char *string_format(const char *format, ...){
    char *string;
    
    va_list arg;
    va_start(arg, format);
    asprintf(&string, format, arg);
    va_end(arg);
    return string;
}

void *_cast(size_t size, void *super_object){
    void *obj = malloc(size);
    return memcpy(obj, super_object, size);
}
