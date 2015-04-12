/*
 * stringhash.h -- Hash table interface
 */

#ifndef STRINGHASH_H
#define STRINGHASH_H

typedef struct {
	int				value;
	char			*key;
	struct entry	*next;
} entry;

entry** mk_table();
void add_word(char* word, entry** table);
void del_table(entry** table);
void print_table(entry** table);

#endif

