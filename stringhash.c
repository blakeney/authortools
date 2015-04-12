/*
 * stringhash.c -- Hash table implementation
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringhash.h"

// Use a medium-sized prime number as the size of the hash table
// to reduce the number of hash collisions.
#define ROWS 4093

// For hashing individual strings
#define SMALLPRIME 31

int hash(char* word) {
	// Suggested by Algorithms, 4th Edition, Section 3.4
	int hashcode = 0;
	while (*word) {
		hashcode = (SMALLPRIME * hashcode + *word++) % ROWS;
	}
	// Absolute value is needed because special characters can
	// have negative integer values.
	return abs(hashcode);
}

void inc_entry(entry *ent) {
	(*ent).value++;
}

entry** mk_table() {
	entry** table = malloc(ROWS * sizeof(entry*));
	assert(table);
	entry* cell;
	for (int i=0; i < ROWS; i++) {
		cell = calloc(1, sizeof(entry));
		assert(cell);
		table[i] = cell;
	}
	return table;
}

void del_table(entry** table) {
	entry* cell;
	entry* tmp;
	for (int i=0; i < ROWS; i++) {
		cell = table[i];
		while (cell) {
			if (cell->key) {
				free(cell->key);
			}
			tmp = cell;
			cell = (entry*)cell->next;
			free(tmp);
		}
	}
	free(table);
}

void add_word(char* word, entry** table) {
	int row_num = hash(word);
	entry* cell = table[row_num];
	int wordsize = strlen(word)+1;
	while (cell) {
		// Free slot at end of list for new word
		if (cell->value == 0) {
			// Space for key in slot
			cell->key = malloc(wordsize);
			assert(cell->key);
			// Set up next slot
			cell->next = calloc(1,sizeof(entry));
			assert(cell->next);
			// Set values for this slot
			strlcpy(cell->key, word, wordsize);
			inc_entry(cell);
			return;
		// Slot in middle of list for existing word
		} else if (strcmp(cell->key, word) == 0) {
			inc_entry(cell);
			return;
		}
		cell = (entry*)cell->next;
	}
	// If the following line is reached, then the word was not placed
	// in the table, which should never happen.
	assert(0);
}

void print_table(entry** table) {
	entry* cell;
	for (int i=0; i < ROWS; i++) {
		cell = table[i];
		while (cell) {
			if (cell->value > 0) {
				printf("%d %s\n", cell->value, cell->key);
			}
			cell = (entry*)cell->next;
		}
	}
}

