
#include <stdbool.h>

typedef struct {
	unsigned char _data[32];
} HashTable;


// create and destroy

HashTable ht_create(
	unsigned int(*hashFunction)(void *), 
	bool (*eqFunction)(void *, void *)
);
void ht_destroy(HashTable t);


// accessors

unsigned int ht_getLength(HashTable t);
unsigned int ht_getNumBuckets(HashTable t);


// mutators

// returns true if value was not already present
bool ht_insert(HashTable t, void *value);
