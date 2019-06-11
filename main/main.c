#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash_table.h"

#define MAX_WORD_LENGTH 150
#define MAX_LINES 53

int main(int argc, char *argv[]) {
    char **inputKeys = NULL;
    char **inputValues = NULL;

    for (int j = 1; j < 3; j++) {
        int nlines1 = 0;

        //from i = 1 cmd arguments begin
        FILE *fp_keys = fopen(argv[j], "r");
        char **inputFile, *bufferKeys;
        int max_lines, c, buflen, bufpos, end_of_line;

        if (argc < 4) {
            printf("There is no enough arguments\n");
            exit(EXIT_FAILURE);
        }
        max_lines = MAX_LINES;

        inputFile = (char **) malloc(max_lines * sizeof(char *));

        if (fp_keys == 0) {
            fprintf(stderr, "Can't open file\n");
            exit(EXIT_FAILURE);
        } else {
            bufpos = 0;
            buflen = MAX_WORD_LENGTH;
            bufferKeys = (char *) malloc(buflen * sizeof(char *));

            c = 0;
            while (c != EOF) {
                end_of_line = 0;
                c = fgetc(fp_keys);
                if (c == EOF || c == '\n' || c == '\r') {
                    end_of_line = 1;
                    /*Discard this character.-------? */

                } else {
                    /*Put this character in the buffer.
                     * But check if we have enough memory first!
                     * Leave room for the null character at the end. */

                    if (bufpos >= buflen - 1) {
                        buflen += MAX_WORD_LENGTH;
                        bufferKeys = (char *) realloc(bufferKeys, buflen * sizeof(char));

                    }
                    bufferKeys[bufpos] = c;
                    bufpos++;
                }
                if (end_of_line) {
                    /*Remember this line and get a new buffer.
                     * Check if we need more memory. */

                    if (nlines1 >= max_lines) {
                        max_lines += MAX_LINES;
                        inputFile = (char **) realloc(inputFile, max_lines * sizeof(char *));

                    }

                    bufferKeys[bufpos++] = 0;
                    inputFile[nlines1] = bufferKeys;
                    nlines1++;
                    bufpos = 0;
                    buflen = MAX_LINES;
                    bufferKeys = (char *) malloc(buflen * sizeof(char *));
                }
            }
        }
        if (j == 1) {
            inputKeys = (char **) malloc(nlines1 * sizeof(char *));
            for (int i = 0; i < nlines1; i++) {
                inputKeys[i] = inputFile[i];
            }
        } else {
            inputValues = (char **) malloc(nlines1 * sizeof(char *));
            for (int i = 0; i < nlines1; i++) {
                inputValues[i] = inputFile[i];
            }
        }
        fclose(fp_keys);
    }

    FILE *f = fopen(argv[3], "w");
    Table *ht = ht_new();

    for (int j = 0; j < 25; j++) {
        ht_insert(ht, inputKeys[j], inputValues[j]);
        //printf("%s, %s \n", inputKeys[j], ht_search(ht, inputKeys[j]));
    }
    fprintf(f, "Hash table from input files: \n");
    printf("Hash table from input files: \n");
    for (int i = 0; i < ht->size; i++) {
        if (ht->items[i] != NULL) {
            printf("%i %s %s\n", i, ht->items[i]->key, ht->items[i]->value);
            fprintf(f, "%i %s %s\n", i, ht->items[i]->key, ht->items[i]->value);
        }
    }
    fprintf(f, "Elements with next keys are being deleted: \n");
    printf("Elements with next keys are being deleted:\n");
    for (int k = 0; k < ht->count; ++k) {
        printf("%s\n", inputKeys[k]);
        fprintf(f, "%s\n", inputKeys[k]);
        ht_delete(ht, inputKeys[k]);
        if (ht_search(ht, inputKeys[k]) != NULL) {
            printf("ERROR OF REMOVE %s\n", inputKeys[k]);
            fprintf(f, "ERROR OF REMOVE %s\n", inputKeys[k]);
        }
    }
    printf("Hash Table after removal first 25 elements from input list\n");
    fprintf(f, "Hash Table after removal first 25 elements from input list\n");
    for (int i = 0; i < ht->size; i++) {
        if (ht->items[i] != NULL && ht->items[i]->key != NULL) {
            printf("%i %s %s\n", i, ht->items[i]->key, ht->items[i]->value);
            fprintf(f, "%i %s %s\n", i, ht->items[i]->key, ht->items[i]->value);
        }
    }
    for (int j = 0; j < 25; j++) {
        ht_insert(ht, inputKeys[j], inputValues[j]);
    }
    printf("Adding the same elements after their removal\n");
    fprintf(f, "Adding the same elements after their removal\n");
    for (int i = 0; i < ht->size; i++) {
        if (ht->items[i] != NULL && ht->items[i]->key != NULL) {
            printf("%i %s %s\n", i, ht->items[i]->key, ht->items[i]->value);
            fprintf(f, "%i %s %s\n", i, ht->items[i]->key, ht->items[i]->value);
        }

    }

    if (ht_del_hash_table(ht) == 1) {
        fprintf(f, "Hash table was deleted successfully");
        printf("Hash table was deleted successfully");
    }
    fclose(f);
    exit(0);
}
