#ifndef __HASH_TABLE_c__
#define __HASH_TABLE_c__

#include "hash-table.h"

unsigned long hash(const char *str, size_t size)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(unsigned long, hash)
                    TYPE_DATA_DBG(const char *, "str = %s")
                        TYPE_DATA_DBG(size_t, "size = %zu")
                            END_TYPE_FUNC_DBG,
                str, size);
#endif
    if (str == (const char *)NULL)
        return 0;

    size_t hash = 0x1505;
    int c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c  djb2 hash algorithm */
    }

    return hash % size;
}

void *removeFromHashTable(HashTable *hashTable, const char *key)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void *, removeFromHashTable)
                    TYPE_DATA_DBG(HashTable *, "hashTable = %p")
                        TYPE_DATA_DBG(const char *, "key = %s")
                            END_TYPE_FUNC_DBG,
                hashTable, key);
#endif

    if (hashTable == NULL || key == NULL)
    {
#ifdef __ERROR_H__
        debug_set_level(DEBUG_LEVEL_WARNING);
        DEBUG_PRINT(DEBUG_LEVEL_WARNING, "removeFromHashTable(HashTable* hashTable = %p, const char* key = %p)\n", hashTable, key);
#endif
        return NULL;
    }

    size_t index = hash(key, hashTable->capacity);

    Entry *prev = NULL;
    Entry *current = hashTable->table[index];

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            // Key found
            if (prev == NULL)
            {
                // If it's the first entry in the list
                hashTable->table[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            void *value = current->value;
            free(current->key);
            free(current);
            hashTable->size--;

            return value;
        }

        prev = current;
        current = current->next;
    }

    return NULL; // Key not found
}

HashTable *createHashTable(size_t size)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(HashTable, createHashTable)
                    TYPE_DATA_DBG(size_t, "size = %zu")
                        END_TYPE_FUNC_DBG,
                size);
#endif
    // HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    HashTable *hashTable;
    debug_malloc(HashTable, hashTable, sizeof(HashTable));
    hashTable->size = 0;
    hashTable->capacity = size;
    // hashTable->table = (Entry**)calloc(size, sizeof(Entry*));
    debug_calloc(Entry *, hashTable->table, size, sizeof(Entry *));
    return hashTable;
}

void put(HashTable *hashTable, const char *key, void *value)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, put)
                    TYPE_DATA_DBG(HashTable *, "hashTable = %p")
                        TYPE_DATA_DBG(const char *, "key = %s")
                            TYPE_DATA_DBG(void *, "value = %p")
                                END_TYPE_FUNC_DBG,
                hashTable, key, value);
#endif
#ifdef __ERROR_H__
    if (hashTable == NULL)
    {
        debug_set_level(DEBUG_LEVEL_WARNING);
        DEBUG_PRINT(DEBUG_LEVEL_WARNING, "#{FG:cyan}put#{FG:white}(#{FG:lred}HashTable#{FG:white}* hashTable = NULL(%p), const char* key = %s, void* value = %p)\n", hashTable, key, value);
        return;
    }
    if (key == (const char *)NULL)
    {
        debug_set_level(DEBUG_LEVEL_WARNING);
        DEBUG_PRINT(DEBUG_LEVEL_WARNING, "#{FG:cyan}put#{FG:white}(#{FG:lred}HashTable#{FG:white}* hashTable = %p, const char* key = NULL(%s), void* value = %p)\n", hashTable, key, value);
        return;
    }
    if (key == value)
    {
        debug_set_level(DEBUG_LEVEL_WARNING);
        DEBUG_PRINT(DEBUG_LEVEL_WARNING, "#{FG:cyan}put#{FG:white}(#{FG:lred}HashTable#{FG:white}* hashTable = %p, const char* key = %s, void* value = NULL(%p))\n", hashTable, key, value);
        return;
    }
#else
    if (hashTable == NULL || key == (const char *)NULL || value == NULL)
        return;
#endif

    size_t index = hash(key, hashTable->capacity);
    // printf("put: %zu\n", index);

    // Entry* entry = (Entry*)malloc(sizeof(Entry));
    Entry *entry;
    debug_malloc(Entry, entry, sizeof(Entry));

    entry->key = strdup(key);
    entry->value = value;
    entry->next = NULL;

    if (hashTable->table[index] == NULL)
    {
        hashTable->table[index] = entry;
        hashTable->size++;
    }
    else
    {
        Entry *current = hashTable->table[index];
        while (current->next != NULL)
        {
            if (strcmp(current->key, key) == 0)
            {
                current->value = value;
                free(entry->key);
                free(entry);
                return;
            }
            current = current->next;
        }
        current->next = entry;
    }

    // Check if table needs to be resized
    if (hashTable->size >= hashTable->capacity)
    {
        size_t newSize = hashTable->capacity * 2;
        // Entry** newTable = (Entry**)calloc(newSize, sizeof(Entry*));
        Entry **newTable;
        debug_calloc(Entry *, newTable, 1, sizeof(Entry *));

        // Rehash and reinsert existing elements
        for (size_t i = 0; i < hashTable->capacity; i++)
        {
            Entry *entry = hashTable->table[i];
            while (entry != NULL)
            {
                Entry *next = entry->next;
                size_t newIndex = hash(entry->key, newSize);
                entry->next = newTable[newIndex];
                newTable[newIndex] = entry;
                entry = next;
            }
        }

        free(hashTable->table);
        hashTable->table = newTable;
        hashTable->capacity = newSize;
    }
}
void updateValue(HashTable *hashTable, const char *key, void *newValue)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, updateValue)
                    TYPE_DATA_DBG(HashTable *, "hashTable = %p")
                        TYPE_DATA_DBG(const char *, "key = %s")
                            TYPE_DATA_DBG(void *, "newValue = %p")
                                END_TYPE_FUNC_DBG,
                hashTable, key, newValue);
