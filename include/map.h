#pragma once 
 

#ifdef MAP_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif



// Define the structure for a key-value pair
typedef struct MapEntry {
    void* key;
    void* value;
    struct MapEntry* next; // For chaining
} MapEntry;

// Define the structure for the map
typedef struct {
    MapEntry** table; // Array of pointers to MapEntry
    size_t size;      // Size of the hash table
} Map;


size_t hash(void* key, size_t size);

// Create a new map
Map* map_create(size_t size);

// Insert a key-value pair into the map
void map_insert(Map* map, void* key, void* value, int (*compare)(void*, void*));

// Retrieve a value by key
void* map_get(Map* map, void* key, int (*compare)(void*, void*));

// Delete a key-value pair from the map
void map_delete(Map* map, void* key, int (*compare)(void*, void*));

// Free the map and its entries
void map_free(Map* map);

#ifdef MAP_IMPLEMENTATION
// Hash function (simple example using pointer address)
size_t hash(void* key, size_t size) {
    return ((size_t)key) % size;
}

// Create a new map
Map* map_create(size_t size) {
    Map* map = (Map*)malloc(sizeof(Map));
    map->size = size;
    map->table = (MapEntry**)calloc(size, sizeof(MapEntry*)); // Initialize to NULL
    return map;
}

// Insert a key-value pair into the map
void map_insert(Map* map, void* key, void* value, int (*compare)(void*, void*)) {
    size_t index = hash(key, map->size);

    // Check if the key already exists
    MapEntry* entry = map->table[index];
    while (entry != NULL) {
        if (compare(entry->key, key) == 0) {
            // Key exists, update the value
            entry->value = value;
            return;
        }
        entry = entry->next;
    }

    // Key does not exist, create a new entry
    MapEntry* newEntry = (MapEntry*)malloc(sizeof(MapEntry));
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = map->table[index]; // Insert at the head of the chain
    map->table[index] = newEntry;
}

// Retrieve a value by key
void* map_get(Map* map, void* key, int (*compare)(void*, void*)) {
    size_t index = hash(key, map->size);

    // Traverse the chain
    MapEntry* entry = map->table[index];
    while (entry != NULL) {
        if (compare(entry->key, key) == 0) {
            return entry->value; // Key found, return the value
        }
        entry = entry->next;
    }

    return NULL; // Key not found
}

// Delete a key-value pair from the map
void map_delete(Map* map, void* key, int (*compare)(void*, void*)) {
    size_t index = hash(key, map->size);

    MapEntry* prev = NULL;
    MapEntry* entry = map->table[index];

    while (entry != NULL) {
        if (compare(entry->key, key) == 0) {
            // Key found, remove the entry
            if (prev == NULL) {
                // Entry is the head of the chain
                map->table[index] = entry->next;
            } else {
                // Entry is in the middle or end of the chain
                prev->next = entry->next;
            }
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

// Free the map and its entries
void map_free(Map* map) {
    for (size_t i = 0; i < map->size; i++) {
        MapEntry* entry = map->table[i];
        while (entry != NULL) {
            MapEntry* next = entry->next;
            free(entry);
            entry = next;
        }
    }
    free(map->table);
    free(map);
}

// Example comparison function for integer keys
int compare_int(void* a, void* b) {
    return *(int*)a - *(int*)b;
}


#endif