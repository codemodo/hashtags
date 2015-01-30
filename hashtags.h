/*
 ============================================================================
 Name        : hashtags.h
 Author      : Alex Fiuk
 Description : Header file for Hashtags program
 ============================================================================
 */

// the initial capacity (number of buckets)
#define CAPACITY 100

typedef struct Node node;
struct Node {
  char* value;
  unsigned long freq;
  node* next; // next node in the list
};

typedef struct Hashtable hashtable;
struct Hashtable {
  node* list[CAPACITY]; // "buckets" of linked lists
};

/* Function prototypes */
int hash(char*, unsigned long*);
int put(char*, hashtable*);
int get(char*, hashtable*);
void print_top_n_hashtags(int, hashtable*);
void refresh_lowest(unsigned long*, unsigned long*, hashtable*, int);
void sort_top_tags(int, hashtable*);