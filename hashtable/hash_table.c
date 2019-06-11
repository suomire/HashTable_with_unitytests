//
// Created by ol on 5/26/2019.
//
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash_table.h"


// HT_DELETED_ITEM is used to mark a bucket containing a deleted item
static Item HT_DELETED_ITEM = {NULL, NULL};


// HT_PRIMEs are parameters in the hashing algorithm
static const int HT_PRIME_1 = 151;
static const int HT_PRIME_2 = 163;

static int ht_hash(const char *s, const int a, const int m) {
    //s - string value; a - number > 128 (ASCII), m - index in the table (m<=53)
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash += (long) pow(a, len_s - (i + 1)) * s[i];
        hash = hash % m;
    }
    return (int) hash;
}


static int ht_get_hash(const char *s, const int num_bucket, const int attempt) {
    const char hash_a = ht_hash(s, HT_PRIME_1, num_bucket);
    const char hash_b = ht_hash(s, HT_PRIME_2, num_bucket);
    return (hash_a + (attempt * (hash_b + 1))) % num_bucket;
}


Table *ht_new() {
    Table *ht = (Table *) calloc(1, sizeof(Table)); //ht--SIGTRAP (Trace/breakpoint trap), table - OK
    ht->size = 53;
    ht->count = 0;
    ht->items = (Item **) calloc((size_t) ht->size, sizeof(Item *));
    return ht;
}

int ht_insert(Table *ht, char *key, char *value) {
    size_t i1 = strlen(key);
    int index = ht_get_hash(key, ht->size, 0);
    if (ht->items[index] == NULL) {
        ht->items[index] = (Item *) calloc(1, sizeof(Item));
        if (ht->items[index] == NULL) {
            exit(EXIT_FAILURE);
        }
        ht->items[index]->key = (char *) calloc(i1 + 1, sizeof(char));
        ht->items[index]->value = (char *) calloc(i1 + 1, sizeof(char));
        strcpy(ht->items[index]->key, key);
        strcpy(ht->items[index]->value, value);
    } else if (ht->items[index]->key == NULL) {
        ht->items[index]->key = (char *) calloc(i1 + 1, sizeof(char));
        ht->items[index]->value = (char *) calloc(i1 + 1, sizeof(char));
        strcpy(ht->items[index]->key, key);
        strcpy(ht->items[index]->value, value);
    } else {
        int i = 0;
        while (ht->items[index] != NULL) {
            index = ht_get_hash(key, ht->size, i++);
        }
        ht->items[index] = (Item *) calloc(1, sizeof(Item));
        if (ht->items[index] == NULL) {
            exit(EXIT_FAILURE);
        }
        ht->items[index]->key = (char *) calloc(i1 + 1, sizeof(char));
        ht->items[index]->value = (char *) calloc(i1 + 1, sizeof(char));
        strcpy(ht->items[index]->key, key);
        strcpy(ht->items[index]->value, value);
    }
    ht->count++;
    return 1;
}

int ht_delete(Table *ht, const char *key) {
    int index = ht_get_hash(key, ht->size, 0);
    int i = 1;
    while (ht->items[index] != NULL) {
        if (ht->items[index]->key != NULL) {
            if (strcmp(ht->items[index]->key, key) == 0) {
                ht->items[index]->key = NULL;
                ht->items[index]->value = NULL;
                break;
            }
        } else {
            index = ht_get_hash(key, ht->size, i);
            i++;
        }
    }
    ht->count--;
    return 1;
}

//поиск по ключу
char *ht_search(Table *ht, const char *key) {
    int index = ht_get_hash(key, ht->size, 0);
    int i = 1;
    while (ht->items[index]->key != NULL) {
        if (strcmp(ht->items[index]->key, key) == 0) { //check equality of keys
            return ht->items[index]->value;


        } else {
            index = ht_get_hash(key, ht->size, i); //если нет, то новая попытка подстчета хэшф
            i++;
        };// изменение счетчика попыток
    }
    return NULL; //ну нет, так нет
}


int ht_del_hash_table(Table *ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->items[i] != NULL) {
            free(ht->items[i]->key);
            free(ht->items[i]->value);
            free(ht->items[i]);
        }
    }
    free(ht->items);
    free(ht);
    return 1;
}



