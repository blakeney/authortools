/*
 * wf.c -- Tabulate word frequencies
 */

#define _WITH_GETLINE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include "stringhash.h"

#define BUF_SIZE 1024
#define SEPARATORS " /\\\n\r\t\"',.;:!?()[]{}-_"

void downcase_word(char* word) {
	size_t len = strlen(word);
	for (int i = 0; i < len; i++) {
		word[i] = towlower(word[i]);
	}
}

void hash_stream(FILE* file, entry** table) {
	size_t bufsize = BUF_SIZE;
	char* filebuf = NULL;
	char* word;
	while (getline(&filebuf, &bufsize, file) > 0) {
		char* filebufcopy = filebuf;
		while ((word = strsep(&filebufcopy, SEPARATORS))) {
			if (strlen(word) > 0) {
				downcase_word(word);
				add_word(word, table);
			}
		}
	}
	free(filebuf);
}

// Stream reading modeled after https://gist.github.com/txgruppi/4495965

void read_file(char *path, entry** table) {
	FILE *file = fopen(path, "r");
	assert(file);
	hash_stream(file, table);
	fclose(file);
}

void read_stdin(entry** table) {
	hash_stream(stdin, table);
}

int main(int argc, char **argv) {
	entry** table = mk_table();
	if (argc > 1 ) {
		for (int i=1; i < argc; i++) {
			read_file(argv[i], table);
		}
	} else {
		read_stdin(table);
	}
	print_table(table);
	del_table(table);
	return 0;
} 

