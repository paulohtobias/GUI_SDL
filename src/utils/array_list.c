#include <stddef.h>

#include "utils/array_list.h"

ArrayList *new_ArrayList(){
	return new_ArrayList_max_size(LIST_DEFAULT_MAX_SIZE);
}

ArrayList *new_ArrayList_max_size(int max){
	ArrayList *list = malloc(sizeof(ArrayList));
	if(list == NULL){
		printf("ArrayList *list = malloc(sizeof(ArrayList));\n");
		exit(1);
	}

	list->size = 0;
	list->first = 0;
	list->last = 0;
	list->data = malloc(max * sizeof(void *));
	if(list->data == NULL){
		printf("list->data = malloc(max * sizeof(void *));\n");
		exit(1);
	}

	int i;
	for(i = 0; i < max; i++){
		list->data[i] = NULL;
	}
	list->max_size = max;

	return list;
}

void free_ArrayList(ArrayList *list, void (*free_data)(void *)){
	if(list_is_empty(list)){
		return;
	}

	int i;
	for(i = list->first; i < list->size; i++){
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
	return(list->size == 0);
}

void list_insert_first(ArrayList *list, void *data){
	//This whole if-else section consists in finding where to put the object
	if(!list_is_empty(list)){
		if(list->first == 0){
			int i;
			//Looking for a free space.
			for(i = list->first + 1; i < list->max_size && list->data[i] != NULL; i++){
			}

			if(i == list->max_size){
				printf("ArrayLista cheia!!!!\n");
				exit(1);
			}

			int j;
			for(j = i - 1; j >= list->first; j--){
				list->data[j + 1] = list->data[j];
			}
		}
		list->first--;
	}

	list->data[list->first] = data;
	list->size++;
}

void list_insert_last(ArrayList *list, void *data){
	if(!list_is_empty(list)){
		if(list->last + 1 == list->max_size){
			printf("ArrayList cheia!!!!\n");
			exit(1);
		}
		list->last++;
	}

	list->data[list->last] = data;
	list->size++;
}

void *list_remove_first(ArrayList *list){
	void *data = NULL;

	if(!list_is_empty(list)){
		data = list->data[list->first];
		list->data[list->first] = NULL;
		list->first++;
		list->size--;
	}
	return data;
}

void *list_remove_last(ArrayList *list){
	void *data = NULL;

	if(!list_is_empty(list)){
		data = list->data[list->last];
		list->data[list->last] = NULL;
		list->last--;
		list->size--;
	}
	return data;
}

void *list_get_index(ArrayList *list, int index){
	if(list_is_empty(list) || index > list->size){
		return NULL;
	}

	//TO-DO
	return list->data[index];

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

void *list_get_first(ArrayList *list){
	if(!list_is_empty(list)){
		return list->data[list->first];
	}else{
		return NULL;
	}
}

void *list_get_last(ArrayList *list){
	if(!list_is_empty(list)){
		return list->data[list->last];
	}else{
		return NULL;
	}
}
