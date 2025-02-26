#pragma once


#include <stddef.h>
#ifdef LIST_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#endif
typedef struct Node_s {
    struct Node_s * next;
	void*  data;
} Node_s;

typedef struct {
    Node_s* head;         // Pointer to the first Node_s in the list

} List_s;

void list_create(List_s * list[static 1]);
void list_free(List_s *list[static 1]);
void list_del(List_s list[static 1], void * data);
void list_ins_end(List_s list[static 1], void * data );
void list_ins_beg(List_s list[static 1], void * data );
Node_s* createNode_s(void * data );


#ifdef LIST_IMPLEMENTATION
Node_s* createNode_s(void * data) {
    Node_s* newNode_s = malloc(sizeof(Node_s));
    if (newNode_s == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode_s->data = data;

    newNode_s->next = NULL;
    return newNode_s;
}

void list_create(List_s * list[static 1]){
	(*list) = calloc(1,sizeof(List_s));
}
// Function to insert a Node_s at the beginning of the list
void list_ins_beg(List_s list[static 1], void * data) {
    Node_s* newNode_s = createNode_s(data);
    newNode_s->next = list->head;
    list->head = newNode_s;
 
}
 

// Function to insert a Node_s at the end of the list
void list_ins_end(List_s list[static 1],void * data) {
    Node_s* newNode_s = createNode_s(data);
    if (list->head == NULL) {
        list->head = newNode_s;
    } else {
        Node_s* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode_s;
    }
	 
}


// Function to delete a Node_s by value
void list_del(List_s list[static 1], void * data) {
    Node_s* temp = list->head;
    Node_s* prev = NULL;

    // If the Node_s to be deleted is the head
    if (temp != NULL && temp->data == data) {
        list->head = temp->next;
        free(temp);
        return;
    }

    // Search for the Node_s to be deleted
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }

    // If the Node_s was not found
    if (temp == NULL) {
        printf("Node_s with data %08x not found!\n", data);
        return;
    }

    // Unlink the Node_s from the list
    prev->next = temp->next;
    free(temp);
 
}

 
// Function to free the entire list
void list_free(List_s * list[static 1]) {
    Node_s* temp = (*list)->head;
    while (temp != NULL) {
        Node_s* next = temp->next;
	 
        free(temp);
        temp = next;
    }
	free((*list));
    (*list) = nullptr;
 
}

#endif
