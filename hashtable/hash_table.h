//
// Created by ol on 5/26/2019.
//

#ifndef HASHTABLE_HASH_TABLE_H
#define HASHTABLE_HASH_TABLE_H

typedef struct ht_item Item;
struct ht_item {
    char *key;
    char *value;
};

typedef struct _table {
    int size;
    int count;
    Item **items;

} Table;

Table *ht_new();

int ht_insert(Table *ht, char *key, char *value);

int ht_delete(Table *ht, const char *key);

char *ht_search(Table *ht, const char *key);

int ht_del_hash_table(Table *ht);


#endif //HASHTABLE_HASH_TABLE_H
