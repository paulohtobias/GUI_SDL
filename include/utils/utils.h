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

char *string_format(const char *format, ...);
    
/**
 * Convert an "object" of an "extended class" to an "object" of a "super class"
 * indicated by <code>Type</code>.
 * 
 * @param Type any data type
 * @param object an "object" of the "extended class" to be casted
 * @return a variable of type <code>Type</code>
 */
#define cast(Type, object) _cast(sizeof(Type), object)
void * _cast(size_t size, void *super_object);

#endif //UTILS_H

