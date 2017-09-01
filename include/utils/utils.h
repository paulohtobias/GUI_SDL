#ifndef UTILS_H
#define UTILS_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef TYPE_BOOL
#define TYPE_BOOL
    typedef int bool;
    #define false 0
    #define true 1
#endif //MOUSE_BOOL

#define MIN(x, y) (x<y)?x:y
#define MAX(x, y) (x>y)?x:y

char *string_format(const char *format, ...);

void string_change(char **dst, const char *src);

#endif //UTILS_H

