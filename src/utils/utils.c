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
		free(*dst);
		*dst = NULL;
	}

	*dst = malloc(strlen(src) + 1);
	if(*dst == NULL){
		printf("*dst = malloc(strlen(src) + 1);\n");
		exit(1);
	}
	strcpy(*dst, src);
}

char *str_from_file(const char *file_name){
	char *str = NULL;
    FILE *in = fopen(file_name, "r");
    if(in == NULL){
        return NULL;
	}

    fseek(in, 0, SEEK_END);
    int size = ftell(in) + 1;
    rewind(in);
    str = malloc(size);
	if(str == NULL){
		return NULL;
	}
    fread(str, 1, size, in);
    fclose(in);

    return str;
}
