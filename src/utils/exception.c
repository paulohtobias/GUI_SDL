#include "utils/exception.h"

Exception new_Exeption(char *message, ...){
    va_list arg;
    va_start(arg, message);
    Exception e = new_Exception_data(NULL, message, arg);
    va_end(arg);
    return e;
}

Exception new_Exception_data(void *data, char *message, ...){
    Exception e;
    
    va_list arg;
    va_start(arg, message);
    e.message = string_format(message, arg);
    va_end(arg);
    e.extra_data = data;
    
    return e;
}

void exception_set_message(Exception *e, char *message, ...){
    if(e->message != NULL){
        free(e->message);
    }
    va_list arg;
    va_start(arg, message);
    e->message = string_format(message, arg);
    va_end(arg);
}
