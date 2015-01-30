/*
 ============================================================================
 Name        : main.c
 Author      : Alex Fiuk
 Description : Main method for Hashtags program
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtags.h"


int main(void)
{
	hashtable *twit_hash = malloc( sizeof(hashtable) );
	FILE *fptr;
	char ch;
	char word [500];
	char file_name[100];
	printf("Please enter the name of a file to be analyzed: ");
	scanf("%s", file_name);
	fptr = fopen(file_name, "r");
	if (fptr == NULL) {
		perror("Error: ");
		exit(1);
	}

	// Read in file word by word.  If hashtag found, compare it against previously found hashtags.
	// If new, add to hashtable.  Otherwise, get() simply increments the hashtag's frequency.  
	do {
		ch = fscanf(fptr, "%s", word);
		
		if (word[0] == 35) {
			
			for (int i = 0; i < strlen(word) + 1; i++) {
				word[i] = tolower(word[i]);
			}
			
			if (get(word, twit_hash) == 0) {
				put(word, twit_hash);
			}				
		}
	} while (ch != EOF);
	printf("\nTop 10 hashtags and their frequencies:\n");
	print_top_n_hashtags(10, twit_hash);
	fclose(fptr);
	return EXIT_SUCCESS;
}