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
	if (src == NULL) {
		free(*dst);
		*dst = NULL;
		return 0;
	}

	size_t src_len = strlen(src) + 1;
	*dst = realloc(*dst, src_len);
	strcpy(*dst, src);

	return src_len;
}

char *str_from_file(const char *file_name){
	char *str = NULL;
	FILE *in = fopen(file_name, "rb");
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
	str[size - 1] = '\0';
	fclose(in);

	return str;
}
