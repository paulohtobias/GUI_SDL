#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "utils/utils.h"

typedef void* Data;

#ifndef LIST_MIN_SIZE
    #define LIST_MIN_SIZE 50
#endif

#ifndef LIST_MAX_SIZE
    #define LIST_MAX_SIZE 300
#endif

typedef struct ArrayList{
    int first;
    int last;
    int size;
    Data *data;
    
    bool unlimited;
    int array_current_size;
}ArrayList;

ArrayList *new_ArrayList();

void free_ArrayList(ArrayList *list, void (*free_data)(void *));

bool list_is_empty(ArrayList *list);

void list_insert_first(ArrayList *list, Data data);

void list_insert_last(ArrayList *list, Data data);

Data list_remove_first(ArrayList *list);

Data list_remove_last(ArrayList *list);

Data list_get_index(ArrayList *list, int index);

Data list_get_first(ArrayList *list);

Data list_get_last(ArrayList *list);

#endif //ARRAY_LIST_H

