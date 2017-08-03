#include <stddef.h>

#include "utils/array_list.h"

ArrayList *new_ArrayList(){
    ArrayList *list = malloc(sizeof(ArrayList));
    
    list->size = 0;
    list->first = 0;
    list->last = 0;
    list->data = malloc(LIST_MIN_SIZE * sizeof(Data));
    
    int i;
    for(i=0; i<LIST_MIN_SIZE; i++){
        list->data[i] = NULL;
    }
    list->unlimited = false;
    list->array_current_size = LIST_MIN_SIZE;
    
    return list;
}

void free_ArrayList(ArrayList *list, void (*free_data)(void *)){
    if(list_is_empty(list)){
        return;
    }
    
    int i;
    for(i=list->first; i<list->size; i++){
        if(list->data[i] != NULL){
            free_data(list->data[i]);
            list->data[i] = NULL;
        }
    }
    free(list->data);
    list->data = NULL;
    list->first = 0;
    list->last = 0;
    list->size = 0;
    
    free(list);
}

bool list_is_empty(ArrayList *list){
    return (list->size == 0);
}

void list_insert_first(ArrayList *list, Data data){
    //This whole if-else section consists in finding where to put the object
	if(!list_is_empty(list)){
        if(list->first == 0){
            int i;
            //Looking for a free space.
            for(i = list->first + 1; i < list->array_current_size && list->data[i] != NULL; i++){}
            
            if(i == list->array_current_size){
                if(list->array_current_size < LIST_MAX_SIZE){
                    list->array_current_size++;
                    list->data = realloc(list->data, list->array_current_size);
                }else{
                    printf("ArrayLista cheia!!!!\n");
                    exit(1);
                }
            }
            
            int j;
            for(j=i-1; j>=list->first; j--){
                list->data[j+1] = list->data[j];
            }
        }
    }

    list->first--;
	list->data[list->first] = data;
	list->size++;
}

void list_insert_last(ArrayList *list, Data data){
    if(list->last + 1 == list->array_current_size){
		if(list->array_current_size < LIST_MAX_SIZE){
            list->array_current_size++;
            list->data = realloc(list->data, list->array_current_size);
        }else{
            printf("ArrayLista cheia!!!!\n");
            exit(1);
        }
	}
    
    list->last++;
	list->data[list->last] = data;
	list->size++;
}

Data list_remove_first(ArrayList *list){
    Data data = NULL;

	if(!list_is_empty(list)){
		data = list->data[list->first];
		list->data[list->first] = NULL;
		list->first++;
		list->size--;
	}
	return data;
}

Data list_remove_last(ArrayList *list){
    Data data = NULL;

	if(!list_is_empty(list)){
		data = list->data[list->last];
		list->data[list->last] = NULL;
		list->last--;
		list->size--;
	}
	return data;
}

Data list_get_index(ArrayList *list, int index){
    if(list_is_empty(list) || index >= list->size){
        return NULL;
    }
    
    int i = list->first;
    int count = 0;
    while(count < index){
        do{
            i++;
        }while(list->data[i] == NULL);
        count++;
    }
    
    return list->data[i];
}

Data list_get_first(ArrayList *list){
    if(!list_is_empty(list)){
        return list->data[list->first];
    }else{
        return NULL;
    }
}

Data list_get_last(ArrayList *list){
    if(!list_is_empty(list)){
        return list->data[list->last];
    }else{
        return NULL;
    }
}