#endif

    /*
     *
     *  Verificar si la clave existe antes de modificarla
     *
     */

    if (hashTable == NULL || key == NULL || newValue == NULL)
    {
#ifdef __ERROR_H__
        debug_set_level(DEBUG_LEVEL_WARNING);
        DEBUG_PRINT(DEBUG_LEVEL_WARNING, "updateValue(HashTable* hashTable = %p, const char* key = %s, void* newValue = %p)\n", hashTable, key, newValue);
#endif
        return;
    }

    size_t index = hash(key, hashTable->capacity);
    for (Entry *current = hashTable->table[index]; current != NULL; current = current->next)
    {
        // printf("Comparando con clave en la lista: '%s'\n", current->key);
        if (strcmp(current->key, key) == 0)
        {
            // Key found, update the value
            current->value = newValue;
            return;
        }
    }
}

bool containsKey(HashTable *hashTable, const char *key)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, containsKey)
                    TYPE_DATA_DBG(HashTable *, "hashTable = %p")
                        TYPE_DATA_DBG(const char *, "key = %s")
                            END_TYPE_FUNC_DBG,
                hashTable, key);
#endif
    /*
     *
     *  Buscar un valor en la tabla hash
     *
     */

    if (hashTable == NULL || key == NULL)
    {
#ifdef __ERROR_H__
        debug_set_level(DEBUG_LEVEL_WARNING);
        DEBUG_PRINT(DEBUG_LEVEL_WARNING, "containsKey(HashTable* hashTable = %p, const char* key = %p)\n", hashTable, key);
#endif
        return false;
    }

    size_t index = hash(key, hashTable->capacity);

    Entry *current = hashTable->table[index];

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return true; // Key found
        }

        current = current->next;
    }

    return false; // Key not found
}

void *get(HashTable *hashTable, const char *key)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void *, get)
                    TYPE_DATA_DBG(HashTable *, "hashTable = %p")
                        TYPE_DATA_DBG(const char *, "key = %s")
                            END_TYPE_FUNC_DBG,
                hashTable, key);
#endif

    if (hashTable == NULL)
    {
#ifdef __ERROR_H__
        debug_set_level(DEBUG_LEVEL_WARNING);
        DEBUG_PRINT(DEBUG_LEVEL_WARNING, "get(HashTable* hashTable = NULL(%p), const char* key = %p)\n", hashTable, key);
#endif
        return NULL;
    }
    if (key == NULL)
    {
#ifdef __ERROR_H__
        debug_set_level(DEBUG_LEVEL_WARNING);
        DEBUG_PRINT(DEBUG_LEVEL_WARNING, "get(HashTable* hashTable = %p, const char* key = NULL(%p))\n", hashTable, key);
#endif
        return NULL;
    }

    size_t index = hash(key, hashTable->capacity);
    Entry *entry = hashTable->table[index];
    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
        {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL; // Key not found
}

void printHashTable(HashTable *hashTable)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, printHashTable)
                    TYPE_DATA_DBG(HashTable *, "hashTable = %p")
                        END_TYPE_FUNC_DBG,
                hashTable);
#endif
    if (hashTable == NULL)
    {
#ifdef DEBUG_ENABLE
        debug_set_level(DEBUG_LEVEL_INFO);
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "printHashTable: NULL(%p)\n", hashTable);
#endif
        return;
    }

    for (size_t i = 0; i < hashTable->capacity; i++)
    {
        Entry *entry = hashTable->table[i];
        while (entry != NULL)
        {
            printf("Key: %s, PTR Value: 0x%p\n", entry->key, entry->value);
            entry = entry->next;
        }
    }
}

void freeHashTable(HashTable *hashTable)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, freeHashTable)
                    TYPE_DATA_DBG(HashTable *, "hashTable = %p")
                        END_TYPE_FUNC_DBG,
                hashTable);
#endif
    if (hashTable == NULL)
    {
#ifdef DEBUG_ENABLE
        debug_set_level(DEBUG_LEVEL_INFO);
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "printHashTable: NULL(%p)\n", hashTable);
#endif
        return;
    }
    for (size_t i = 0; i < hashTable->size; i++)
    {
        Entry *entry = hashTable->table[i];
        while (entry != NULL)
        {
            Entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
        hashTable->table[i] = NULL; // Set the table slot to NULL after freeing entries
    }
}

#endif