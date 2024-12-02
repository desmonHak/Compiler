#ifndef __HASH_TABLE1_H__
#define __HASH_TABLE1_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "../debug_c.h"
#include "list.h"
#include "hash-table.h"
#include "list.h"

// Define una estructura que incluye una lista enlazada y una tabla de hash.
typedef struct {
    List* list;
    size_t capacity;
    Entry** table;
} HashList;

// Funciones para manipular la estructura combinada.
HashList* createHashList(size_t size);
void putInList(HashList* hashList, void* value);
void putInHash(HashList* hashList, const char* key, void* value);
void* getByHash(HashList* hashList, const char* key);
void printHashList(HashList* hashList);
void freeHashList(HashList* hashList);

#endif


HashList* createHashList(size_t size) {
    HashList* hashList = (HashList*)malloc(sizeof(HashList));
    if (hashList == NULL) {
        // Manejo de error
        exit(EXIT_FAILURE);
    }

    hashList->list = createList();
    hashList->capacity = size;

    debug_calloc(Entry*, hashList->table, size, sizeof(Entry*));

    return hashList;
}

void putInList(HashList* hashList, void* value) {
    push(hashList->list, value);
}

void putInHash(HashList* hashList, const char* key, void* value) {
    size_t index = hash(key, hashList->capacity);

    Entry* entry = (Entry*)malloc(sizeof(Entry));
    if (entry == NULL) {
        // Manejo de error
        exit(EXIT_FAILURE);
    }

    entry->key = strdup(key);
    entry->value = value;
    entry->next = hashList->table[index];

    hashList->table[index] = entry;
}

void* getByHash(HashList* hashList, const char* key) {
    size_t index = hash(key, hashList->capacity);

    Entry* entry = hashList->table[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL; // Clave no encontrada
}

void printHashList(HashList* hashList) {
    printf("Lista:\n");
    printList(hashList->list);

    printf("Tabla de Hash:\n");
    for (size_t i = 0; i < hashList->capacity; i++) {
        Entry* entry = hashList->table[i];
        while (entry != NULL) {
            printf("Key: %s, PTR Value: 0x%p\n", entry->key, entry->value);
            entry = entry->next;
        }
    }
}

void freeHashList(HashList* hashList) {
    freeList(hashList->list);

    for (size_t i = 0; i < hashList->capacity; i++) {
        Entry* entry = hashList->table[i];
        while (entry != NULL) {
            Entry* temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }

    free(hashList->table);
    free(hashList);
}
#include <stdio.h>
#include <stdlib.h>


int main() {
    // Crear una estructura HashList
    HashList* hashList = createHashList(10);

    // Agregar elementos a la lista
    putInList(hashList, (void*)123);
    putInList(hashList, (void*)1);
    putInList(hashList, (void*)13);

    // Agregar elementos a la tabla de hash
    putInHash(hashList, "key1", (void*)123);

    // Obtener un valor de la tabla de hash por clave
    const char* searchKey = "key1";
    void* foundValue = getByHash(hashList, searchKey);
    if (foundValue != NULL) {
        printf("Valor encontrado para clave '%s': 0x%p\n", searchKey, foundValue);
    } else {
        printf("Clave '%s' no encontrada.\n", searchKey);
    }

    // Imprimir la estructura combinada
    printHashList(hashList);

    // Liberar memoria
    freeHashList(hashList);

    return 0;
}
