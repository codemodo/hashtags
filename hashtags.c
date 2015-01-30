/*
 ============================================================================
 Name        : hashtags.c
 Author      : Alex Fiuk
 Description : Methods used to analyze hashtags in text file.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtags.h"


/*
 * For the given string referred to by the pointer "string",
 * calculate the hashcode and update the variable pointed to by "value".
 *
 * Return 1 if successful, and 0 if an error occurred
 * (e.g. if the string is null).
 */
int hash(char* string, unsigned long* value)
{
  if (string == NULL || value == NULL) {
  	return 0;
  }

  int hash_code = 0;
  int len = strlen(string);
  
  for (int i = 0; i < len; i++) {
  	hash_code = hash_code + string[i];
  }

  *value = hash_code;
  return 1;
}


/*
 * Adds the string to the hashtable in the appropriate "bucket".
 *
 * Returns 1 if successful, and 0 if an error occurred
 * (e.g. if the string is null, if memory could not be allocated,
 * or if the string is already in the hashtable).
 */
int put(char* string, hashtable* h)
{
	unsigned long tempValue;

	//1. get the hashcode
	if (hash(string, &tempValue) == 0) {
		return 0;
	}
	//2. figure out which bucket
	int bucket_num = tempValue % CAPACITY;

	// //3. add to that bucket (Linked List)
	node* head = h -> list[bucket_num];
	node* new = malloc(sizeof(node));
	new -> value = malloc (strlen(string) + 1);
	strcpy(new -> value, string);
	new -> next = head;
	new -> freq = 1;
	h -> list[bucket_num] = new;
	return 1;
}


/*
 * Determines whether the specified string is in the hashtable.
 * Returns 1 if it is found, 0 if it is not (or if it is null).
 */
int get(char* string, hashtable* h)
{
	unsigned long tempValue;

	if (string == NULL) {
		return 0;
	}

	// load tempValue with the hashcode
	if (hash(string, &tempValue) == 0) {
		return 0;
	}

	//get bucket number to corresponding linked list
	int bucket_num = tempValue % CAPACITY;
	node* currNode = h -> list[bucket_num];
	while (currNode != NULL) {
		if (strcmp(currNode -> value, string) == 0) {
			currNode -> freq++;
			return 1;
		}
		currNode = currNode -> next;
	}
	return 0;
}


/*
 * Creates new hashtable containing top n hashtags
 * Prints top n hashtags
 */
void print_top_n_hashtags(int n, hashtable* h)
{
hashtable* top_tags = malloc(sizeof(hashtable));
int i = 0;
unsigned long* lowestPos = malloc(sizeof(unsigned long));
unsigned long* lowestVal = malloc(sizeof(unsigned long));
int tags_checked = 0;


node* curr_head = malloc(sizeof(node*));
curr_head = h -> list[i];


while (i < CAPACITY) {

	while (curr_head != NULL) {
		
		while (curr_head != NULL) {
			
			if (tags_checked > n) {
				
				if (curr_head -> freq > *lowestVal) {
					top_tags -> list[*lowestPos] = curr_head;
					refresh_lowest(lowestPos, lowestVal, top_tags, n);
				}
			}

			else if (tags_checked == n) {
				refresh_lowest(lowestPos, lowestVal, top_tags, n);
				tags_checked ++;
			}

			else if (tags_checked < n) {
				top_tags -> list[(int)tags_checked] = curr_head;
				tags_checked++;
			}

			curr_head = curr_head -> next;
		}
	}
	i++;
	curr_head = h -> list[i];
}

sort_top_tags(n, top_tags);

for (i = 0; i < n; i++) {
	node* print_head = malloc(sizeof(node*));
	print_head = top_tags -> list[i];
	int j = 0;
	
	while ( (print_head -> value)[j] != '\0' ) {
		printf("%c", (print_head -> value)[j]);
		j++;
	}
	
	printf(": %lu\n", print_head -> freq);
}

}


/*
 * Used to help keep track of lowest frequency hashtags that have been added
 * to the top_tags table as it's being built.  When a greater frequency than the lowest is encountered,
 * the lowest position and value are updated.
 */
void refresh_lowest(unsigned long* pos, unsigned long* val, hashtable* h, int n)
{
	node* curr_node = malloc(sizeof(node*));
	curr_node = h -> list[0];
	unsigned long temp_low_val =  curr_node -> freq;
	unsigned long temp_low_pos = 0;
	for (int i = 1; i < n; i++) {
		curr_node = h -> list[i];
		if (curr_node -> freq < temp_low_val) {
			temp_low_val = curr_node -> freq;
			temp_low_pos = i;
		}
	}
	*pos = temp_low_pos;
	*val = temp_low_val;
}


/*
 * Used to sort the top n tags after the hashtable containing them is completed
 */
void sort_top_tags(int n, hashtable* h)
{
	int i = 0;
	while (i < n) {
		int j = i + 1;
		while (j < n) {
			
			if (h -> list[i] -> freq >= h -> list[j] -> freq) j++;
			
			else {
				node* temp_pnt = malloc(sizeof(node*));
				temp_pnt = h -> list[i]; 
				h -> list[i] = h -> list[j];
				h -> list[j] = temp_pnt;
				j = n + 1;
				i = -1;
			}
		}
		i++;	
	}
}






