#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "utils/utils.h"

#ifndef LIST_DEFAULT_MAX_SIZE
#define LIST_DEFAULT_MAX_SIZE 300
#endif

typedef struct ArrayList{
	int first;
	int last;
	int size;
	void **data;

	int max_size;
} ArrayList;

ArrayList *new_ArrayList();

ArrayList *new_ArrayList_max_size(int max);

void free_ArrayList(ArrayList *list, void (*free_data)(void *));

int list_is_empty(ArrayList *list);

void list_insert_first(ArrayList *list, void *data);

void list_insert_last(ArrayList *list, void *data);

void *list_remove_first(ArrayList *list);

void *list_remove_last(ArrayList *list);

void *list_get_index(ArrayList *list, int index);

void *list_get_first(ArrayList *list);

void *list_get_last(ArrayList *list);

#endif //ARRAY_LIST_H

