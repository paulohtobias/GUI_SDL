#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "utils/utils.h"

typedef struct Exception{
    char *message;
    void *extra_data;
}Exception;

Exception new_Exeption(char *message, ...);

Exception new_Exception_data(void *data, char *message, ...);

void exception_set_message(Exception *e, char *message, ...);

#endif //EXCEPTION_H
