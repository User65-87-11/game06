#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

constexpr static int max_size = 512;
constexpr static int max_size_bits_idx = 0b0000'0001'1111'1111;
constexpr static int max_size_bits_blocks = 0b1111'1110'0000'0000;

typedef struct Array_node{
	struct Array_node * next;
	void** data;
} Array_node;


typedef struct Array_list{
	Array_node * head;
	size_t length;
} Array_list;


void * alist_at(Array_list a[static 1], size_t ind){
	if(ind >= a->length){
		printf("index[%i] >= array.length[%i] \n",ind,a->length);
		exit(1);
	}
 
	size_t node_idx = ind & max_size_bits_blocks;
	size_t data_idx = ind & max_size_bits_idx;
	Array_node *n =a->head;
	while(node_idx > 0){
		n = n->next;
		node_idx --;
	}

	return &n->data[data_idx];
}
Array_node * anode_create();
void alist_append(Array_list a[static 1],void * data){
	size_t len = a->length;
	size_t node_idx = len & max_size_bits_blocks;
	size_t data_idx = len & max_size_bits_idx;
	Array_node *n =a->head;
	while(node_idx > 0){
		n = n->next;
		node_idx --;
	}
	if(n == nullptr){
		n = anode_create();
		n->next =  a->head;
		a->head = n;
	}
	n->data[a->length]  = data;
	a->length++;
}

Array_node * anode_create(){
	Array_node *ret = calloc(1, sizeof(Array_node));
	(*ret).data = malloc(sizeof(void *)*max_size );
	return  ret;
};
void anode_free(Array_node n [static 1]){
	free(n->data);
	free(n);
 
};

void alist_create( Array_list* a[static 1]){

	(* a) = calloc(1, sizeof(Array_list));
	// Array_node * node= anode_create();
	// node->next = (* a)->head;
	// (* a)->head = node;
 
};

void alist_free(Array_list *a [static 1]){
 
	Array_node* temp = (*a)->head;
	while (temp != NULL) {
        Array_node* next = temp->next;
		anode_free(temp);
        temp = next;
    }
	free( (*a));
	(*a) = nullptr;
};
