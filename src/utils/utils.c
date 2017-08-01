#include "utils/utils.h"

char *string_format(const char *format, ...){
    char *string;
    
    va_list arg;
    va_start(arg, format);
    asprintf(&string, format, arg);
    va_end(arg);
    return string;
}
