#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct {
    char* key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair* table[TABLE_SIZE];
} HashTable;

HashTable* createHashTable() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) {
        perror("Failed to create hash table");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

unsigned int hash(char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

void insert(HashTable* ht, char* key, int value) {
    unsigned int index = hash(key);
    while (ht->table[index] != NULL) {
        // Linear probing: Move to the next slot if collision occurs
        index = (index + 1) % TABLE_SIZE;
    }
    KeyValuePair* kvp = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    if (!kvp) {
        perror("Failed to insert key-value pair");
        exit(EXIT_FAILURE);
    }
    kvp->key = strdup(key);
    kvp->value = value;
    ht->table[index] = kvp;
}

int get(HashTable* ht, char* key) {
    unsigned int index = hash(key);
    while (ht->table[index] != NULL) {
        KeyValuePair* kvp = ht->table[index];
        if (strcmp(kvp->key, key) == 0) {
            return kvp->value; // Found the key
        }
        // Linear probing: Move to the next slot to check
        index = (index + 1) % TABLE_SIZE;
    }
    return -1; // Key not found
}

void freeHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        KeyValuePair* kvp = ht->table[i];
        if (kvp) {
            free(kvp->key);
            free(kvp);
        }
    }
    free(ht);
}

#endif  // HASH_TABLE_H
